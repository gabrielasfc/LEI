#ifndef CMD_INT_
#define CMD_INT_

#include "../include/cat_commits.h"
#include "../include/cat_users.h"
#include "../include/cat_repos.h" 

void commands_interpreter(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, void** queries_data, char* file_name, char* is_query_9_first_time, char* is_query_10_first_time);

#endif