#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>

int main(/* int argc,char *argv[] */ ){

    const int ALLOWED_WORDS = 128;
    const int BUFFER =  2048;

    printf("$");

    char input[BUFFER];
    char *args_array[ALLOWED_WORDS]; 
    fgets(input, sizeof input, stdin);
    // printf("fgets got: %s", input);     // sanity check

    int i = 0;                  
    char *token = strtok(input, " ");
    // printf("%d: [%p] ---- %s\n", i, token, token);     // sanity check 

    while(token != NULL && i < ALLOWED_WORDS){          // adding tokens to a char* array (p1.3)
        args_array[i] = token;                        
        ++i;
        token = strtok(NULL, " ");
        // printf("%d: [%p] ---- %s\n", i, token, token);  // sanity check
    }   

    args_array[i] = NULL; 
    

    for(i = 0; i < ALLOWED_WORDS; ++i){       //sanity check
        printf("%s ", args_array[i]);
    }



}

    
    // Put those words in an array of char*s. Be sure to terminate the array with a NULL so you can pass it easily to execvp().
    // I suggest you stop here as well, and make sure the array is built as you expected. It's easier to debug small bits at a time than the whole thing at once.
    // Call execvp() with your array. Pass the 0th element as the first argument ot execvp().

