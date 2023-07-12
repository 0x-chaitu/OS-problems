#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h> //fork


int main(int argc, char const *argv[])
{
    int pid = fork();
    int waitPid;
    int status;

    if(pid == 0) {
        //waitPid = wait(NULL);
        
        //waitPid = waitpid(-1,NULL, WUNTRACED | WCONTINUED);
        //printf("Pid returned at child %d\n", waitPid);

        close(STDOUT_FILENO);
        printf("Accessing after closing stdout\n");
    }else if(pid == -1) {
        printf("error");
    }else {
        // waitPid = wait(NULL);
        // waitPid = waitpid(pid,&status, WUNTRACED | WCONTINUED);
        //printf("Pid returned at Parent %d %d\n", waitPid, status);

        wait(NULL);
        printf("Parent\n");
    }

    return 0;
}