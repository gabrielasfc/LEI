#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_RDWR, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    int stdout_fd = dup(1);

    int fd_in = dup2(ifd, 0);
    close(ifd);
    int fd_out = dup2(ofd, 1);
    close(ofd);
    int fd_err = dup2(efd, 5);
    close(efd);

    if (fork() == 0){
        write(1, "teste", 5);

        char *buf = malloc(5);
        lseek(1, 0, SEEK_SET);
        read(1, buf, 5);

        write(stdout_fd, buf, 5);

        _exit(0);
    }
    wait(NULL);
}
