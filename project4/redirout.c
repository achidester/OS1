#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    const int BUFFER = 2048;
    char input[BUFFER];

    if(argc < 3){
        perror("Error: Not enough information");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);

    int pfd[2];        
    pipe(pfd);


    pid_t pid = fork();

    if(pid == -1){                                // if fork fails it will return a -1, print an error
        perror("Error: Fork failed");
        exit(1);
    }

    if(pid == 0){                                 // child process 
        dup2(pfd[1], 1);
        close(pfd[0]);
        execvp(argv[2], argv + 2);
        perror("Error: The child has failed us");
        
    } else{
        close(pfd[1]);
        read(pfd[0], &input, BUFFER);
        write(fd, input, (size_t)BUFFER);

        perror("Error: The parent has failed us");
        close(pfd[0]);
        close(pfd[1]);

    }


}