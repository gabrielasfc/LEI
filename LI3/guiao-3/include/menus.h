#ifndef MENUS_
#define MENUS_

#include "../include/cat_commits.h"
#include "../include/cat_repos.h"
#include "../include/cat_users.h"

void display_queries_menu();

int ask_for_query_info(char* query_info[3]);

int display_page(int q_id, GList *list, int* page_num, int page_lim, void *query1, float query2, int query3, float query4, Cat_Users cat_users, Cat_Repos cat_repos);

GList* query_caller(int id, char *query_input[3], Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos);

void free_query_caller(int query_id, GList *list);

#endif