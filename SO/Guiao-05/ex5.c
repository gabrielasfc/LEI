#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pipe_fd[2]; pipe(pipe_fd);

    if (fork() == 0){
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);

        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        _exit(0);
    }
    wait(NULL);

    int pipe2_fd[2]; pipe(pipe2_fd);

    if (fork() == 0){
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        close(pipe2_fd[0]);
        dup2(pipe2_fd[1], 1);
        close(pipe2_fd[1]);

        execlp("cut", "cut", "-f7", "-d:", NULL);
        _exit(0);
    }
    wait(NULL);
    close(pipe_fd[0]); close(pipe_fd[1]);

    int pipe3_fd[2]; pipe(pipe3_fd);

    if (fork() == 0){
        close(pipe2_fd[1]);
        dup2(pipe2_fd[0], 0);
        close(pipe2_fd[0]);

        close(pipe3_fd[0]);
        dup2(pipe3_fd[1], 1);
        close(pipe3_fd[1]);

        execlp("uniq", "uniq", NULL);
        _exit(0);
    }
    wait(NULL);
    close(pipe2_fd[0]); close(pipe2_fd[1]);

    if (fork() == 0){
        close(pipe3_fd[1]);
        dup2(pipe3_fd[0], 0);
        close(pipe3_fd[1]);

        execlp("wc", "wc", "-l", NULL);
        _exit(0);
    }
    wait(NULL);
    close(pipe3_fd[0]); close(pipe3_fd[1]);

    return 0;
}