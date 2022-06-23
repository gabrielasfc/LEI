#ifndef SCHEDULER_
#define SCHEDULER_

#include "request.h"

void update_transf_array(int* curr_transf_arr, char* request_transf);

void print_transf_array(int* curr_transf_arr, int* max_transf_arr);

char* get_server_status(Request* curr_requests, int num_requests, int* curr_transfs, int* max_transfs);

int check_update_conc_operation(Request r, int* curr_tranfs, int* max_transfs);

int check_exceed_transformations(Request r, int *max_transfs);

void remove_request(Request r, Request* curr_requests, int* num_requests, int* curr_transfs);

#endif