#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigalrm_handler(int signum){
    kill(0, SIGABRT);
}

int main(int argc, char* argv[]){
    int n_files = argc-2;
    char *files[n_files];
    int pid;
    int pids[n_files]; // array com os ids dos processos

    for (int i=0; i < n_files; i++){
        files[i] = argv[i+2];
    }

    for (int i=0; i < n_files; i++){
        alarm(10);
        
        if (signal(SIGALRM, sigalrm_handler) == SIG_ERR){
            printf("error on sigalrm\n");
            return 1;
        }

        if ((pid = fork()) == 0){
            pids[i] = pid;

            if (execlp("grep", "grep", argv[1], files[i], NULL) < 0) _exit(-1);
        }
    }
    
    int found = 0;

    for (int i=0; i < n_files && !found; i++){
        int status;
        wait(&status);

        if (WEXITSTATUS(status) == 0){
            for (int j=0; j < n_files; j++){
                kill(pids[j], SIGKILL);
            }
            found = 1;
        }
    }

    return 0;
}
