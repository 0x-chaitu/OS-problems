#include <unistd.h> //fork
#include <signal.h> //sigaction kill
#include <stdio.h>
#include <getopt.h>
#define _XOPEN_SOURCE 700


static sig_atomic_t sig = 0;
static void sigHandler() {
    sig = 1; //on arriving of signal change the wait state to not-waiting
}

static void waitForSignal(){
    //define action
    struct sigaction action; // datatype sigaction: 
    action.sa_handler = sigHandler; //handler fucntion 
    sigemptyset(&action.sa_mask); //sigemptyset constructor initilizes the set sa_mask to 
                                  //exclude all of the signal
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, NULL) == -1){ // sigaction function 
        //how a signal must be handled by process 
        //Signal is SIGUSR1  
        //newaction is the middle paramater, old action is the last parameter
        printf("Error in sigaction");
    }

    sigset_t newSet, oldSet; 
    sigemptyset(&newSet);
    sigaddset(&newSet,SIGUSR1);

    if (sigprocmask(SIG_BLOCK,&newSet, &oldSet) == -1){
        printf("error in manipulating process mask");
    }; 
    //method is used to change the current process signal mask
    //collection of signals currenlty blocked
    //merges oldmask into newmask if SIG_BLOCK is provided as first parameter
    
    int pid = fork(); //create a child process
    if(pid == 0) {
        printf("I am child\n");
        kill(getppid(),SIGUSR1);//send a signal to parent
    }else if (pid == -1)
    {
        printf("error in starting a new process");
    }else {
        while(sig == 0){
            sigsuspend(&oldSet); //process mask is replaced with parameter
                //then process is suspended until a signal not part of process arrives
                //when sigsuspend return newSet is regained as mask
        }
        printf("I am parent\n");
    }
    



}

int main(void) {

    waitForSignal();
    return(0);
}
