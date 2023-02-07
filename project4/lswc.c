#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>

int main(int argc, char *argv[]){
    (void)argc;                                  

    int pfd[2];
    pipe(pfd);

    int pid = fork();

    if(pid ==-1){
        perror("Error: Fork failed");
        exit(1);
    }
         
    if(pid == 0){ 
        dup2(pfd[0], 0); 
        close(pfd[1]);                   
        execlp("wc", "wc", "-l", 0, NULL);
        perror("Error: Child process exec failed");
        exit(1);                     
    } 
    else{                                     
        dup2(pfd[1], 1);
        close(pfd[0]);
        execlp("ls", "ls", "-1a", argv[1], NULL);
        perror("Error: Parent process exec failed.");
        exit(1); 
    }

}