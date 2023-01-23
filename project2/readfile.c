#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[]){

    int fd = open(argv[1], O_RDONLY);
    char buffer[2048];
    size_t bytes_read;

    if(argc < 2){
        perror("please provide a file \n");
        return 1;
    }

    if(fd == -1){
        perror("open failed \n");
        return 1;
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytes_read);
    }
    
    close(fd);

    return 0;
}