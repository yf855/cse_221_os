#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, char * argv[]){
    
    int loops = 10000;
    int i = 0;
    unsigned long int total = 0;
    for(;i < loops;i++) {
        
        int fd[2];
        pid_t cpid;        
        pipe(fd); 
    
        cpid = fork(); 
        if (cpid == -1) {
            printf("fork failure\n");
            exit(-1);
        }
        if(cpid!= 0){
            unsigned long int start, end;
            start = rdtsc();
            wait(NULL);
            read(fd[0], &end, sizeof(end));
            total += end - start;
            wait(NULL);
        }else{ 
            unsigned long int end;
            end = rdtsc();
            write(fd[1], &end, sizeof(end));
            return 0;
        }  

    }

    printf("Process Context Switch : %llu cycles \n", total/loops);
    return 0;
}