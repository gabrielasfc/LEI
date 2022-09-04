#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (fork() == 0){
        if (execl("/bin/ls", "/bin/ls", "-l", NULL) < 0) perror("error on exec");
        _exit(0);
    }

    wait(NULL);

    return 0;
}