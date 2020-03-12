#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, char* argv[]) {

    int size_pow = 28; //32 MB 3+5+20
    unsigned long int size = 1<<size_pow;
    char *array = (char*) malloc(size*sizeof(char));
    memset (array, '1', size);
    
    unsigned long int total_read = 0;
    unsigned long int total_write = 0;
    unsigned long int start, end;
    unsigned long int halfsize = size/2 -1;
    
    
    int loops = 100;
    int j = 0;
    char ch1, ch2,ch3,ch4;

// read bandwidth    
    int i = 0;
    rdtsc();
    start = rdtsc();
    for(;i < loops;i++) {
        int j = 0;
        for(;j < halfsize;j += 2) {
             ch1 = array[j];
             ch2 = array[size-1-j];
             ch3 = array[j+1];
             ch4 = array[size-2-j];
        }
    }
    
    end = rdtsc();
    total_read = end - start;

    printf ("Read bandwidth = %f MB/s\n", 8*loops*size/((total_read)*4.5*pow(10,-10)*1024*1024));
  // write bandwidth    
    i = 0;
    for(;i < loops;i++) {
        int j = 0;
        for(;j < halfsize;j += 2) {
            array[j] = '0';
            array[size-1-j]='0';
            array[j+1]='0';
            array[size-2-j]='0';
        }
    }
    
    end = rdtsc();
    total_write = end - start;
    printf ("Write bandwidth = %f MB/s\n", 8*loops*size/((total_write)*4.5*pow(10,-10)*1024*1024));
    
    free (array);

    return 0;
}
