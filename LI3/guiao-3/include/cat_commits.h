#ifndef CAT_COMMITS_
#define CAT_COMMITS_

#include <glib.h>

typedef struct cat_commits *Cat_Commits;
typedef struct commit *Commit;
typedef struct repo_info *R_Info;

Cat_Commits create_commits_cat();

int get_cat_commits_size(Cat_Commits cat_commits);

int get_repo_info_num_commits(R_Info repo_info);

int check_commit(Cat_Commits cat_commits, int repo_id);

Commit search_commit(Cat_Commits cat_commits, int repo_id);

int insert_commit(Cat_Commits cat_commits, char* fields[4]);

void commits_foreach(Cat_Commits cat_commits, GHFunc func, gpointer data);

void free_commit(gpointer data);

void free_cat_commits(Cat_Commits cat_commits);

int commits_memory_to_file(Cat_Commits cat_commits);

int count_repos_with_bots(Cat_Commits cat_commits, GHashTable *id_bots);

int count_total_collabs(Cat_Commits cat_commits);

int previous_date(int date_year, char date_month, char date_day, char *lmt_date);

int future_date(int date_year, char date_month, char date_day, char *lmt_date);

void traverse_commits(Cat_Commits cat_commits, void (*func)(Commit, void*), void* traverse_data);

void print_commit(Commit commit);

void print_cat_commits(Cat_Commits cat_commits);

int get_commit_repo_id(Commit commit_info);

int get_commit_author_id(Commit commit_info);

int get_commit_committer_id(Commit commit_info);

int get_commit_msg_ln(Commit commit_info);

int get_commit_date_year(Commit commit_info);

char get_commit_date_month(Commit commit_info);

char get_commit_date_day(Commit commit_info);

int sort_by_msg_ln(Cat_Commits cat_commits, GList* arr[], int N);

#endif
