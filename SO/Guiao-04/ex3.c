#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    dup2(ifd, 0); close(ifd);
    dup2(ofd, 1); close(ofd);
    dup2(efd, 5); close(efd);

    if (fork() == 0){
        execlp("wc", "wc", NULL);
        _exit(0);
    }
    wait(NULL);

    return 0;
}