#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

#define MAX_INPUT 1024

char** parse_input(char *input_string){
    char **ptr=(char **)malloc(2*sizeof(*ptr));

    //handling the case in which malloc could fail
    if(ptr==NULL){
        return NULL;
    }

    int ptr_size=0;
    int ptr_capacity=2;

    char d[]=" ";
    char *portion=strtok(input_string, d);
    int idx=0;


    while(portion!=NULL){
        //using the memory allocation pattern where we double the memory on each realloc
        if(ptr_size+1==ptr_capacity){
            ptr_capacity*=2;
            char **tmp=realloc(ptr, ptr_capacity*sizeof(*ptr));
            if(tmp==NULL){
                free(ptr);
                return NULL;
            }
            ptr=tmp;
        }
        ptr[idx]=portion;
        // printf("%s\n", portion);
        idx++;
        ptr_size++;

        portion=strtok(NULL, d);
    }
    // idx--;
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
            printf("\n");
            break;
        }

        //removing the \n from the input
        input[strcspn(input, "\n")]='\0';


        //modifying this input into a new char* so that it can be passed to the function
        char *mod_input=strdup(input);
        
        //handling the case in which strdup could fail
        if(mod_input==NULL){
            perror("strdup");
            continue;
        }
        
        //parsing the mod input into token
        char **input_token_array=parse_input(mod_input);
        
        //handling the edge case where input_token_array is NULL
        if(input_token_array==NULL){
            free(mod_input);
            continue;
        }

        //handling the edge case when the user gives no input
        if(input_token_array[0]==NULL){
            free(input_token_array);
            free(mod_input);
            continue;
        }

        //Now calling a child process
        pid_t pid=fork();

        if(pid<0){
            perror("fork");
        }
        else if(pid==0){
            //inside the child process
            execvp(input_token_array[0], input_token_array);

            //if the command in the shell is not found
            if(errno==ENOENT){  
                fprintf(stderr,"%s: command not found\n", input_token_array[0]);
            }
            else{
                perror(input_token_array[0]);
            }

            exit(EXIT_FAILURE);
        }
        else{
            //the parent has to wait for th e
            wait(NULL);
        }

        free(input_token_array);
        free(mod_input);
    }
    
    return 0;
}