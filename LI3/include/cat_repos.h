#ifndef CAT_REPOS_
#define CAT_REPOS_

#include <glib.h>

typedef struct cat_repos *Cat_Repos;
typedef struct repo *Repo;

Cat_Repos create_repos_cat();

int check_repo(Cat_Repos cat_repos, int repo_id);

Repo search_repo(Cat_Repos cat_repos, int key);

int insert_repo(Cat_Repos cat_repos, char *fields[4]);

void repos_foreach(Cat_Repos cat_repos, GHFunc func, gpointer data);

void repos_foreach_remove(Cat_Repos cat_repos, GHRFunc func, gpointer data);

void free_repo(Repo repo);

void free_cat_repos(Cat_Repos cat_repos);

int get_cat_repos_size(Cat_Repos cat_repos);

int get_repo_repo_id(Repo data);

int get_repo_owner_id(Repo data);

char *get_repo_description(Repo data);

char *get_repo_language(Repo data);

void print_repo(Repo repo);

#endif
