#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, char* argv[]) {


    unsigned long int start, end;
    //generate random 
    srand(time(NULL));

    int size = 9;
    int loops = 100000;
    
    for(;size < 31;size++) {
        unsigned long int arraysize = 1 << size;
        unsigned long int start, end;
        unsigned long int total = 0;
        //allocate array of "arraysize"
        char *array = (char*)malloc( sizeof(char) * arraysize);
        memset(array,'1',arraysize);
        rdtsc();
        start = rdtsc();
        int i = 0;
        for(;i < loops;i++) {
            //access random position
            int pos = rand() % (arraysize-1);
            char ch = array[pos];
        }
        end = rdtsc();
        total += end - start;
        free(array);
        
        printf("With Array size : %d, the memory access time is : %f\n", size, (total*1.0)/loops);
        
    }
    
    
    
    return 0;
    
}
