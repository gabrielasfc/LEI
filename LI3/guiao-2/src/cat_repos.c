/**
 @file cat_repos.c
 @brief File containing structure of repositories catalog
 */
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cat_repos.h"


/**
 * @brief Repositories catalog (currently an hashtable from GLib)
 */
struct cat_repos{ /** Repositories catalogue **/
    GHashTable *repos; /** Hashtable for repositories **/
};


/**
 * @brief Repository struct
 */
struct repo{ /** Struct for repository **/
    char *owner_id; /** Owner id of a repository **/
    char *description; /** Description of a repository **/
    char *language; /** Language of a repository **/
};


/**
 * @brief Creates a repository object
 * 
 * @param fields List of repository fields in string format
 * 
 * @return Repository struct
 */
Repo create_repo(char **fields){
    Repo repo = malloc(sizeof(struct repo));

    repo->owner_id = fields[1];
    repo->description = fields[2];
    repo->language = fields[3];

    return repo;
}


/**
 * @brief Create a repository catalog object
 * 
 * @return Cat_Repos
 */
Cat_Repos create_repos_cat(){
    Cat_Repos cat_repos = malloc(sizeof(struct cat_repos));
    cat_repos->repos = g_hash_table_new(g_str_hash, g_str_equal);

    return cat_repos;
}


/**
 * @brief Inserts a repo in repos catalog
 * 
 * @param key Repo id from repo to insert
 * @param data Repo data to insert
 * @param cat_repos Repos catalog
 * 
 * @return Updated repos catalog
 */
Cat_Repos insert_repo(void *key, Repo data, Cat_Repos cat_repos){
    g_hash_table_insert(cat_repos->repos, key, data);

    return cat_repos;
}


/**
 * @brief Searches a repo in repositories catalog
 * 
 * @param key Repo id to search
 * @param cat_repos Repos catalog
 * 
 * @return Repo data
 */
Repo search_repo(char *key, Cat_Repos cat_repos){
    return(g_hash_table_lookup(cat_repos->repos, key));
}


/**
 * @brief Gets the length of the hash in repositories catalog
 * 
 * @param cat_repos Repos catalog
 * 
 * @return Hash size
 */
int get_cat_repos_length(Cat_Repos cat_repos){
    return g_hash_table_size(cat_repos->repos);
}


/**
 * @brief Applies a function to all entries of repos hash
 * 
 * @param cat_repos Repositories catalog
 * @param func Func to be applied
 * @param traverse_data Data passed to the function
 */
void repos_for_each(Cat_Repos cat_repos, GHFunc func, gpointer traverse_data){
    g_hash_table_foreach(cat_repos->repos, func, traverse_data);
}


/**
 * @brief Gets owner_id from a repo; Allocates memory
 * 
 * @param data Repository data
 * 
 * @return Owner_id
 */
char* get_repo_owner_id(Repo data){ 
    return strdup(data->owner_id); 
}


/**
 * @brief Gets description from a repo; Allocates memory
 * 
 * @param data Repository data
 * 
 * @return Repo description
 */
char* get_repo_description(Repo data){ 
    return strdup(data->description); 
}


/**
 * @brief Gets language from a repo; Allocates memory
 * 
 * @param data Repository data
 * 
 * @return Repo language
 */
char* get_repo_language(Repo data){ 
    return strdup(data->language); 
}


/**
 * @brief Prints a repository
 * 
 * @param key Repo id
 * @param repo_data Repo data
 * @param traverse_data Data passed to the function
 */ 
void print_repos_aux(void *key, void *repo_data, void *traverse_data){
    Repo data = repo_data;
    printf("%s;%s;%s;%s\n", (char*)key, data->owner_id, data->description, data->language);
}


/**
 * @brief Prints repositories catalog data
 * 
 * @param cat_repos Repositories catalog
 */
void print_repos(Cat_Repos cat_repos){
    g_hash_table_foreach(cat_repos->repos, print_repos_aux, NULL);
}


/**
 * @brief Free a repo
 * 
 * @param key Repo id
 * @param value Data to be freed
 * @param traverse_data Data passed to the function
 */
void free_repos_aux(void *key, void *value, void *traverse_data){
    Repo repo_struct = value;

    free(repo_struct->owner_id);
    free(repo_struct->description);
    free(repo_struct->language);
    free(repo_struct);
    free(key);
}

/**
 * @brief Frees the repositories catalog
 * 
 * @param cat_repos Repositories catalog
 */
void free_repos(Cat_Repos cat_repos){
    g_hash_table_foreach(cat_repos->repos, free_repos_aux, NULL);
    g_hash_table_destroy(cat_repos->repos);
    free(cat_repos);
}
