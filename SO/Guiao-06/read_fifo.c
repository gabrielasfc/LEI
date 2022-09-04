#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int fifo_fd = open("fifo", O_RDONLY);
    char buffer[1024];
    int bytes;

    if (fifo_fd < 0){
        perror("error on opening fifo");
        return 1;
    }

    printf("writing...\n");

    while ((bytes = read(fifo_fd, buffer, 1024)) > 0){
        write(1, buffer, bytes);
    }
    close(fifo_fd);
    unlink("fifo");

    return 0;
}