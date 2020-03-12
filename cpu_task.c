#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>


static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}
void proc_creation(){
	unsigned long int total = 0;
    unsigned long int start;
    unsigned long int end;
    pid_t pid;
    int loops = 10000;
    int i =0; 
    for (; i < loops; i++) {
        rdtsc();
        start = rdtsc();
        pid = fork();
    
        if (pid == 0) {
            exit(1);
        }else {
            wait(NULL);
            end = rdtsc();
            total += end - start;
        }
    }
    printf("process creation time: %f\n", total*1.0/loops);
}
void *runThread(void *tid) {
     pthread_exit(NULL);
}
void thread_creation(){
    unsigned long int total = 0;
    unsigned long int start;
    unsigned long int end;
    pid_t pid;
    int loops = 10000;
    int i =0; 
    for (; i < loops; i++) {
        pthread_t thread;

        rdtsc();
        start = rdtsc();
        pthread_create(&thread, NULL, runThread, NULL);
        end = rdtsc();
        total += end - start;
        pthread_join(thread, NULL);
    }
    
    printf("thread creation time: %f\n", total*1.0/loops);
}
int main(int argc, char **argv) {
    proc_creation();
    thread_creation();
    return 0; 

}