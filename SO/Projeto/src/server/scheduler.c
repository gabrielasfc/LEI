#include "../include/scheduler.h"
#include "../include/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void update_transf_array(int* curr_transf_arr, char* request_transf){
    while (*request_transf){
        curr_transf_arr[*request_transf-1]++;
        request_transf++;
    }
}

void print_transf_array(int* curr_transf_arr, int* max_transf_arr){
    for(int i=0; i<7; i++){
        printf("%d out of %d\n", curr_transf_arr[i], max_transf_arr[i]); fflush(stdout);
    }
}

char* get_server_status(Request* curr_requests, int num_requests, int* curr_transfs, int* max_transfs){
    char* server_status = malloc(10000); *server_status = '\0';

    for(int i=0; i<num_requests; i++){
        char* request_str = malloc(1000);
        sprintf(request_str, "task #%d: proc-file %d %s %s %s\n", curr_requests[i]->task_number, curr_requests[i]->priority, curr_requests[i]->input_file, curr_requests[i]->output_file, transforms_to_string(curr_requests[i]->transforms));
        strcat(server_status, request_str);
        free(request_str);
    }

    for(int i=0; i<7; i++){
        char* transf_status = malloc(100);
        if(i == 0) sprintf(transf_status, "transf nop: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 1) sprintf(transf_status, "transf bcompress: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 2) sprintf(transf_status, "transf bdecompress: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 3) sprintf(transf_status, "transf gcompress: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 4) sprintf(transf_status, "transf gdecompress: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 5) sprintf(transf_status, "transf encrypt: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        if(i == 6) sprintf(transf_status, "transf decrypt: %d/%d (running/max)\n", curr_transfs[i], max_transfs[i]);
        strcat(server_status, transf_status);
        free(transf_status);
    }

    char* newline = "\n"; strcat(server_status, newline);
    return server_status;
}

int check_update_conc_operation(Request r, int* curr_tranfs, int* max_transfs){
    int* old_curr_transfs = malloc(7*sizeof(int)); //free
    char* transformations = r->transforms;
    int flag = 1;

    for(int i=0; i<7; i++) // Guarda uma cópia do buffer inicial
        old_curr_transfs[i] = curr_tranfs[i];

    while (*transformations && flag){
        if (++curr_tranfs[*transformations-1] > max_transfs[*transformations-1]) flag = 0;
        transformations++;
    }

    if (flag == 0){
        // Guarda uma cópia do buffer inicial
        for(int i=0; i<7; i++){
            curr_tranfs[i] = old_curr_transfs[i];
        }
    }
    free(old_curr_transfs);
    return flag;
}


int check_exceed_transformations(Request r, int *max_transfs){
    char *transforms = r->transforms;
    int req_transforms[7] = {0};

    for(int i = 0; i < strlen(transforms); i++){
       req_transforms[transforms[i]-1]++;
    }

    int flag = 1;
    for(int i = 0; i < 7 && flag; i++){
        if(req_transforms[i] > max_transfs[i]) flag = 0;
    }

    return flag;
}


void remove_request(Request r, Request* curr_requests, int* num_requests, int* curr_transfs){
    int i;
    for(i=0; i<(*num_requests); i++){
        if (curr_requests[i]->id == r->id){
            free(curr_requests[i]);
            break;
        }
    }
    while (i<(*num_requests)){
        curr_requests[i] = curr_requests[i+1]; // Shift -left
        i++;
    }

    char* transformations = r->transforms;
    while (*transformations){
        curr_transfs[*transformations-1]--;
        transformations++;
    }
    
    (*num_requests)--;
}