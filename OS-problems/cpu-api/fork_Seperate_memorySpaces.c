#include <unistd.h> //fork
#include <stdio.h> //printf
#include <sys/wait.h>

int main(int argc, char **argv){
   int x;
   x = 100;
   __pid_t pid;

   pid = fork();

   if (pid == 0) {
      printf("I am child with x as %d\n", x);
      x = 1056;
      printf("I am child with updates x as %d\n", x);
   } else if (pid == -1) {
      printf("Error in creating achild process");
   } else {
      wait(NULL);
      printf("I am parent with x as %d\n", x);
      x = 10590;
      printf("I am parent with updates x as %d\n", x);
   }
}