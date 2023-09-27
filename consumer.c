#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/types.h>
#include<fcntl.h>

#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE _PC_PIPE_BUF

int main(){

    int pipe_fd, res;

    int open_mode = O_RDONLY;

    int bytes_read = 0;

    char buffer[BUFFER_SIZE+1];

    printf("Process %d starting to read on pipe\n",getpid());

    pipe_fd = open(FIFO_NAME, open_mode);

    if(pipe_fd != -1){
        do{
            res = read(pipe_fd, buffer, BUFFER_SIZE);
                bytes_read += res;
            }while(res > 0);
            (void)close(pipe_fd);
        }else{
            exit(EXIT_FAILURE);
        }

    printf("Process %d finished %d bytes\n",getpid(),bytes_read);

    exit(EXIT_SUCCESS);

    return 0;
}