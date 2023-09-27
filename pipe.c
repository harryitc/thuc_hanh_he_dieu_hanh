#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void do_child(int dataPipes[]){

    int c, rc;

    close(dataPipes[1]);

    while((rc = read(dataPipes[0], &c, 1)) > 0){
        putchar(c);
    }

    exit(0);
}

void do_parent(int dataPipes[]){
    int c, rc;
    close(dataPipes[0]);
    while( (c = getchar()) > 0){
        rc = write(dataPipes[1], &c, 1);
        if(rc == -1){
            perror("Parent: pipe write error");
            close(dataPipes[1]);
            exit(1);
        }
    }
    close(dataPipes[1]);
    exit(0);
}

int main(){

    int dataPipes[2];

    int pid, rc;

    rc = pipe(dataPipes);

    if(rc == -1){
        perror("Error: pipe cannot created");
        exit(1);
    }

    pid = fork();
    
    switch(pid){
        case -1:
            perror("Error: Child process cannot create");
            exit(1);
        case 0:
            do_child(dataPipes);
            break;
        default:
            do_parent(dataPipes);
            break;
    }

    return 0;
}