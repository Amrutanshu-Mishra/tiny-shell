#include<stdio.h>
#include<string.h>

int main(){
    char *p="abc";
    int size_p=sizeof(*p)/sizeof(char);
    printf("%d\n", size_p);
}