#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>


int main(){
    pid_t p=fork();

    if(p==0){
        printf("Child process going to sleep\n");
        sleep(3);
        printf("Child process wakes up\n");
        exit(0);
    }
    else{
        wait(NULL);
        printf("Parent process being executed\n");
    }
}
