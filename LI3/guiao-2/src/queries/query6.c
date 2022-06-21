/**
 @file query6.c
 @brief File that contains query 6 resolution
 */
#include <stdio.h>
#include <strings.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/cat_users.h"
#include "../../include/queries_aux.h"
#include "../../include/counter_hash.h"


/**
 * @brief Query6 operations
 * 
 * @param value Node of commits list
 * @param traverse_data Traverses data
 */
void list_func_q6(void *value, void *traverse_data){
    void **func_data = traverse_data;
    GHashTable **hash = func_data[0];
    Cat_Users cat_users = func_data[1];
    char *author_id = get_commit_author_id(value);
    char *committer_id = get_commit_committer_id(value);

    if(!strcmp(author_id, committer_id)){
        void *data_users = search_user(author_id, cat_users);
        char *login = get_user_login(data_users);

        increment(author_id, login, hash);

        free(login);
    }
    else{
        void *data_users1 = search_user(author_id, cat_users);
        void *data_users2 = search_user(committer_id, cat_users);
        char *login1 = get_user_login(data_users1);
        char *login2 = get_user_login(data_users2);

        increment(author_id, login1, hash);
        increment(committer_id, login2, hash);

        free(login1);
        free(login2);
    }
    free(author_id); free(committer_id);
}


/**
 * @brief Applies query6 operations to an entry of repos' hashtable
 * 
 * @param key Repo_id
 * @param repo_value Data of that repository
 * @param traverse_data Traverses data
 */
void q6_func(void *key, void *repo_value, void *traverse_data){
    void **func_data = traverse_data;
    void *hash = func_data[0];
    char *lang = func_data[1];
    Cat_Commits cat_commits = func_data[2];
    Cat_Users cat_users = func_data[3];
    char *repo_lang = get_repo_language(repo_value);

    if(!strcasecmp(lang, repo_lang)){
        char *repo_id = key;

        void *commit_list = search_commit(repo_id, cat_commits);

        void *traverse_data2[2] = {&hash, cat_users};
        if(commit_list != NULL) g_list_foreach(commit_list, list_func_q6, traverse_data2);
    }
    free(repo_lang);
}


/**
 * @brief Prints user id, login and number of commits on output file
 * 
 * @param list Pointer to list on final hashtable's entry
 * @param output Output txt file
 */
void print_node_q6(void *list, FILE *output){
    int count = get_nd_count(list);
    char *id = get_nd_key(list);
    char *login = get_nd_value(list);
    fprintf(output, "%s;%s;%d\n", id, login, count);
}


/**
 * @brief Query 6 : Top N of users with more commits in repositories of a given language
 * 
 * @param output Output txt file
 * @param N Number of users from input
 * @param language Repository language from input
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void query6(FILE *output, int N, char *language, Cat_Users cat_users ,Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    GList *list;
    void *traverse_data1[4] = {hash, language, cat_commits, cat_users};

    repos_for_each(cat_repos, q6_func, traverse_data1);

    list = present_N(hash, print_node_q6, N, output);

    free_hash(hash);
    free_list(list);
}