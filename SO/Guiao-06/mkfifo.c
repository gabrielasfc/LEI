#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if (mkfifo(argv[1], 0666) < 0){
        perror("error on creating fifo");
        return 1;
    }
    else printf("fifo was successfully created\n");

    return 0;
}