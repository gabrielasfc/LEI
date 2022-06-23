#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>


Request parse_args(int argc, char* argv[]){
    int i = 2;

    int priority;
    if (!strcmp(argv[2],"-p") && argv[3][0] - 48 <= 5){
        // Foi passada uma prioridade
        priority = atoi(argv[3]);
        i+=2; 
    }
    else {
        // Prioridade padrão = 0
        priority = 0;
    }
    i += 2;
    int j = i;
    char* transformations = malloc(argc-i+1);    
    // Guardar os identificadores das transformações    
    while (i < argc){
        transformations[i-j] = interpret_trans(argv[i]);
        i++;
    }
    transformations[i-j] = '\0';
    // Criar o pedido
    int ind;
    if(!strcmp(argv[2], "-p")) ind = 4;
    else ind = 2;

    Request req = create_request(getpid(), priority, argv[ind], argv[ind+1], transformations);
    free(transformations);
    return req;
}

ssize_t readln(int fd, char *line, size_t size){
    int i;

    for(i = 0; i < size && read(fd, &line[i], 1) > 0; i++){ 
        if(line[i] == '\n') {i++; break;}
    }

    return i;
}

void interpret_transform(char *line, int bytes_read, int max_transfs[]){
    int i = 0;
    char buffer[20];

    while(i < bytes_read && *line != ' '){
        buffer[i] = *line;
        line++;
        i++;
    }
    buffer[i] = '\0';
    line++;

    int qnt = (*line) - 48;
    
    //0 - NOP; 1 - BCOMPRESS; 2 - BDECOMPRESS; 3 - GCOMPRESS; 4 - GDECOMPRESS; 5 - ENCRYPT; 6 - DECRYPT
    if(strcmp(buffer, "nop") == 0){
        max_transfs[0] = qnt;
    }
    else if(strcmp(buffer, "bcompress") == 0){
        max_transfs[1] = qnt;
    }
    else if(strcmp(buffer, "bdecompress") == 0){
        max_transfs[2] = qnt;
    }
    else if(strcmp(buffer, "gcompress") == 0){
        max_transfs[3] = qnt;
    }
    else if(strcmp(buffer, "gdecompress") == 0){
        max_transfs[4] = qnt;
    }
    else if(strcmp(buffer, "encrypt") == 0){
        max_transfs[5] = qnt;
    }
    else if(strcmp(buffer, "decrypt") == 0){
        max_transfs[6] = qnt;
    }

}

