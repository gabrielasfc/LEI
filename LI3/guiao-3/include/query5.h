#ifndef QUERY5_
#define QUERY5_

GList *query5(int N, char *start_date, char *end_date, Cat_Commits cat_commits);

void display_page_q5(GList *list, Cat_Users cat_users, int page_num);

void print_q5(GList *list, Cat_Users cat_users, FILE *output, int N);

#endif