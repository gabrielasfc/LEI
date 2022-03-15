#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

//Lê um caracter de cada vez
ssize_t readln(int fd, char *line, size_t size){
    ssize_t i=0;
    for (; i < size && read(fd, &line[i], 1) > 0; i++){
        if (line[i] == '\n'){
            i++;
            break;
        }
    }
    return i;
}


int main(int agrc, char *argv[]){
    //1. open files
    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd < 0){
        perror("Error on opening file\n");
        return 1;
    }

    //2. read/write
    char buf[1024];
    int bytes_read = 0;
    while ((bytes_read = readln(file_fd, buf, 1024)) > 0){
        write(1, &buf, bytes_read);
    }

    return 0;
}
