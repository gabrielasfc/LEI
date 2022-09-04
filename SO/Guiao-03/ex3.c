#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    for (int i=1; i < argc; i++){
        if (fork() == 0){
            execlp(argv[i], argv[i], NULL);
            _exit(0);
        }
    }

    for (int i=1; i < argc; i++) wait(NULL);

    return 0;
}
