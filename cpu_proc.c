#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#pragma OPTIMIZE OFF

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

void __attribute__ ((noinline)) test0() {}
void __attribute__ ((noinline)) test1(int a1) {}
void __attribute__ ((noinline)) test2(int a1, int a2) {}
void __attribute__ ((noinline)) test3(int a1, int a2, int a3) {}
void __attribute__ ((noinline)) test4(int a1, int a2, int a3, int a4){}
void __attribute__ ((noinline)) test5(int a1, int a2, int a3, int a4, int a5){}
void __attribute__ ((noinline)) test6(int a1, int a2, int a3, int a4, int a5, int a6){}
void __attribute__ ((noinline)) test7(int a1, int a2, int a3, int a4, int a5, int a6, int a7){}


int main(int argc, char* argv[]) {

    int loops = 100000;
	unsigned long int total;
    unsigned long int start;
    unsigned long int end;
    int i =0; 

//0 arg
    total = 0;
    i = 0;
    rdtsc();
    for (; i < loops; i++) {
        start = rdtsc();
        test0();
        end = rdtsc();
        total += (end - start);
    }
    printf("0 argument function procedure call overhead: %f cycles\n", total*1.0/loops);

//1 arg
    total = 0;
    i = 0;
    rdtsc();
    for (; i < loops; i++) {
        start = rdtsc();
        test1(1);
        end = rdtsc();
        total += (end - start);
    }
    printf("1 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
//2 argss
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test2(1,2);
        end = rdtsc();
        total += (end - start);
    }
    printf("2 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
//3 args
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test3(1,2,3);
        end = rdtsc();
        total += (end - start);
    }
    printf("3 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
//4 args
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test4(1,2,3,4);
        end = rdtsc();
        total += (end - start);
    }
    printf("4 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
//5 args 
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test5(1,2,3,4,5);
        end = rdtsc();
        total += (end - start);
    }
    printf("5 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
// 6 args
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test6(1,2,3,4,5,6);
        end = rdtsc();
        total += (end - start);
    }
    printf("6 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
// 7 args
    total = 0;
    i = 0;
    rdtsc();

    for (; i < loops; i++) {
        start = rdtsc();
        test7(1,2,3,4,5,6,7);
        end = rdtsc();
        total += (end - start);
    }
    printf("7 argument function procedure call overhead: %f cycles\n", total*1.0/loops);
}