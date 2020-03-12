#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>


static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

int main(int argc, const char *argv[]){
    int procID = atoi(argv[1]);
    int blksize = 4 * 1024;
    //random seed
    srand(time(NULL));
    void* buf = malloc (blksize);

    double coefficient = 2;

    unsigned long long megabit = 1<< 20;
    unsigned long long Fsize = coefficient*megabit*sizeof(char);
    unsigned long long blknum = Fsize/blksize;

    char FPATH[14];
    snprintf(FPATH,14, "fileproc%d.txt",procID);
    FILE *fp = fopen(FPATH,"w");
    ftruncate(fileno(fp),coefficient*megabit*sizeof(char));
    fclose(fp);
    // sequential access
    //use odirect and osync to minimize cache effects
    int fd = open(FPATH, O_SYNC);

    int no_cache = fcntl(fd, F_NOCACHE,1);
    if (no_cache == -1){
        printf("cache cannot disable\n");
        exit(-1);
    }
    unsigned long int start, end;
    unsigned long int total = 0;
    unsigned long long i = 0;
    lseek(fd, Fsize-1, SEEK_SET);

    for (;i<blknum;i++){
        lseek(fd, -i*blksize, SEEK_CUR);
        start = rdtsc();
        ssize_t bytes = read(fd,buf,blksize);
        end = rdtsc();
        total += end - start;
    }
    close(fd);
    printf("sequential total: %lu, time: %f \n", total, total*1.0/blknum);
    //random read
    total = 0;
    
    fd = open(FPATH, O_SYNC);

    no_cache = fcntl(fd, F_NOCACHE,1);
    if (no_cache == -1){
        printf("cache cannot disable\n");
        exit(-1);
    }
    //random
    //lseek (fd, 0, SEEK_SET);
    while(1){
        i=0;
        for (;i<blknum;i++){
            int offset= rand()%blknum;
            start = rdtsc();
            lseek(fd, offset*blksize,SEEK_SET);
            read (fd, buf,blksize);
            end = rdtsc();
            total += end - start;
        }
    }
    close(fd);
    printf("random read total: %lu, time %f \n", total, total*1.0/blknum);
    free(buf);
    return 0;

}
