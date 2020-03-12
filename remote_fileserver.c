#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#define MAX 80 
#define PORT 50027 
#define SA struct sockaddr 

#define FPATH "./remotefileread.txt"

// Function designed for chat between client and server. 
void func(int sockfd, double coefficient) { 
    char buff[MAX]; 
    int blksize = 4 * 1024;
    void* buf = malloc (blksize);


    unsigned long long megabit = 1<< 20;
    unsigned long long Fsize = coefficient*megabit*sizeof(char);
    unsigned long long blknum = Fsize/blksize;

    int n; 
    // infinite loop for chat 
    while (1) { 
        bzero(buff, MAX); 
    
        // read the message from client and copy it in buffer 
        read(sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s \t To client : ", buff); 
        if(strcmp(buff, "seq")){
            int fd = open(FPATH, O_SYNC);
            int no_cache = fcntl(fd, F_NOCACHE,1);
            if (no_cache == -1){
                printf("cache cannot disable\n");
                exit(-1);
            }

            //unsigned long int start, end;
            //unsigned long int total = 0;
            unsigned long long i = 0;
            lseek(fd, Fsize-1, SEEK_SET);
            for (;i<blknum;i++){
                lseek(fd, -i*blksize, SEEK_CUR);     
                ssize_t bytes = read(fd,buf,blksize);

            }
            close(fd);
            bzero(buff, MAX); 
            buff[0] = 'c';
        }else if(strcmp(buff,"rand")){
            int fd = open(FPATH, O_SYNC);
            int no_cache = fcntl(fd, F_NOCACHE,1);
            if (no_cache == -1){
                printf("cache cannot disable\n");
                exit(-1);
            }
            //unsigned long int total = 0;
            unsigned long long i = 0;

            //random
            //lseek (fd, 0, SEEK_SET);
            for (;i<blknum;i++){
                int offset= rand()%blknum;
                lseek(fd, offset*blksize,SEEK_SET);
                read (fd, buf,blksize);
            }
            close(fd);
            bzero(buff, MAX); 
            buff[0] = 'c';
            free(buf);
        }

        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
    free(buf);
} 
  
// Driver function 
int main() { 
    //socket creation referred from internet
    //create a file first
    //random seed
    srand(time(NULL));
    //void* buf = malloc (blksize);
    int blksize = 4 * 1024;
    double coefficient = 4;

    unsigned long long megabit = 1<< 20;
    unsigned long long Fsize = coefficient*megabit*sizeof(char);
    unsigned long long blknum = Fsize/blksize;

    FILE *fp = fopen(FPATH,"w");
    ftruncate(fileno(fp),coefficient*megabit*sizeof(char));
    fclose(fp);


    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed\n"); 
        exit(0); 
    } 
    else
        printf("Socket creation successful..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    // Function for chatting between client and server 
    func(connfd, coefficient); 
  
    // After chatting close the socket 
    close(sockfd); 

} 
