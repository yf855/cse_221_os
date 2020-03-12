#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int fd[2];

void *helper_func(void *tid) {
    unsigned long int end;
    end = rdtsc();
    write(fd[1], &end, sizeof(end));
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    int loops = 10000;
    
    int i = 0;
    unsigned long int total = 0;
    
    pipe(fd);
    
    for(;i < loops;i++) {
        pthread_t thread;
        pthread_create(&thread, NULL, helper_func, NULL);
        
        unsigned long int start, end;
        start = rdtsc();
        read(fd[0], &end, sizeof(end));
        pthread_join(thread, NULL);
        total += end - start;
    }
    printf("thread context switch: %llu cycles;\n", total/loops, total);
    return 0;
}
