#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int agrc, char *argv[]){
    int pid;

    pid = fork();

    if (pid == 0){
        printf("PID: %d\n", getpid());
        printf("PID do pai: %d\n", getppid());
        _exit(5);
    }
    else{
        int status;
        int finished_pid;
        printf("Child PID: %d\n", pid);
        printf("PID: %d\n", getpid());
        printf("PID do pai: %d\n", getppid());

        finished_pid = wait(&status);
        if (WIFEXITED(status)){
            printf("Child pid finished: %d; status code: %d\n", finished_pid, WEXITSTATUS(status));
        }
        else printf("error: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
