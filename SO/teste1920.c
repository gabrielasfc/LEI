#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


char* get_regiao(char *line){
    int count_espaco = 0;
    char inteiro[5];
    
    for (int i=0, j=0; line[i] != '\0'; i++){
        if (line[i] == ' ') count_espaco++;
        if (count_espaco == 2){
            inteiro[j] = line[i];
            j++;
        }
    }
    
    return inteiro;
}


int vacinados(char* regiao, int idade){
    int fd_pipe[2];
    if (pipe(fd_pipe) < 0){
        perror("error on creating pipe1");
        return 1;
    }

    if (fork() == 0){
        close(fd_pipe[0]);
        dup2(fd_pipe[1], 1); close(fd_pipe[1]);

        char *idade_arg = malloc(5);
        sprintf(idade_arg, "%d", idade);

        execlp("grep", "grep", idade_arg, regiao, NULL);

        _exit(0);
    }

    int fd_pipe2[2];
    if (pipe(fd_pipe2) < 0){
        perror("error on creating pipe2");
        return 1;
    }

    if (fork() == 0){
        close(fd_pipe2[0]);
        dup2(fd_pipe2[1], 1); close(fd_pipe2[1]);

        close(fd_pipe[1]);
        dup2(fd_pipe[0], 0); close(fd_pipe[0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }

    close(fd_pipe2[1]);
    close(fd_pipe[0]); close(fd_pipe[1]);

    wait(NULL); wait(NULL);

    char *buffer[5];
    read(fd_pipe2[0], buffer, 5);
    
    close(fd_pipe2[0]);

    return atoi(buffer);
}


bool vacinado(char* cidadao){
    int pid[10];
    for (int i=0; i < 9; i++){
        if ((pid[i] = fork()) == 0){
            char ficheiro[1];
            sprintf(ficheiro, "%d", i);

            execlp("grep", "grep", cidadao, ficheiro, NULL);
        }
    }

    bool ret = false;
    for (int i=0; i < 9 && !ret; i++){
        int status;
        wait(&status);

        if (WEXITSTATUS(status) == 0){
            ret = true;
            for (int j=0; j < 9; j++){
                kill(pid[j], SIGKILL);
            }
        }
    }

    return ret;
}


int main(int argc, char* argv[]){
    mkfifo("fifo", 0666);

    int fd_fifo = open("fifo", O_RDONLY);

    while (1){
        char buffer[1024];
        int n_bytes = 0;
        while ((n_bytes = read(fd_fifo, buffer, 1024)) > 0){
            char *regiao = get_regiao(buffer);

            int fd_ficheiro = open(regiao, O_CREAT | O_APPEND | O_WRONLY, 0640); 

            write(fd_ficheiro, buffer, n_bytes);
            write(fd_ficheiro, "\n", 1);

            close(fd_ficheiro);
        }

    }

    close(fd_fifo);
    unlink("fifo");

    return 0;
}