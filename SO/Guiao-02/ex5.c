#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


int procura(int m[10][50], int val){
    int i, j;
    int status = 0;

    for (i=0; i<10; i++){
        int pid = fork();
        if (pid == 0){
            for (j=0; j<50; j++){
                if (m[i][j] == val){
                   status = 1;
                   _exit(status);
                }
            }
            _exit(status);
        }
    }

    int ret = 0;
    for (i=0; i<10; i++){
        wait(&status);
        ret = ret || status;
    }

    return ret;
}


int main(int argc, char *argv[]){
    srand(time(NULL));
    int i, j;
    int m[10][50];

    for (i=0; i<10; i++){
        for (j=0; j<50; j++){
            m[i][j] = rand()%500;
        }
    }

    int val = atoi(argv[1]);

    int found = procura(m, val);

    printf("\nO elemento %d ", val);
    printf((found == 1) ? "foi": "não foi");
    printf(" encontrado\n\n");

    return 0;
}
