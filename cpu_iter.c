#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, char* argv[]) {
	
	// to use: ./[out] [loop size]

	//int loops = atoi(argv[1]);

    int loops = 1000000;
	unsigned long int total = 0;
    unsigned long int start;
    unsigned long int end;
    int i =0; 
    rdtsc();
    start = rdtsc();
	for (; i < loops; i++) {

	}
    end = rdtsc();
    total = end - start;
	printf("CPU reading rdtsc iteration average time :%llu  %f\n", total, total*1.0/loops);
}