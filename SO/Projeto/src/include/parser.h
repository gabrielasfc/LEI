#ifndef PARSER_
#define PARSER_

#include "request.h"

void interpret_transform(char *line, int bytes_read, int max_transfs[]);
Request parse_args(int argc, char* argv[]);
ssize_t readln(int fd, char *line, size_t size);

#endif