#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

void catch_int(int sig_num){
    signal(SIGINT, catch_int);
    printf("Caught signal %d - Do not press Ctrl+C\n", sig_num);
}

int main(){

    int count = 0;

    signal(SIGINT, catch_int);

    while(1){
        printf("Counting ... %d\n",count++);
        sleep(1);
    }

    return 0;
}