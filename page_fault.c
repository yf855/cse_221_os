#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

#define FPATH "./pagefaultdata.txt"

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}


int main(int argc, char *argv[]){
    printf("the page size for this system is %ld bytes. \n",sysconf(_SC_PAGESIZE));
    //int page_size = sysconf(_SC_PAGESIZE);
    int page_size = 4096;   //byte
    int file_size = 40960 * sizeof(char);   //41kB file

    FILE *fp = fopen(FPATH,"w");
    ftruncate(fileno(fp),40960*sizeof(char));
    fclose(fp);

    int fd = open(FPATH, O_RDWR);
    char * map;
    map = mmap (0, file_size, PROT_READ,MAP_FILE|MAP_PRIVATE,fd,0);
    if (map == MAP_FAILED) {
        close(fd);
        perror("Error mmapping");
        exit(EXIT_FAILURE);
    }
    unsigned long int start, end, total;
    total = 0;
    rdtsc();
    int i = 0;
    start = rdtsc();

    for (;i<10;i++){
        char ch = map[i*4096];
    }

    end = rdtsc();
    total += end - start;
    printf("total: %lu, pagefault per byte: %f\n", total, total*1.0/10);
    int unmap_result = munmap(map, file_size);
    close(fd);
    return 0; 
}