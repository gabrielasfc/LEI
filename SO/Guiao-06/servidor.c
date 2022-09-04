#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (mkfifo("fifo2", 0666) < 0){
        perror("error on creating fifo");
    }

    int fifo_fd = open("fifo2", O_RDONLY);

    if (fifo_fd < 0){
        perror("error on opening fifo");
        return 1;
    }

    int output_fd = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0640);

    int buffer[1024];
    int bytes;

    while(1){ //server should never die
        while ((bytes = read(fifo_fd, buffer, 1024)) > 0){
            write(output_fd, buffer, bytes);
        }
    }
    close(fifo_fd); close(output_fd);
    unlink("fifo2");

    return 0;
}