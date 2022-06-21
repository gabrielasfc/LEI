/**
 @file query5.c
 @brief File that contains query 5 resolution
 */
#include <stdio.h>
#include <string.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_users.h"
#include "../../include/queries_aux.h"
#include "../../include/counter_hash.h"


/**
 * @brief Query5 operations
 * 
 * @param value Commit data
 * @param traverse_data Traverses data
 */
void list_func_q5(void *value, void *traverse_data){
    void **func_data = traverse_data;
    GHashTable **hash = func_data[0];
    char *start_date = func_data[1];
    char *end_date = func_data[2];
    Cat_Users cat_users = func_data[3];

    char *author_id = get_commit_author_id(value);
    char *committer_id = get_commit_committer_id(value);
    char *cmp_date = get_commit_commit_at(value);

    struct tm Commit_Date;
    struct tm Bottom_Date;
    struct tm Top_Date;

    strptime(cmp_date, "%Y-%m-%d %H:%M:%S", &Commit_Date);
    strptime(start_date, "%Y-%m-%d %H:%M:%S", &Bottom_Date);
    strptime(end_date, "%Y-%m-%d %H:%M:%S", &Top_Date);

    
    int bool_future = not_future_date(Commit_Date.tm_mday, Commit_Date.tm_mon+1, Commit_Date.tm_year +1900 , Top_Date.tm_mday, Top_Date.tm_mon+1, Top_Date.tm_year+1900);
    int bool_prev = not_prev_date(Commit_Date.tm_mday, Commit_Date.tm_mon+1, Commit_Date.tm_year +1900 , Bottom_Date.tm_mday, Bottom_Date.tm_mon+1, Bottom_Date.tm_year+1900);

    if(bool_future && bool_prev && !strcmp(author_id, committer_id)){
        void *data_users = search_user(author_id, cat_users);
        char *login = get_user_login(data_users);

        increment(author_id, login, hash);
        free(login);
    }
    else if(bool_future && bool_prev){
        void *data1_users = search_user(author_id, cat_users);
        void *data2_users = search_user(committer_id, cat_users);
        char *login1 = get_user_login(data1_users);
        char *login2 = get_user_login(data2_users);

        increment(author_id, login1, hash);
        increment(committer_id, login2, hash);
        free(login1); free(login2);
    }
    free(cmp_date); free(author_id); free(committer_id);
}


/**
 * @brief Applies query5 operations to an entry of commits' hashtable
 * 
 * @param key Repo_id
 * @param commit_value Pointer to list of commits with same repo id
 * @param traverse_data Traverses data
 */
void q5_func(void* key, void* commit_value, void* traverse_data){
    void **func_data = traverse_data;
    GHashTable *hash = func_data[0];
    char *start_date = func_data[1];
    char *end_date = func_data[2];
    Cat_Users cat_users = func_data[3];
    void *traverse_data1[4] = {&hash, start_date, end_date, cat_users};

    g_list_foreach(commit_value, list_func_q5, traverse_data1);

}


/**
 * @brief Prints user id, login and number of commits on output file
 * 
 * @param list Pointer to list on final hashtable's entry
 * @param output Output txt file
 */
void print_node_q5(void *list, FILE *output){
    int count = get_nd_count(list);
    char *id = get_nd_key(list);
    char *login = get_nd_value(list);
    fprintf(output, "%s;%s;%d\n", id, login, count);
}


/**
 * @brief Query 5 : Top N of most active users on a given date range
 * 
 * @param output Output txt file
 * @param N Number of users from input
 * @param start_date Bottom limit of date range from input
 * @param end_date Top limmit of date range from input
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 */
void query5(FILE *output, int N, char *start_date, char *end_date, Cat_Users cat_users, Cat_Commits cat_commits){
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    GList *list;
    void *traverse_data[5] = {hash, start_date, end_date, cat_users, cat_commits};

    commits_for_each(cat_commits, q5_func, traverse_data);

    list = present_N(hash, print_node_q5, N, output);

    free_hash(hash);
    free_list(list);
}