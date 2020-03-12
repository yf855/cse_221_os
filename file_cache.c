#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>

#define FPATH "./file_cache_data.txt"

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}


int main(int argc, char *argv[]){
    
    int blksize = 4*1024;
    void* buf = malloc(blksize);
    FILE *fp = fopen(FPATH,"w");
    //unsigned coefficient = 1;
    //unsigned coefficient = 2;
    //unsigned coefficient = 3;
    //unsigned coefficient = 4;
    //unsigned coefficient = 5;
    double coefficient = 8.5;
    unsigned long long Gigabit = 1<< 30;
    unsigned long long Fsize = coefficient*Gigabit*sizeof(char);
    unsigned long long blknum = Fsize/blksize;
    //create file of certain size
    ftruncate(fileno(fp),coefficient*Gigabit*sizeof(char));
    fclose(fp);
    int fd = open(FPATH, O_RDONLY);
    //read to memory first time
    lseek(fd, Fsize-1, SEEK_SET);
    unsigned long long i = 1;
    for (;i<blknum;i++){
        lseek(fd, -i*blksize, SEEK_CUR);
        ssize_t bytes = read(fd,buf,blksize);
    }
    close(fd);
    printf("you are here\n");
    //read again
    fd = open(FPATH, O_RDONLY);
    totalBytes = 0;
    lseek(fd,Fsize-1, SEEK_SET);

    i = 1;
    unsigned long int start, end;
    unsigned long int total = 0;
    for (;i<blknum;i++){
        lseek(fd, -i*blksize, SEEK_CUR);
        start = rdtsc();

        ssize_t bytes = read(fd,buf,blksize);
        end = rdtsc();
        total += end-start;
    }
    close(fd);
    free(buf);
    printf("total: %lu, time: %f", total, total*1.0/(Fsize/blksize));
    return 0; 
}