#ifndef QUERY8_
#define QUERY8_

#include <stdio.h>

void print_q8(GList *list, FILE *output, int N);

void display_page_q8(GList *list, int page_num);

GList *query8(int N, char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos);

#endif