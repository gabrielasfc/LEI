#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int agrc, char *argv[]){
    //1. open files
    int file1_fd = 0; //STDIN_FILENO
    int file2_fd = 1; //STDOUT_FILENO

    //2. read/write
    char buf[1024];
    int bytes_read = 0;
    while ((bytes_read = read(file1_fd, &buf, 1024)) > 0){
        write(file2_fd, &buf, bytes_read);
    }
    
    return 0;
}