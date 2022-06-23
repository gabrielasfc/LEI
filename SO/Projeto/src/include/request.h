#ifndef REQUEST_
#define REQUEST_

#include <unistd.h>

typedef struct request {
	pid_t id;
	char priority;
	char input_file[100];
	char output_file[100];
	char transforms[20];
	int fd;
	int task_number;
} *Request;

char interpret_trans(char* transf);

char* transforms_to_string(char* transf);

void print_transforms(char* transforms);

Request create_request(pid_t id, char priority, char* input_file, char* output_file, char* transforms);

void print_request(Request r);

int read_request(int fd, Request r);

int write_request(int fd, Request r);


#endif
