#ifndef CAT_COMMITS_
#define CAT_COMMITS_

#include <glib.h>

typedef struct cat_commits *Cat_Commits;
typedef struct commit *Commit;

Commit create_commit(char** fields);

Cat_Commits create_commits_cat();

Cat_Commits insert_commit(void *key, Commit commit, Cat_Commits cat_commits);

Commit search_commit(char *key, Cat_Commits cat_commits);

int get_cat_commits_length(Cat_Commits cat_commits);

void commits_for_each(Cat_Commits cat_commits, GHFunc func, gpointer traverse_data);

char* get_commit_author_id(Commit data);

char* get_commit_committer_id(Commit data);

char *get_commit_commit_at(Commit data);

int get_commit_msg_ln(Commit data);

void print_commits(Cat_Commits cat_commits);

void free_commits(Cat_Commits cat_commits);

int has_bots_in_repo(char* repo_id, Cat_Commits cat_commits, GHashTable* id_bots);

int collabs_counter(char *repo_id, char *author_id, char *committer_id, Cat_Commits cat_commits);

#endif