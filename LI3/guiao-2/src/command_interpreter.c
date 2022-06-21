/**
 @file command_interpreter.c
 @brief File that contains functions responsible for read commands and apply the relative query resolution
 */
#include <stdio.h>
#include <string.h>
#include "../include/cat_commits.h"
#include "../include/cat_users.h"
#include "../include/cat_repos.h"
#include "../include/command_interpreter.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"
#include "../include/query10.h"


/**
 * @brief Calls query5 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 */
void parseQ5(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits){
    int N = atoi(strsep(&line, " \r\n"));
    char* date_inic = strsep(&line, " \r\n");
    char* date_fin = strsep(&line, " \r\n");

    query5(output, N, date_inic, date_fin, cat_users, cat_commits);
}


/**
 * @brief Calls query6 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 */
void parseQ6(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    int N = atoi(strsep(&line, " \r\n"));
    char* language = strsep(&line, " \r\n");

    query6(output, N, language, cat_users, cat_commits, cat_repos);
}


/**
 * @brief Calls query7 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 */
void parseQ7(char* line, FILE* output, Cat_Commits cat_commits, Cat_Repos cat_repos){
    char* date = strsep(&line, " \r\n");

    query7(output, date, cat_commits, cat_repos);
}


/**
 * @brief Calls query8 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 */
void parseQ8(char* line, FILE* output, Cat_Commits cat_commits, Cat_Repos cat_repos){
    int N = atoi(strsep(&line, " \r\n"));
    char* date = strsep(&line, " \r\n");

    query8(output, N, date, cat_commits, cat_repos);
}


/**
 * @brief Calls query9 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog 
 */
void parseQ9(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    int N = atoi(strsep(&line, " \r\n"));

    query9(output, N, cat_users, cat_commits, cat_repos);
}


/**
 * @brief Calls query10 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 */
void parseQ10(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits){
    int N = atoi(strsep(&line, " \r\n"));

    query10(output, N, cat_users, cat_commits);
}


/**
 * @brief Reads a lines and interprete the query to be used
 * 
 * @param line Line to be interpreted
 * @param num_command Query number
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 * @param queries_data Data about statistical queries to be passed to the function
 */
void line_interpreter(char* line, int num_command, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, void** queries_data){
    char* dup = strdup(line), *backup = dup;
    int qId = 0;
    qId=atoi(strsep(&dup, " \r\n"));
    char fileName[28] = {};
    char n_command[4];
    int* user_types = queries_data[0]; // 0 - User, 1 - Bot, 2 - Organization
    sprintf(n_command, "%d", num_command);
    
    strcat(fileName, "saida/command");
    strcat(fileName, n_command);
    strcat(fileName, "_output.txt");

    FILE* output = fopen(fileName, "w");

    switch(qId){
        case 1: fprintf(output, "Bot: %d\nOrganization: %d\nUser: %d\n", user_types[1], user_types[2], user_types[0]); break;
        case 2: fprintf(output, "%.2f\n", *(float* )queries_data[1]); break;
        case 3: fprintf(output, "%d\n", *(int* )queries_data[2]); break;
        case 4: fprintf(output, "%.2f\n", *(float* )queries_data[3]); break;
        case 5: parseQ5(dup, output, cat_users, cat_commits); break;
        case 6: parseQ6(dup, output, cat_users, cat_commits, cat_repos); break;
        case 7: parseQ7(dup, output, cat_commits, cat_repos); break;
        case 8: parseQ8(dup, output, cat_commits, cat_repos); break; 
        case 9: parseQ9(dup, output, cat_users, cat_commits, cat_repos); break; 
        case 10: parseQ10(dup, output, cat_users, cat_commits); break; 
    }

    free(backup);
    fclose(output);
}


/**
 * @brief Reads the command
 * 
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 * @param queries_data Data about statistical queries to be passed to the function
 * @param file_name String with the file name
 */
void commands_interpreter(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, void** queries_data, char* file_name){
    FILE* commands = fopen(file_name, "r");
    char buffer[1000];
    int i=1;

    if (commands==NULL){
        printf("Ficheiro não existe\n");
        return ;
    }

    while(fgets(buffer, 1000, commands) != NULL){
        line_interpreter(buffer, i, cat_users, cat_commits, cat_repos, queries_data);
        i++;
    }
    fclose(commands);
}