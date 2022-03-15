#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>


void procura(int m[10][50], int val, int ret[10]){
    int i, j;
    int status = 0;

    for (i=0; i<10; i++){
        int pid = fork();
        if (pid == 0){
            for (j=0; j<50; j++){
                if (m[i][j] == val){
                    status = i;
                   _exit(status);
                }
            }
            _exit(status);
        }
    }

    for (i=0; i<10; i++){
        wait(&status);
        ret[i] = status;
    }
}


int compare_fnc(const void *a, const void *b){
    return *(int *)a - *(int *)b;
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

    int lines_found[10];

    procura(m, val, lines_found);

    qsort(lines_found, 10, sizeof(int), compare_fnc);

    int found = 0;

    for (i=0; i<10; i++){
        if (lines_found[i] != 0){
            printf("Linha %d\n", i);
            found = 1;
        }
    }
    if (found == 0) printf("O elemento %d não foi encontrado\n", val);

    return 0;
}
