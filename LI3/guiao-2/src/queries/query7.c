/**
 @file query7.c
 @brief File that contains query 7 resolution
 */
#include <stdio.h>
#include <time.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/queries_aux.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query7 operations to an entry of repos' hashtable
 * 
 * @param key Repo_id
 * @param repo_value Data of that repository
 * @param traverse_data Traverses data
 */
void q7_func(void *key, void *repo_value, void *traverse_data){
    void **input_data = traverse_data;
    char *lmt_date = input_data[0];
    Cat_Commits cat_commits = input_data[1];
    GHashTable *final_hash = input_data[2];

    char *repo_id = key;
    void *commit_data = search_commit(repo_id, cat_commits);
    if (commit_data == NULL){
        char *repo_desc = get_repo_description(repo_value);
        g_hash_table_insert(final_hash, repo_id, repo_desc);
    }
    else{
        int is_inactive = !check_commit_after(commit_data, lmt_date);
        if(is_inactive){
            char *repo_desc = get_repo_description(repo_value);
            g_hash_table_insert(final_hash, repo_id, repo_desc);
        }
    }
}


/**
 * @brief Prints an hashtable's entry
 * 
 * @param key Repo_id
 * @param repo_value Repo_desc
 * @param output File where we want to print
 */
void print_q7(void *key, void *repo_value, void *output){
    char *repo_id = key;
    char *desc = repo_value;
    fprintf(output, "%s;%s\n", repo_id, desc);
}


/**
 * @brief Frees an hashtable entry
 * 
 * @param key Repo_id
 * @param value Repo_desc
 * @param traverse_data NULL
 */
void free_q7(void *key, void *value, void *traverse_data){
    free(value);
}


/**
 * @brief Frees hashtable
 * 
 * @param hash Hashtable that stores query7 data
 */
void free_hash_q7(GHashTable *hash){
    g_hash_table_foreach(hash, free_q7, NULL);
    g_hash_table_destroy(hash);
}


/**
 * @brief Query 7 : List of inactive repos from a given date (indicated by parameter)
 * 
 * @param output Output txt file
 * @param lmt_date Limit date from input
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void query7(FILE* output, char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    void *traverse_data[3] = {lmt_date, cat_commits, hash};

    repos_for_each(cat_repos, q7_func, traverse_data);
    g_hash_table_foreach(hash,  print_q7, output);

    free_hash_q7(hash);
}