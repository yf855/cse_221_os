#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>

/*
Note and Citation: the client and server for remote file access is adapted from a chat bot program from geekforgeek.com
*/

#define MAX 80 
#define PORT 50027 
#define SA struct sockaddr 

static inline uint64_t rdtsc(void) {
    uint32_t lo, hi;
    __asm__ __volatile__("xor %%eax, %%eax;" "cpuid;" "rdtsc;": "=a" (lo), "=d" (hi));
    return (((uint64_t)hi << 32) | lo);
}

void func(int sockfd, unsigned long long blknum) { 
    char buff[MAX]; 
    int n; 
    unsigned long int start,end;
    unsigned long int total =0; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        start = rdtsc();
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        end = rdtsc();
        total += end -start; 
        printf("time : %f\n", total/blknum);
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main() { 
    double coefficient = 4; 
    int blksize = 4*1024;
    unsigned long long megabit = 1<< 20;
    unsigned long long Fsize = coefficient*megabit*sizeof(char);
    unsigned long long blknum = Fsize/blksize;
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func(sockfd,blknum); 
  
    // close the socket 
    close(sockfd); 
} 
