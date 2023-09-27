#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>

void user_handler(int inputPipe[], int outputPipe[]){
    char c;
    int rc;
    close(inputPipe[1]);
    close(outputPipe[0]);

    while((c = getchar()) > 0){
        rc = write(outputPipe[1],&c,1);
        if(rc == -1){
            perror("user handler: pipe write error");
            close(inputPipe[0]);
            close(outputPipe[1]);
            exit(1);
        }
        
        rc = read(inputPipe[0], &c, 1);

        if(rc <= 0){
            perror("user handler: read error");
            close(inputPipe[0]);
            close(outputPipe[1]);
            exit(1);
        }
        putchar(c);
    }

    close(inputPipe[0]);
    close(outputPipe[1]);
    exit(0);
}

void translator(int inputPipe[], int outputPipe[]){
    char c;
    int rc;
    close(inputPipe[1]);
    close(outputPipe[0]);

    while(read(inputPipe[0], &c, 1) > 0){

        if(__isascii(c) && islower(c)){
            c = toupper(c);
        }

        rc = write(outputPipe[1],&c,1);
        if(rc == -1){
            perror("translator: write error");
            close(inputPipe[0]);
            close(outputPipe[1]);
            exit(1);
        }
    }

    close(inputPipe[0]);
    close(outputPipe[1]);
    exit(0);

}

int main(){

    int us[2], su[2], pid, rc = pipe(us);

    if(rc == -1){
        perror("main: pipe user to translate error");
        exit(1);
    }

    rc = pipe(su);

    if(rc == -1){
        perror("main: pipe user to translate error");
        exit(1);
    }

    pid = fork();

    switch (pid)
    {
        case -1:
            perror("main: fork error");
            exit(1);
        case 0:
            translator(us,su);
            break;
        default:
            user_handler(su,us);
            break;
    }

    return 0;
}