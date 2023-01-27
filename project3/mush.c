#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc,char *argv[]){

    for(int i=0; i<argc; i++){
        printf("%s \n", argv[i]);
    }

    // Begin with the main loop. For now, just have it go forever.
    while(1){
        printf("$\n");
        char buf[8];
        while(fgets(buf, sizeof buf, tmpf) != NULL)
            printf("\"%s\n", buf);
    }

    // You should print a prompt, read a line (fgets()), and then parse it down to individual words (strtok()).
    // I suggest you stop here and test everything to make sure it's working as expected.
    // Put those words in an array of char*s. Be sure to terminate the array with a NULL so you can pass it easily to execvp().
    // I suggest you stop here as well, and make sure the array is built as you expected. It's easier to debug small bits at a time than the whole thing at once.
    // Call execvp() with your array. Pass the 0th element as the first argument ot execvp().


    return 0;
}