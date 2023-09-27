#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>


int main(){

    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_addr, client_addr;

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(9734);
    server_len = sizeof(server_addr);

    bind(server_sockfd, (struct sockaddr *)&server_addr, server_len);

    listen(server_sockfd, 5);

    signal(SIGCHLD, SIG_IGN);

    while(1){
        char ch;
        printf("Server waiting...\n");

        client_len = sizeof(client_addr);

        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);

        if(fork() == 0){
            read(client_sockfd, &ch, 1);
            sleep(3);
            ch++;
            write(client_sockfd, &ch, 1);
            close(client_sockfd);
            exit(0);
        }else{
            close(client_sockfd);
        }
    
    }


    return 0;
}