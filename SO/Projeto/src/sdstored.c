#include "include/request.h"
#include "include/logger.h"
#include "include/queue.h"
#include "include/scheduler.h"
#include "include/pipe.h"
#include "include/parser.h"
#include "include/transformations.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INFO_FIFO "tmp/INFO"
#define REQUEST_FIFO "tmp/REQUEST"

int is_closed = 0;
int info_fd_global;

void sigterm_handler(int signum){
    int info = -1;
    write(info_fd_global, &info, sizeof(int));
    delete_fifo(REQUEST_FIFO);

    is_closed = 1;
}

int main(int argc, char* argv[]){
    signal(SIGTERM, sigterm_handler); 

    int max_transfs[7];
    int tasks_count = 1;
    char *config_path = argv[1];
    char *transf_path = argv[2];

    // Leitura do ficheiro de configuração
	int fd_config = open(config_path, O_RDONLY), bytes_read;
	char buffer[1024];
	while((bytes_read = readln(fd_config, buffer, 1024)) > 0){
		interpret_transform(buffer, bytes_read, max_transfs);
	}
    close(fd_config);

    log_info("Creating INFO fifo for both processes ...");
    create_fifo(INFO_FIFO);

    log_info("Creating REQUEST fifo on proc 1 ...");
    create_fifo(REQUEST_FIFO);

    // Para não bloquear a abertura do fifo
    if (fork() == 0){
        open_fifo(INFO_FIFO, 1);
        open_fifo(REQUEST_FIFO, 1);
        _exit(0);
    }

    log_info("Opening INFO fifo on proc 1");
    int info_fd1 = open_fifo(INFO_FIFO, 0);
    int info_fd2 = info_fd_global = open_fifo(INFO_FIFO, 1);

    log_info("Opening REQUEST fifo on proc 1 ...");
    int req_fd = open_fifo(REQUEST_FIFO, 0);
    
    int send_request_fd[2];
    log_info("Creating send_request pipe for both processes ...");
    create_pipe(send_request_fd);

    int send_concluded_request_fd[2];
    log_info("Creating send_concluded_request pipe for both processes ...");
    create_pipe(send_concluded_request_fd);


    int curr_transfs[7] = {0};
    Request* curr_requests = malloc(100*sizeof(struct request));
    int num_conc_requests = 0;
    PriorityQueue pq = initQueue();


    if (fork() == 0){
        close(send_request_fd[1]);
        close(send_concluded_request_fd[0]);
        close(info_fd1);
        close(req_fd);

        Request req = malloc(sizeof(struct request));
        
        log_info("Opening INFO fifo on proc 2");
    
        while (read(send_request_fd[0], req, sizeof(struct request)) > 0){
            if (fork() == 0){
                log_info("\n\nNovo pedido para entrar nas transformações ....\n");

                if(strlen(req->transforms) == 1){
                    if(fork() == 0){
                        single_transformation(req->input_file, req->output_file, req->transforms, transf_path);
                        _exit(0);
                    }
                    wait(NULL);
                }
                else{
                    int nr_pipes = strlen(req->transforms) - 1;
                    int nr_transfs = strlen(req->transforms);
                    int transf_pipe[nr_pipes][2];

                    for(int i = 0; i < nr_transfs; i++){
                        if(i==0){
                            pipe(transf_pipe[0]);

                            if(fork() == 0){
                                initial_transformation(req->input_file, i, req->transforms, transf_path, transf_pipe[0]);
                                
                                _exit(0);
                            }
                        }
                        else if(i==nr_pipes){
                            if(fork() == 0){
                                final_transformation(req->output_file, i, req->transforms, transf_path, transf_pipe[i-1]);

                                _exit(0);
                            }
                            close(transf_pipe[i-1][0]); close(transf_pipe[i-1][1]);
                        }
                        else{
                            pipe(transf_pipe[i]);

                            if(fork() == 0){
                                middle_transformation(i, req->transforms, transf_path, transf_pipe[i-1], transf_pipe[i]);

                                _exit(0);
                            }
                            close(transf_pipe[i-1][0]); close(transf_pipe[i-1][1]);
                        }    
                    }
                    
                    for(int i = 0; i < nr_transfs; i++){
                        wait(NULL);
                    }
                }
            
                int info = -2;
                write(info_fd2, &info, sizeof(int));

                write(send_concluded_request_fd[1], req, sizeof(struct request));

                _exit(0);
            }
        }

        _exit(0);
    }

    close(send_request_fd[0]);
    close(send_concluded_request_fd[1]);
    
    int info;
    while (is_closed == 0 || num_conc_requests > 0){
        read(info_fd1, &info, sizeof(int));

        if (info == -1 && is_closed == 0){ // Recebe pedido e envia para a fila
            log_info("Received new request");

            Request req = malloc(sizeof(struct request));
            read(req_fd, req, sizeof(struct request));

            char* client_id = malloc(10);
            sprintf(client_id, "tmp/%d", req->id);

            log_info("Opening 1CLIENT fifo on proc 1");
            req->fd = open_fifo(client_id, 1);

            free(client_id);

            if(!check_exceed_transformations(req, max_transfs)){
                int message = -1;
                write(req->fd, &message, sizeof(int));
                
                close(req->fd);
                free(req);
                continue;
            }

            if (pq->size == 0 && check_update_conc_operation(req, curr_transfs, max_transfs)){ // Caso transf esteja disponível e queue esteja vazia 
                req->task_number = tasks_count++;
                write(send_request_fd[1], req, sizeof(struct request));
                curr_requests[num_conc_requests++] = req;

                int message = 1;
                write(req->fd, &message, sizeof(int));

                message = 2;
                write(req->fd, &message, sizeof(int));
                close(req->fd); // Para n esgotar o nº de ficheiros abertos
            }
            else { // Caso transf estejam cheias ou queue não vazia
                log_info("Request not immediatly forwarded\n");

                enqueue(pq, req);
                
                int message = 1;
                write(req->fd, &message, sizeof(int));
                close(req->fd);

                Request req = dequeue(pq);

                if(check_update_conc_operation(req, curr_transfs, max_transfs)){
                    req->task_number = tasks_count++;
                    write(send_request_fd[1], req, sizeof(struct request));
                    curr_requests[num_conc_requests++] = req;

                    char* client_id = malloc(10);
                    sprintf(client_id, "tmp/%d", req->id);

                    log_info("Opening CLIENT fifo on proc 1");
                    req->fd = open_fifo(client_id, 1);

                    free(client_id); 

                    message = 2;
                    write(req->fd, &message, sizeof(int));
                    close(req->fd);
                }
                else{ 
                    enqueue(pq, req);
                }
            }
        }
        else if (info == -1 && is_closed == 1){ 
            log_warning("Servidor já não recebe mais pedidos\n");
        }
        else if (info == -2){
            // Recebe pedido que terminou
            Request req = malloc(sizeof(struct request));
            read(send_concluded_request_fd[0], req, sizeof(struct request));

            log_info("Este pedido já terminou ....\n\n");

            char* client_id = malloc(10);
            sprintf(client_id, "tmp/%d", req->id);

            log_info("Opening CLIENT fifo on proc 1");
            req->fd = open_fifo(client_id, 1);

            free(client_id); 

            int message = 3;
            write(req->fd, &message, sizeof(int));

            int input = open(req->input_file, O_RDONLY);
            int output = open(req->output_file, O_RDONLY);

            int bytes_read = lseek(input, 0, SEEK_END);
            int bytes_written = lseek(output, 0, SEEK_END);

            close(input);
            close(output);

            write(req->fd, &bytes_read, sizeof(int));
            write(req->fd, &bytes_written, sizeof(int));

            // Atualiza o estado do curr_transfs
            remove_request(req, curr_requests, &num_conc_requests, curr_transfs); 
            
            close(req->fd);
            free(req);
            // Vai buscar o que está no início da fila e vê se consegue entrar
            int flag = 1;

            while (pq->size != 0 && flag){
                Request req = dequeue(pq);
            
                if (check_update_conc_operation(req, curr_transfs, max_transfs) == 1){ // Caso transf esteja disponível
                    req->task_number = tasks_count++;
                    write(send_request_fd[1], req, sizeof(struct request));
                    curr_requests[num_conc_requests++] = req;
                    
                    char* client_id = malloc(10);
                    sprintf(client_id, "tmp/%d", req->id);

                    log_info("Opening CLIENT fifo on proc 1");
                    req->fd = open_fifo(client_id, 1);

                    free(client_id); 

                    int message = 2;
                    write(req->fd, &message, sizeof(int));
                    close(req->fd);
                }
                else {
                    enqueue(pq, req); 
                    flag = 0;
                }
            }
            if (pq->size == 0 && is_closed == 1) {
                close(send_request_fd[1]);
            }
        }
        else { // Recebe pedido de status
            log_info("Received status request");
            char* status = get_server_status(curr_requests, num_conc_requests, curr_transfs, max_transfs);

            char* client_id = malloc(10);
            sprintf(client_id, "tmp/%d", info);

            log_info("Opening INFO fifo on proc 1");
            int client_fd = open_fifo(client_id, 1);

            write(client_fd, status, strlen(status)); // Alterar
            close(client_fd);

            free(status);
            free(client_id);
        }
    }

    close(send_concluded_request_fd[0]);
    close(send_request_fd[1]);

    free(curr_requests);

    log_info("Deleting INFO fifo...");
    delete_fifo(INFO_FIFO);
}
