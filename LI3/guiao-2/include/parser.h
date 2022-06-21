#ifndef PARSER_
#define PARSER_
#include "cat_commits.h"
#include "cat_repos.h"
#include "cat_users.h"

typedef enum user_type {Us = 0, Bot = 1, Organization = 2} U_TYPE;

void get_fields(char* line, char** fields, int* positions, int num_positions);

void* parser(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos);

#endif