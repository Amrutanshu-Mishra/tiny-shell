#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_INPUT 1024

char** parse_input(char *input_string){
    char **ptr=(char *)malloc(2*sizeof(char*));
    int ptr_size=0;
    int ptr_capacity=2;


    char *dup_inp_str=input_string;
    char d[]=" ";
    char *portion=strtok(dup_inp_str, d);
    int idx=0;


    while(portion!=NULL){
        //using the memory allocation pattern where we double the memory on each realloc
        if(ptr_size+1==ptr_capacity){
            ptr_capacity*=2;
            char **tmp=realloc(ptr, ptr_capacity*sizeof(char*));
            if(tmp==NULL){
                free(ptr);
                return NULL;
            }
            ptr=tmp;
        }
        ptr[idx]=portion;
        idx++;
        ptr_size++;

        portion=strtok(NULL, d);
    }
    ptr[idx]=NULL;
    

    return ptr;
}

int main(){
    char input[MAX_INPUT];

    while (1)
    {
        printf("myshell>");
        fflush(stdout);

        if(fgets(input, MAX_INPUT, stdin) == NULL){
            perror("fgets falied");
            continue;
        }

        printf("You typed %s", input);
    }
    
    return 0;
}