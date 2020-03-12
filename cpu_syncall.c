#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>

#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

// just run this output file multiple times..

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, char **argv) {
    int start, end;
    rdtsc();
    start = rdtsc();
    getppid();
    end = rdtsc();
    //total+= end - start;
    printf("syncall time overhead:  %d\n", end - start);
   
    return end - start;
}