#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    pid_t p=fork();

    if(p==0){
        printf("The child process ID is %d\n", getpid());
    }
    else{
        printf("The parent process ID is %d\n", getpid());
    }
}