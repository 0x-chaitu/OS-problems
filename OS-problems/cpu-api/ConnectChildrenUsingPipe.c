#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h> //fork
#include <string.h>

int main(void){
    int pipefd[2];
    int rc[2];
    char *word;
    if (pipe(pipefd) == -1){
        //pipe function return two file descriptors
        //first is read end late write end of the pipe
        //used for interprocess communication
        //data at 2nd end is buffered by kernel until read by 1st end
        perror("error in pipe");
    }

    if( (rc[0] = fork()) == -1 ){
        perror("Rc Error");
    }else if(rc[0] == 0){
        //child 1
        word = "hello from child\n";
        close(pipefd[0]);
        // if (pipefd[1] != STDOUT_FILENO) { 
        //     if (dup2(pipefd[1], STDOUT_FILENO) != STDOUT_FILENO) perror("error dup2");
        //     close(pipefd[1]);
        // }
        write(pipefd[1],word,strlen(word)+1);
        close(pipefd[1]);

    }else {
        if ((rc[1] = fork() ) == -1){
            perror("Error");
        }else if (rc[1] == 0)
        {
            close(pipefd[1]);
            //printf("%d %d",pipefd[0], STDIN_FILENO);
            // if (pipefd[0] != STDIN_FILENO) { // APUE 15.2
            //     if (dup2(pipefd[0], STDIN_FILENO) != STDIN_FILENO) perror("error dup2");
            //     close(pipefd[0]);
            // }   
            char buf[BUFSIZ];
            read(pipefd[0], buf, BUFSIZ);
            close(pipefd[0]);
            printf("Second %s",buf);
        }else {
            if (waitpid(rc[0],NULL,0) < 0  ){
                perror("Error in waiting");
            }
            if (waitpid(rc[1],NULL,0) < 0  ){
                perror("Error in waiting");
            }
        }
        
    }
    return(0);
 
}