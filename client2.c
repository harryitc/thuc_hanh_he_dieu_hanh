#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#include<arpa/inet.h>


int main(){
    int sockfd;
    int len;
    struct sockaddr_in addr;
    int result;

    char ch = 'A';

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9734);
    len = sizeof(addr);
    result = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    if(result == -1){
        perror("Oops: client2 problem");
        return 0;
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server: %c\n", ch);
    close(sockfd);
    return 1;
}