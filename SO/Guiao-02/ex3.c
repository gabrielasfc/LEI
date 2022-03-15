#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int i;

    for (i=1; i<=10; i++){
        int pid = fork();

        if (pid == 0){
            printf("\nPID: %d\n", getpid());
            printf("PID do pai : %d\n", getppid());
            _exit(i);
        }
        else{
            int status;
            wait(&status);
            printf("Child pid finished: %d; status code: %d\n", finished_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
