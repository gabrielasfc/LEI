#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int i, status;

    for (i=1; i<=10; i++){
        int pid = fork();

        if (pid == 0){
            printf("\nPID: %d\n", getpid());
            printf("PID do pai : %d\n", getppid());
            _exit(i);
        }
    }

    for (i=1; i<=10; i++){
        wait(&status);
        printf("Código de saída do processo : %d\n", WEXITSTATUS(status));
    }

    return 0;
}
