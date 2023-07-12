#include <unistd.h> //exec* fork 
#include <sys/wait.h>
#include <stdio.h> //printf

int main(void){

    int rc;
    char *argv[] = {"/bin/ls",NULL};

    if((rc = fork()) == 0) {
        if(execvp("/bin/ls",argv) == -1){
            printf("error");
        };
    }else if(rc == -1){
        printf("cant create a child process");
    }else{
        wait(NULL);
        //parent
    }

    if((rc = fork()) == 0) {
        if(execl("/bin/ls","ls",NULL) == -1){
            printf("error");
        };
    }else if(rc == -1){
        printf("cant create a child process");
    }else{
        wait(NULL);
        //parent
    }

    return(0);

}