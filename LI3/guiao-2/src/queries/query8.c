/**
 @file query8.c
 @brief File that contains query 8 resolution
 */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/queries_aux.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query8 operations to an entry of repos' hashtable
 * 
 * @param key Repo_id
 * @param repo_value Data of that repository
 * @param traverse_data Traverse data
 */
void q8_func(void *key, void *repo_value, void *traverse_data){
    void **input_data = traverse_data;
    char *lmt_date = input_data[0];
    Cat_Commits cat_commits = input_data[1];
    GHashTable **final_hash = input_data[2];

    char *repo_id = key;
    void *commit_data = search_commit(repo_id, cat_commits);
    char *repo_lang = get_repo_language(repo_value);

    if (commit_data == NULL || strcasecmp(repo_lang,"None")==0){
        free(repo_lang);
        return;
    }
    else{
        int is_commit_after = check_commit_after(commit_data, lmt_date);

        if (is_commit_after){
            increment(repo_lang, NULL, final_hash);
        }
    }
    free(repo_lang);
}


/**
 * @brief Prints repo language on output file
 * 
 * @param list Pointer to list on final hashtable's entry
 * @param output Output txt file
 */
void print_node_q8(void *list, FILE *output){
    fprintf(output, "%s\n", get_nd_key(list));
}


/**
 * @brief Query 8 : Top N of most used languages ​​since a given date
 * 
 * @param output Output txt file
 * @param N Number of languages from input
 * @param lmt_date Limit date from input
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void query8(FILE* output, int N, char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    void *traverse_data1[3] = {lmt_date, cat_commits, &hash};

    repos_for_each(cat_repos, q8_func, traverse_data1);

    GList *list = present_N(hash, print_node_q8, N, output);

    free_hash(hash);
    free_list(list);
}