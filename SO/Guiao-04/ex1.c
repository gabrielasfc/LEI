#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    int stdout_fd = dup(1);

    dup2(ifd, 0); close(ifd);
    dup2(ofd, 1); close(ofd);
    dup2(efd, 5); close(efd);

    write(stdout_fd, "terminei\n", 9);

    return 0;
}