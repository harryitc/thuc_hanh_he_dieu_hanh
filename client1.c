#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>

int main(){

    int sockfd;

    int len;

    
    struct sockaddr_un addr;

    int result;
    char ch = 65;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path,"server_socket");

    len = sizeof(addr);

    result = connect(sockfd, (struct sockaddr*)&addr, len);

    if(result == -1){
        perror("Oops! client1 problem");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("Char from servere %c", ch);
    close(sockfd);
    exit(0);
    return 0;
}