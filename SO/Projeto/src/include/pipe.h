#ifndef PIPE_
#define PIPE_

int create_fifo(char* name);
int open_fifo(char* name, int mode);
int delete_fifo(char* name);
int create_pipe(int fds[2]);

#endif