#ifndef QUERY7_
#define QUERY7_

#include <stdio.h>
#include "cat_commits.h"
#include "cat_repos.h"

GList *query7(char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos);

void print_q7(GList *list, Cat_Repos cat_repos, FILE *output);

void display_page_q7(GList* list, Cat_Repos cat_repos, int page_num);

void free_q7_list(GList *list);

#endif