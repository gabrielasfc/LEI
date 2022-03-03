/**
 @file command_interpreter.c
 @brief File that contains functions responsible for read commands,
        apply the relative query resolution and print outputs on .txt files
 */
#include <stdio.h>
#include <string.h>
#include "../include/cat_commits.h"
#include "../include/cat_users.h"
#include "../include/cat_repos.h"
#include "../include/command_interpreter.h"
#include "../include/counter_hash.h"
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
    char* start_date = strsep(&line, " \r\n");
    char* end_date = strsep(&line, " \r\n");

    GList *list = query5(N, start_date, end_date, cat_commits);
    print_q5(list, cat_users, output, N);

    free_list(list);
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

    GList *list = query6(N, language, cat_commits, cat_repos);
    print_q6(list, cat_users, output, N);

    free_list(list);
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

    GList *list = query7(date, cat_commits, cat_repos);
    print_q7(list, cat_repos, output);

    free_q7_list(list);
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

    GList *list = query8(N, date, cat_commits, cat_repos);
    print_q8(list, output, N);

    free_list(list);
}


/**
 * @brief Calls query9 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog 
 * @param is_first_time To check if it is the first time we run query 9
 */
void parseQ9(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, char* is_first_time){
    int N = atoi(strsep(&line, " \r\n"));

    GList* list = query9(N, cat_users, cat_commits, cat_repos, is_first_time);
    print_q9(list, output);

    free_string_list(list);
}


/**
 * @brief Calls query10 function
 * 
 * @param line Line to be parsed
 * @param output File where we write the query result
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param is_first_time To check if it is the first time we run query 10
 */
void parseQ10(char* line, FILE* output, Cat_Users cat_users, Cat_Commits cat_commits, char* is_first_time){
    int N = atoi(strsep(&line, " \r\n"));

    GList* list = query10(N, cat_users, cat_commits, is_first_time);
    print_q10(list, output);

    free_string_list(list);
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
 * @param is_query_9_first_time To check if it is the first time we are running query 9
 * @param is_query_10_first_time To check if it is the first time we are running query 10
 */
void line_interpreter(char* line, int num_command, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, void** queries_data, char* is_query_9_first_time, char* is_query_10_first_time){
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
        case 9: parseQ9(dup, output, cat_users, cat_commits, cat_repos, is_query_9_first_time); break; 
        case 10: parseQ10(dup, output, cat_users, cat_commits, is_query_10_first_time); break; 
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
 * @param is_query_9_first_time To check if it is the first time we are running query 9
 * @param is_query_10_first_time To check if it is the first time we are running query 10
 */
void commands_interpreter(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, void** queries_data, char* file_name, char* is_query_9_first_time, char* is_query_10_first_time){
    FILE* commands = fopen(file_name, "r");
    char buffer[1000];
    int i=1;

    if (commands==NULL){
        printf("Ficheiro não existe\n");
        return ;
    }

    while(fgets(buffer, 1000, commands) != NULL){
        line_interpreter(buffer, i, cat_users, cat_commits, cat_repos, queries_data, is_query_9_first_time, is_query_10_first_time);
        i++;
    }
    fclose(commands);
}