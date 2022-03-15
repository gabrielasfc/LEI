#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int agrc, char *argv[]){
    //1. open files
    int file1_fd = open(argv[1], O_RDONLY);
    if (file1_fd < 0){
        perror("Error on opening file1\n");
        return 1;
    }

    int file2_fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0640);
    if (file2_fd < 0){
        perror("Error on opening file2\n");
        return 1;
    }

    //2. read/write
    char buf[1024];
    int bytes_read = 0;
    while ((bytes_read = read(file1_fd, &buf, 1024)) > 0){
        write(file2_fd, &buf, bytes_read);
    }
    
    //3. close files
    close(file1_fd);
    close(file2_fd);

    return 0;
}