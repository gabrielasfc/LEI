#ifndef CAT_REPOS_
#define CAT_REPOS_

#include <glib.h>

typedef struct cat_repos *Cat_Repos;
typedef struct repo *Repo;

Repo create_repo(char **fields);

Cat_Repos create_repos_cat();

Cat_Repos insert_repo(void *key, Repo data, Cat_Repos cat_repos);

Repo search_repo(char *key, Cat_Repos cat_repos);

int get_cat_repos_length(Cat_Repos cat_repos);

void repos_for_each(Cat_Repos cat_repos, GHFunc func, gpointer traverse_data);

char* get_repo_owner_id(Repo data);

char* get_repo_description(Repo data);

char* get_repo_language(Repo data);

void print_repos(Cat_Repos cat_repos);

void free_repos(Cat_Repos cat_repos);

#endif