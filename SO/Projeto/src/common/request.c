#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/request.h"

char interpret_trans(char* transf){
	if (strcmp(transf, "nop") == 0) return 1;
	else if (strcmp(transf, "bcompress") == 0) return 2;
	else if (strcmp(transf, "bdecompress") == 0) return 3;
	else if (strcmp(transf, "gcompress") == 0) return 4;
	else if (strcmp(transf, "gdecompress") == 0) return 5;
	else if (strcmp(transf, "decrypt") == 0) return 6;
	else if (strcmp(transf, "encrypt") == 0) return 7;
	else return 8;
}

char* transforms_to_string(char* transf){
	char* string_transforms = malloc(1000); *string_transforms = '\0';
	while (*transf){
		char t = *transf;
		switch(t){
			case 1: strcat(string_transforms, "nop "); break;
			case 2:	strcat(string_transforms, "bcompress "); break;
			case 3:	strcat(string_transforms, "bdecompress "); break;
			case 4:	strcat(string_transforms, "gcompress "); break;
			case 5:	strcat(string_transforms, "gdecompress "); break;
			case 6: strcat(string_transforms, "decrypt "); break;
			case 7: strcat(string_transforms, "encrypt "); break;
			default: break;
		}
		transf++;
	}
	return string_transforms;
}

void print_transforms(char* transforms){
	if (transforms == NULL) { return; }
	while (*transforms != '\0'){
		char t = *transforms;
		switch(t){
			case 1: printf("nop "); break;
			case 2:	printf("bcompress "); break;
			case 3:	printf("bdecompress "); break;
			case 4:	printf("gcompress "); break;
			case 5:	printf("gdecompress "); break;
			case 6: printf("decrypt "); break;
			case 7: printf("encrypt "); break;
			default: printf("Transf indevida"); break;
		}
		transforms++;
	} 


}

Request create_request(pid_t id, char priority, char* input_file, char* output_file, char* transforms){
	Request r = malloc(sizeof(struct request));
	r->id = id;
	r->priority = priority;
	
	strcpy(r->input_file, input_file);
	strcpy(r->output_file, output_file);

	if (transforms != NULL){
		strcpy(r->transforms, transforms);
	}
	else r->transforms[0] = '\0';

	return r;
}

void print_request(Request r){
	printf("Id: %d\nFd: %d\nPriority: %d\ninput_file: %s\noutput_file: %s\ntransforms: ", r->id, r->fd, r->priority, r->input_file, r->output_file);
	print_transforms(r->transforms);
	putchar('\n');


}

int write_request(int fd, Request r){
	write(fd, r, sizeof(struct request));
	return 0;
}

int read_request(int fd, Request r){
	ssize_t bytes_read = read(fd, r, sizeof(struct request));	
	return bytes_read;
}




