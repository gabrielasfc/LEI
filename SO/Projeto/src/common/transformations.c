#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/transformations.h"
#include "../include/logger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


void single_transformation(char *input_file, char *output_file, char *transforms, char *transf_path){
    int fd_input = open(input_file, O_RDONLY);
    if (fd_input > 0) log_info("Input file opened successfully\n");
    int fd_output = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0640);
    if (fd_output > 0) log_info("Output file opened successfully\n");

    dup2(fd_input, 0);
    dup2(fd_output, 1);

    close(fd_input);
    close(fd_output);


    char exec_path[100] = "";
    strcat(exec_path, transf_path);

    if(transforms[0] == 1){ strcat(exec_path, "/nop"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 2) { strcat(exec_path, "/bcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 3) { strcat(exec_path, "/bdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 4) { strcat(exec_path, "/gcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 5) { strcat(exec_path, "/gdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 6) { strcat(exec_path, "/decrypt"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[0] == 7) { strcat(exec_path, "/encrypt"); execlp(exec_path, exec_path, NULL);}

}


void initial_transformation(char *input_file, int i, char *transforms, char *transf_path, int transf_pipe[]){
    int fd_input = open(input_file, O_RDONLY);

    dup2(fd_input, 0);
    close(fd_input);

    close(transf_pipe[0]);
    dup2(transf_pipe[1], 1);
    close(transf_pipe[1]);


    char exec_path[100] = "";
    strcat(exec_path, transf_path);

    if(transforms[i] == 1){ strcat(exec_path, "/nop"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 2) { strcat(exec_path, "/bcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 3) { strcat(exec_path, "/bdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 4) { strcat(exec_path, "/gcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 5) { strcat(exec_path, "/gdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 6) { strcat(exec_path, "/decrypt"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 7) { strcat(exec_path, "/encrypt"); execlp(exec_path, exec_path, NULL);}
}


void middle_transformation(int i, char *transforms, char *transf_path, int transf_pipe1[], int transf_pipe2[]){
    close(transf_pipe1[1]);
    dup2(transf_pipe1[0], 0);
    close(transf_pipe1[0]);

    close(transf_pipe2[0]);
    dup2(transf_pipe2[1], 1);
    close(transf_pipe2[1]);     


    char exec_path[100] = "";
    strcat(exec_path, transf_path);

    if(transforms[i] == 1){ strcat(exec_path, "/nop"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 2) { strcat(exec_path, "/bcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 3) { strcat(exec_path, "/bdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 4) { strcat(exec_path, "/gcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 5) { strcat(exec_path, "/gdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 6) { strcat(exec_path, "/decrypt"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 7) { strcat(exec_path, "/encrypt"); execlp(exec_path, exec_path, NULL);}
}


void final_transformation(char *output_file, int i, char *transforms, char *transf_path, int transf_pipe[]){
    int fd_output = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0640);
    if (fd_output > 0) log_info("Output file opened successfully\n");
    dup2(fd_output, 1);
    close(fd_output);

    close(transf_pipe[1]);
    dup2(transf_pipe[0], 0);
    close(transf_pipe[0]);


    char exec_path[100] = "";
    strcat(exec_path, transf_path);

    if(transforms[i] == 1){ strcat(exec_path, "/nop"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 2) { strcat(exec_path, "/bcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 3) { strcat(exec_path, "/bdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 4) { strcat(exec_path, "/gcompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 5) { strcat(exec_path, "/gdecompress"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 6) { strcat(exec_path, "/decrypt"); execlp(exec_path, exec_path, NULL);}
    else if(transforms[i] == 7) { strcat(exec_path, "/encrypt"); execlp(exec_path, exec_path, NULL);}
}