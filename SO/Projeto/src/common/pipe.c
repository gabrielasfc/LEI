#include "../include/pipe.h"
#include "../include/logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_fifo(char* name){
    int r = mkfifo(name, 0666); // Criação do pipe

    if (r == -1){
        log_error("Error creating fifo\n");
        perror("\n");
    }
    else{
        log_info("Fifo created successfully\n");
    }
    return r;
}

int open_fifo(char* name, int mode){
    int fifo_fd;
    if (mode == 0){
        fifo_fd = open(name, O_RDONLY); // Abertura do pipe para leitura 
    }
    else if (mode == 1){
        fifo_fd = open(name, O_WRONLY); // Abertura do pipe para escrita
    }
    else if (mode == 2){
        fifo_fd = open(name, O_RDWR); // Abertura do pipe para leitura e escrita
    }

    if (fifo_fd == -1){
        log_error("Error opening fifo\n");
        perror("\n");
    }
    else{
        log_info("Fifo opened successfully\n");
    }
    return fifo_fd;
}

int delete_fifo(char* name){
    int r = unlink(name); // Elimina os pipes criados

    if (r == -1){
        log_error("Error deleting fifo\n");
        perror("\n");
    }
    else{
        log_info("Fifo deleted successfully\n");
    }
    return r;
}

int create_pipe(int fds[2]){
    int r = pipe(fds);

    if (r == -1){
        log_error("Error creating pipe\n");
        perror("\n");
    }
    else{
        log_info("Pipe created successfully\n");
    }
    return r;
}