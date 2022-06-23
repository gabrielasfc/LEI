#include "include/request.h"
#include "include/logger.h"
#include "include/pipe.h"
#include "include/parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define INFO_FIFO "tmp/INFO"
#define REQUEST_FIFO "tmp/REQUEST"

int main(int argc, char* argv[]){
    log_info("Opening INFO fifo ...");
    int info_fd = open_fifo(INFO_FIFO, 1);
    if(info_fd == -1) return -1;

    log_info("Opening REQUEST fifo ...");
    int req_fd = open_fifo(REQUEST_FIFO, 1);
    if (req_fd == -1) return -1;

    int my_id = getpid();
    char* pipe_name = malloc(10);
    sprintf(pipe_name, "tmp/%d", my_id);
    create_fifo(pipe_name); // Pipe onde o cliente recebe as respostas

    if (strcmp(argv[1], "proc-file") == 0){
        // Criar o pedido
        Request req = parse_args(argc, argv);

        int info = -1;
        write(info_fd, &info, sizeof(int)); // Aviso de que um pedido vai a caminho

        write(req_fd, req, sizeof(struct request)); // Envio do pedido

        int client_fd = open_fifo(pipe_name, 0);
        int client_fd_write = open_fifo(pipe_name, 1);

        int message;
        int flag = 1;
        for(int i=0; i<3 && flag; i++){
            read(client_fd, &message, sizeof(int));
            switch (message){
                case 1  : write(1, "pending\n", 9); break;
                case 2  : write(1, "processing\n", 12); break;
                case 3  : write(1, "concluded", 10); break;
                case -1 : write(1, "pedido inválido\n", 18); flag = 0; break;
            }
        }

        if(flag){
            int bytes_read, bytes_written;
            read(client_fd, &bytes_read, sizeof(int));
            read(client_fd, &bytes_written, sizeof(int));

            char buffer_read[20];
            char buffer_written[20];
            sprintf(buffer_read, "%d", bytes_read);
            sprintf(buffer_written, "%d", bytes_written);

            write(1, " (bytes-input: ", 16);
            write(1, buffer_read, strlen(buffer_read));
            write(1, ", bytes-output: ", 17);
            write(1, buffer_written, strlen(buffer_written));
            write(1, ")\n\n", 2);
        }

        free(req);
        close(client_fd);
        close(client_fd_write);
    }
    else if (strcmp(argv[1], "status") == 0){
        write(info_fd, &my_id, sizeof(int));

        log_info("Opening CLIENT fifo on client ...");
        int client_fd = open_fifo(pipe_name, 0);

        char* message = malloc(10000);
        ssize_t bytes_read = read(client_fd, message, 10000);
        write(1, message, bytes_read);
        
        free(message);
        close(client_fd);
    }

    close(info_fd);
    close(req_fd);

    delete_fifo(pipe_name);
    free(pipe_name);
    
}