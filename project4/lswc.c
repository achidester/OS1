#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>

int main(int argc, char *argv[]){
    (void)argc;                     // cast it into the fire!       

    int pfd[2];        
    pipe(pfd);

    int pid = fork();

    if(pid ==-1){                   // if fork fails it will return a -1, print an error
        perror("Error: Fork failed");
        exit(1);
    }
         
    if(pid == 0){                   //child process runs wc on the parents ls (after duping std out)
        dup2(pfd[0], 0); 
        close(pfd[1]);                   
        execlp("wc", "wc", "-l", 0, NULL);
        perror("Error: Child process exec failed");
        exit(1);                     
    } 
    else{                          //parent process sends ls through a pipe (after duping std in)  
        dup2(pfd[1], 1);
        close(pfd[0]);
        execlp("ls", "ls", "-1a", argv[1], NULL);
        perror("Error: Parent process exec failed.");
        exit(1); 
    }

}