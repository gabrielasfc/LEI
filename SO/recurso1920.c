#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


int main(int argc, char *argv []){
    int n_args = argc-1;
    char *args[argc];
    int array[10] = {0};

    for (int j=1; j <= argc; j++){
        args[j-1] = argv[j];
    }

    for (int i=0; i < 9; i++){
        int fd_pipepai[2]; pipe(fd_pipepai);

        if (fork() == 0){
            execvp(argv[1], args);

            int fd_pipe[2]; pipe(fd_pipe);

            if (fork() == 0){ //grep
                close(fd_pipepai[0]); close(fd_pipepai[1]);

                close(fd_pipe[0]);
                dup2(fd_pipe[1], 1); close(fd_pipe[1]);

                int pid = getppid();
                char arg[25];
                sprintf(arg, "/proc/%d/memstats", pid);

                execlp("grep", "grep", "VmPeak", arg, NULL);

                _exit(0);
            }

            int fd_pipe2[2]; pipe(fd_pipe2);

            if (fork() == 0){
                close(fd_pipepai[0]); close(fd_pipepai[1]);

                close(fd_pipe[1]);
                dup2(fd_pipe[0], 0); close(fd_pipe[0]);

                close(fd_pipe2[0]);
                dup2(fd_pipe2[1], 1); close(fd_pipe2[1]);

                execlp("cut", "cut", "-d" "", "-f4", NULL);

                _exit(0);
            }

            close(fd_pipe[0]); close(fd_pipe[1]);
            close(fd_pipe2[1]);
            close(fd_pipepai[0]);

            wait(NULL); wait(NULL);

            char buffer[10];
            int n_bytes = read(fd_pipe2[0], buffer, 10);

            close(fd_pipe2[0]);

            write(fd_pipepai[1], buffer, n_bytes);

            close(fd_pipepai[1]);

            _exit(0); 
        }
        else{
            close(fd_pipepai[1]);
            wait(NULL);

            char buffer[10];
            read(fd_pipepai[0], buffer, 10);

            close(fd_pipepai[0]);
            array[i] = buffer;
        }
    }

    char *min = array[0];
    char *max = array[0];
    double media = 0;
    for (int i=0; i < 9; i++){
        if (atoi(array[i]) > atoi(max)) max = array[i];
        else if (atoi(array[i]) < atoi(min)) min = array[i];
        media += atoi(array[i]);
    }

    media = media / 10.0;

    write(1, "memoria :", 9); 
    write(1, min, strlen(min)); write(1, " ", 1);
    write(1, max, strlen(max)); write(1, " ", 1);

    char media_c[10];
    sprintf(media_c, "%d", media);

    write(1, media_c, strlen(media_c));

    return 0;
}


int is_closed = 0;
int seconds = 0;
int rounds = 0;
int pid = 0;

void sig_handler(int signum){
    is_closed = 1;

    char buffer[10];
    sprintf(buffer, "%d", rounds);
    write(1, buffer, strlen(buffer));
}

void sig_alarm(int signum){
    if (seconds >= 20) kill(pid, SIGKILL)

    seconds++;
    alarm(1);
}

int main(int argc, char *argv[]){
    signal(SIGINT, sig_handler);
    signal(SIGALRM, sig_alarm);

    while (!is_closed){
        if ((pid = fork()) == 0){
            for (int i=0; i < 100; i++){
                if (fork() == 0){
                    execlp("cmd", "cmd", NULL);

                    _exit(0);
                }
            }

            for (int i=0; i < 100; i++) wait(NULL);

            _exit(0);
        }
        else{
            alarm(1);
            wait(NULL);
            rounds++;
        }
    }
    return 0;
}