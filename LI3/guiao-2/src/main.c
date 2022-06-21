/**
 @file main.c
 @brief File that has the function reponsible for the execution of the program
 */
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/cat_repos.h"
#include "../include/cat_users.h"
#include "../include/cat_commits.h"
#include "../include/command_interpreter.h"

/**
 * @brief Main function
 * Calls parser and commands interpreter
 * Frees all memory from catalogues
 * 
 * @param argc Arguments count
 * @param argv Arguments values
 * @return 0 (no errors)
 */
int main(int argc, char** argv){
    Cat_Users cat_users = create_users_cat();
    Cat_Commits cat_commits = create_commits_cat();
    Cat_Repos cat_repos = create_repos_cat();

    void** queries_data = parser(cat_users, cat_commits, cat_repos);
    
    commands_interpreter(cat_users, cat_commits, cat_repos, queries_data, argv[1]); // Argv[1] is the name of the file with the commands
    
    free(queries_data[0]);
    free(queries_data);
    
    free_repos(cat_repos);
    free_users(cat_users);
    free_commits(cat_commits);
    
    return 0;
}