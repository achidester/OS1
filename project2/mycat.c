#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd;
    char buffer[2048];
    ssize_t bytes_read;

    if(argc < 2){
        fd = 0;
    }
    else{
        for(int i=1; i<argc; i++){
            fd = open(argv[i], O_RDONLY);
            if(fd==-1){
                perror(argv[i]);
                return 1;
            }
        }
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1){
        perror("read");
        return 1;
    }

    close(fd);
    return 0;
}