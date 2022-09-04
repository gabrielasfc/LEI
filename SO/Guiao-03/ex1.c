#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    //execl("/bin/ls", "/bin/ls", "-l" , NULL);
    
    execlp("ls", "ls", "-l", NULL);

    //char *exec_args[] = {"/bin/ls" , "-l", NULL};
    //execv("/bin/ls", exec_args);

    return 0;
}