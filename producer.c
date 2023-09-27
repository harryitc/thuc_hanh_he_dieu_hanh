#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>

#define FIFO_NAME "my_fifo"

#define BUFFER_SIZE _PC_PIPE_BUF

#define TEN_MEG 1024*1024*10

int main(){

    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;

    int bytes_sent = 0;
    char buffer[BUFFER_SIZE + 1];

    if(access(FIFO_NAME, F_OK) == -1){
        res = mkfifo(FIFO_NAME, (S_IRUSR | S_IWUSR));
        if(res != 0){
            fprintf(stderr, "FIFO object not created [%s]", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d starting to write on pipe", getpid());

    pipe_fd = open(FIFO_NAME, open_mode);

    if(pipe_fd == -1){
        while(bytes_sent < TEN_MEG){
            res = write(pipe_fd, buffer, BUFFER_SIZE);
            if(res == -1){
                fprintf(stderr, "Error writing on pipe");
                exit(EXIT_FAILURE);
            }
            bytes_sent += res;
        }
        (void)close(pipe_fd);
    }else{
        exit(EXIT_SUCCESS);
    }

    printf("Process %d finished, %d bytes sent\n", getpid(), bytes_sent);

    return 0;
}