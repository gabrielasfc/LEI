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
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", NULL);

        _exit(0);
    }
    
    close(pipe_fd[0]);

    int bytes_read;
    char buf[5];

    while ((bytes_read = read(0, buf, 5)) > 0){
        write(pipe_fd[1], buf, bytes_read);
    }
    
    close(pipe_fd[1]);

    wait(NULL);

    return 0;
}
