#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>

int main(/* int argc,char *argv[] */ ){

    const int ALLOWED_WORDS = 128;
    const int BUFFER =  2048;

    while(1){
        printf("$$$ ");

    // Get/Parse command 
        char input[BUFFER];
        char *args_array[ALLOWED_WORDS]; 
        
        fgets(input, sizeof input, stdin);

        int i = 0;                  
        char *token = strtok(input, " \n");

        while(token != NULL && i < ALLOWED_WORDS){  // adding tokens to a char* array (p1.3)
            args_array[i] = token;                        
            ++i;
            token = strtok(NULL, " \n");
        }   
        args_array[i] = NULL;                       // Last index NULL for terminator 


    // Check commands
        //internal checks

        if(strcmp(args_array[0], "exit") == 0){     // compare strings, returns difference. If command is exit; close shell
            exit(0);
        }
        if(strcmp(args_array[0], "cd") == 0){       // Compares strings, if command is cd should be an internal syscall
            if(chdir(args_array[1])==-1){
                perror("Error: ");
            }
        } 

        //create child process
        int id = fork();           
        if(id==0){                                   // Child process calls exec
            execvp(args_array[0], args_array);
            exit(0);                                 // if child process exec fails, exit(0) (fixes multiple exit input error)
        } else 
            wait(NULL);                             // Parent waits for it
        
    
    }

}



