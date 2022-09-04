#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int seconds = 0;
int count_ctrl = 0;
int should_exit = 0;

void inc_second(int signum){
    seconds++;
    printf("ALRM\n");
    alarm(1);
}

void print_seconds(int signum){
    printf("CTRL+C. seconds: %d \n", seconds);
    count_ctrl++;
}

void sigquit_handler(int signum){
    printf("number of CTRL+C: %d\n", count_ctrl);
    printf("exiting...\n");
    should_exit = 1;
}


int main(int argc, char *argv[]){
    if (signal(SIGALRM, inc_second) == SIG_ERR){
        printf("error on sigalrm\n");
        return 1;
    }

    if (signal(SIGINT, print_seconds) == SIG_ERR){
        printf("error on sigint\n");
        return 1;
    }

    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR){
        printf("error on siquit\n");
        return 1;
    }

    printf("getpid: %d\n", getpid());

    alarm(1);

    while(!should_exit){
        pause();
    }

    printf("seconds: \n", seconds); 
    
    return 0;
}
