#ifndef QUERY6_
#define QUERY6_

GList *query6(int N, char *language, Cat_Commits cat_commits, Cat_Repos cat_repos);

void display_page_q6(GList *list, Cat_Users cat_users, int page_num);

void print_q6(GList *list, Cat_Users cat_users, FILE *output, int N);

#endif