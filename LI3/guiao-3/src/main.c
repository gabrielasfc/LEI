/**
 @file main.c
 @brief File that contains the function reponsible executing program
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/menus.h"
#include "../include/parser.h"
#include "../include/cat_repos.h"
#include "../include/cat_users.h"
#include "../include/cat_commits.h"
#include "../include/counter_hash.h"
#include "../include/command_interpreter.h"


/**
 * @brief Main function
 *        Calls parser and, according to arguments, calls modules to print queries on files and on terminal
 *        Frees all memory from catalogues
 * 
 * @param argc Arguments count
 * @param argv Arguments values
 * 
 * @return 0 (no errors)
 */
int main(int argc, char** argv){
    Cat_Users cat_users = create_users_cat();
    Cat_Commits cat_commits = create_commits_cat();
    Cat_Repos cat_repos = create_repos_cat();
    void **queries_data = (void**) data_to_catalogues_with_parsing(cat_users, cat_commits, cat_repos);
    char is_query_9_first_time = 1;
    char is_query_10_first_time = 1;

    float query2 = *(float *)queries_data[1];
    int query3 = *(int *)queries_data[2];
    float query4 = *(float *)queries_data[3];

    if (argc == 2){
        commands_interpreter(cat_users, cat_commits, cat_repos, queries_data, argv[1], &is_query_9_first_time, &is_query_10_first_time); // Argv[1] is the name of the file with the commands
    }
    else{

        char *query_input[3];
        int query_id, page_num;

        do{
            page_num = 1;
            display_queries_menu();
            query_id = ask_for_query_info(query_input);

            if (query_id == -1){free(query_input[0]); free(query_input[1]); free(query_input[2]); break;}

            if (query_id == 10) query_input[1] = &is_query_10_first_time;
            else if (query_id == 9) query_input[1] = &is_query_9_first_time;

            GList *list = query_caller(query_id, query_input, cat_users, cat_commits, cat_repos);

            int list_length = g_list_length(list);
            int page_lim;
            
            if(list_length%5 != 0) page_lim = 1 + (list_length/5);
            else page_lim = list_length/5;

            while(display_page(query_id, list, &page_num, page_lim, queries_data[0], query2, query3, query4, cat_users, cat_repos));
            
            free_query_caller(query_id, list);
            free(query_input[0]); 
            if (query_id != 9 && query_id != 10) {
                free(query_input[1]); free(query_input[2]);
            }
        } while(query_id != 0); 

    }

    free(queries_data[0]);
    free(queries_data);
    free_cat_repos(cat_repos);
    free_cat_users(cat_users);
    free_cat_commits(cat_commits);

    return 0;
}
