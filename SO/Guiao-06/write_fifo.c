#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int fifo_fd = open("fifo", O_WRONLY);
    char buffer[1024];
    int bytes;

    if (fifo_fd < 0){
        perror("error on opening fifo");
        return 1;
    }

    printf("fifo is open\n");

    printf("writing...\n");

    while ((bytes = read(0, buffer, 1024)) > 0){
        write(fifo_fd, buffer, bytes);
    }
    close(fifo_fd);

    return 0;
}