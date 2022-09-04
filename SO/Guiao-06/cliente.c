#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fifo_fd = open("fifo2", O_WRONLY);

    if (fifo_fd < 0){
        perror("error on opening fifo");
        return 1;
    }

    for (int i=1; i < argc; i++){
        write(fifo_fd, argv[i], strlen(argv[i]));
        write(fifo_fd, "\n", 1);
    }

    return 0;
}