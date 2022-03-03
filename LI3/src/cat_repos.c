/**
 @file cat_repos.c
 @brief File containing structure of repositories catalog
 */
#include <glib.h>
#include <stdio.h>
#include "../include/cat_repos.h"


/**
 * @brief Repositories catalogue struct
 */
struct cat_repos{ /** Repos catalogue **/
    FILE *hash; /** Where the hashtable will be stored **/
    GHashTable *index; /** Index from the repos' positions on file **/
    int file_size; /** Repos' file size **/
};


/**
 * @brief Repo struct
 */
struct repo{ /** Repo struct **/
    int repo_id; /** Repo id (key) **/
    int owner_id; /** Owner id **/
    char *description; /** Description from repo **/
    int description_length; /** Length of description string **/
    char *language; /** Language from repo **/
    int language_length; /** Language string length **/
};


/**
 * @brief Creates repos catalogue
 *
 * @return Repos catalogue
 */
Cat_Repos create_repos_cat(){
    Cat_Repos cat_repos = malloc(sizeof(struct cat_repos));
    cat_repos->hash = fopen("saida/REPOS.bin", "wb+");
    cat_repos->index = g_hash_table_new(g_int_hash, g_int_equal);
    cat_repos->file_size = 0;

    return cat_repos;
}


/**
 * @brief Creates an repository with given fields; Allocates memory
 *
 * @param fields List of repo fields in string format
 *
 * @return Repository
 */
struct repo create_repo(char* fields[4]){
    struct repo repo;
    repo.repo_id = atoi(fields[0]);
    repo.owner_id = atoi(fields[1]);
    repo.description = fields[2];
    repo.description_length = strlen(fields[2]);
    repo.language = fields[3];
    repo.language_length = strlen(fields[3]);
    return repo;
}


/**
 * @brief Checks if a repo exists in repos catalogue
 * 
 * @param cat_repos Repos catalogue
 * @param repo_id Repo_id to search
 * 
 * @return 1 if the given repo_id is found, 0 otherwise
 */
int check_repo(Cat_Repos cat_repos, int repo_id){
    void *value = g_hash_table_lookup(cat_repos->index, &repo_id);

    return value != NULL;
}


/**
 * @brief Searches a repo in repos catalogue
 * 
 * @param cat_repos Repos catalogue
 * @param key Repo_id to search
 * 
 * @return Repo data
 */
Repo search_repo(Cat_Repos cat_repos, int key){
    int *index = g_hash_table_lookup(cat_repos->index, &key);
    if(index != NULL){
        Repo repo = malloc(sizeof(struct repo));

        fseek(cat_repos->hash, *index, 0);

        fread(&repo->repo_id, sizeof(int), 1, cat_repos->hash);
        fread(&repo->owner_id, sizeof(int), 1, cat_repos->hash);
        
        fread(&repo->description_length, sizeof(int), 1, cat_repos->hash);

        repo->description = malloc(sizeof(char)*(repo->description_length+1));
        fread(repo->description, sizeof(char), repo->description_length, cat_repos->hash);
        repo->description[repo->description_length] = '\0';

        fread(&repo->language_length, sizeof(int), 1, cat_repos->hash);

        repo->language = malloc(sizeof(char)*(repo->language_length+1));
        fread(repo->language, sizeof(char), repo->language_length, cat_repos->hash);
        repo->language[repo->language_length] = '\0';

        return repo;
    }
    return NULL;
}


/**
 * @brief Inserts a repo in repos catalogue
 * 
 * @param cat_repos Repos catalogue
 * @param fields List of repo fields in string format 
 * 
 * @return 0 if succeed
 */
int insert_repo(Cat_Repos cat_repos, char* fields[4]){
    struct repo repo = create_repo(fields);

    int *index = malloc(sizeof(int));
    int *repo_id = malloc(sizeof(int));
    *index = cat_repos->file_size;
    *repo_id = repo.repo_id;

    fwrite(&repo.repo_id, sizeof(int), 1, cat_repos->hash);
    fwrite(&repo.owner_id, sizeof(int), 1, cat_repos->hash);
    fwrite(&repo.description_length, sizeof(int), 1, cat_repos->hash);
    fwrite(repo.description, sizeof(char), repo.description_length, cat_repos->hash);
    fwrite(&repo.language_length, sizeof(int), 1, cat_repos->hash);
    fwrite(repo.language, sizeof(char), repo.language_length, cat_repos->hash);

    g_hash_table_insert(cat_repos->index, repo_id, index);

    cat_repos->file_size += 4 * sizeof(int) + repo.description_length * sizeof(char) + repo.language_length * sizeof(char);

    return 0;
}


/**
 * @brief Applies a function to all entries of repos indexes hash
 * 
 * @param cat_repos Repositories catalog
 * @param func Function to be applied
 * @param data Data passed to the function
 */
void repos_foreach(Cat_Repos cat_repos, GHFunc func, gpointer data){
    g_hash_table_foreach(cat_repos->index, func, data);
}


/**
 * @brief Applies a function(condition) to all entries of repos indexes hash
 *        and removes repos which don't validate the condition
 * 
 * @param cat_repos Repositories catalog
 * @param func Function to be applied
 * @param data Data passed to the function
 */
void repos_foreach_remove(Cat_Repos cat_repos, GHRFunc func, gpointer data){
    g_hash_table_foreach_remove(cat_repos->index, func, data);
}


/**
 * @brief Frees a repo
 * 
 * @param repo Repo to be freed
 */
void free_repo(Repo repo){
    free(repo->description);
    free(repo->language);
    free(repo);
}


/**
 * @brief Frees an entry in the indexes hash
 * 
 * @param key Entry key
 * @param value Entry value
 * @param data Data to pass to the function
 */
void free_cat_repos_entry(gpointer key, gpointer value, gpointer data){
    free(value);
    free(key);
}


/**
 * @brief Frees repo catalogue
 * 
 * @param cat_repos Repos catalogue
 */
void free_cat_repos(Cat_Repos cat_repos){
    g_hash_table_foreach(cat_repos->index, free_cat_repos_entry, NULL);
    g_hash_table_destroy(cat_repos->index);
    free(cat_repos->hash);
    free(cat_repos);
}


/**
 * @brief Gets the size of indexes hash
 * 
 * @param cat_repos Repos catalogue
 * 
 * @return Size
 */
int get_cat_repos_size(Cat_Repos cat_repos){
  return g_hash_table_size(cat_repos->index);
}


/**
 * @brief Gets repo id from a repo
 * 
 * @param data Repo data
 * 
 * @return Repo_id
 */
int get_repo_repo_id(Repo data){
    return data->repo_id;
}


/**
 * @brief Gets owner_id from a repo
 * 
 * @param data Repo data
 * 
 * @return Owner_id
 */
int get_repo_owner_id(Repo data){
    return data->owner_id;
}


/**
 * @brief Gets description from a repo; Allocates memory
 *
 * @param data Repo data
 * 
 * @return Description
 */
char *get_repo_description(Repo data){
    return strdup(data->description);
}


/**
 * @brief Gets language from a repo; Allocates memory
 *
 * @param data Repo data
 * 
 * @return Language
 */
char *get_repo_language(Repo data){
    return strdup(data->language);
}


/**
 * @brief Prints a repo
 * 
 * @param repo Repo to be printed
 */
void print_repo(Repo repo){
    if (repo != NULL)
      printf("Repo_id: %d\nOwner_id: %d\nDescription: %s\nLanguage: %s\n", repo->repo_id, repo->owner_id, repo->description, repo->language);
    else printf("Repo inválido!\n");
}