
//#define DEBUG
#ifdef DEBUG

#include "../include/logger.h"
#include <stdio.h>
#include <time.h>

void log_info(char* message){
    printf("\033[0;37m");
    time_t now;
    time(&now);
    printf("%s: %s\n", ctime(&now), message);
}

void log_warning(char* message){
    printf("\033[0;33m");
    time_t now;
    time(&now);
    printf("%s: %s\n", ctime(&now), message);
}

void log_error(char* message){
    printf("\033[0;31m");
    time_t now;
    time(&now);
    printf("%s: %s\n", ctime(&now), message);
}
#endif
#ifndef DEBUG
void log_info(char* message){

}

void log_warning(char* message){

}

void log_error(char* message){

}
#endif