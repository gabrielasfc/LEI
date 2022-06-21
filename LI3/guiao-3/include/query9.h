#ifndef QUERY9_
#define QUERY9_

#include <stdio.h>
#include "cat_users.h"
#include "cat_commits.h"
#include "cat_repos.h"

void display_page_query_9(GList* list, int page_num);

GList* query9(int N, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, char* is_first_time);

void print_q9(GList* list, FILE* output);

#endif