#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"


int main(int argc, char const* argv[]){

    if (argc != 2){
        printf("Numero de argumentos invalido\n");
        return 1;
    }

    if (!strcmp(argv[1], "exercicio-1") || 
       (!strcmp(argv[1], "exercicio-2") && 
           (access("saida/users-ok.csv", F_OK) || access("saida/repos-ok.csv", F_OK) != 0 || access("saida/commits-ok.csv", F_OK) != 0))){
        exercicio1();
    }
        
    if(!strcmp(argv[1], "exercicio-2")){
        exercicio2();
    }
}