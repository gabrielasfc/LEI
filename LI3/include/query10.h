#ifndef QUERY10_
#define QUERY10_

#include <stdio.h>
#include "cat_commits.h"
#include "cat_users.h"

void display_page_query_10(GList* list, int page_num);

void print_q10(GList *list, FILE *output);

GList* query10(int N, Cat_Users cat_users, Cat_Commits cat_commits, char* is_first_time);

#endif
