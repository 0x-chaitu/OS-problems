#include <unistd.h> //fork
#include <stdio.h> 
#include <sys/wait.h>


void writeToFile(FILE *fp, char *string){
    for (int i = 0; string[i] != 0x00;i++ ){
        fputc(string[i],fp);
    } 
}

int main(int argc, char **argv){
    __pid_t pid;
    FILE *fp;
    char *string;
    fp = fopen("Conn.txt","w+");
    if (fp == NULL){
        printf("Cannot open file\n");
        return 1;
    }

    pid = fork();
    
    if(pid==0) {    //child
        string = "Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file Race condition from child to write to the same file \n";
        writeToFile(fp, string);
    }else if(pid == -1){
        printf("Error in creating achild process\n");
    }else {       //parent
        string = "Can Parent access fp when child is writing to it? Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  Can Parent access fp when child is writing to it?  \n";   
        writeToFile(fp, string);
        wait(NULL);
    }
    fclose(fp);
    return 0;
}
