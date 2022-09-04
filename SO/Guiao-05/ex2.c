#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    int pipe_fd[2];

    if (pipe(pipe_fd) < 0){
        perror("pipe");
        return -1;
    }

    if (fork() == 0){
        close(pipe_fd[1]);
        int bytes_read;
        char buf[5];

        while ((bytes_read = read(pipe_fd[0], buf, 5)) > 0){
            write(1, buf, 5);
        }

        _exit(0);
    }

    close(pipe_fd[0]);
    write(pipe_fd[1], "teste", 5);
    close(pipe_fd[1]);

    wait(NULL);

    return 0;
}

