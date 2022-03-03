/**
 @file query5.c
 @brief File that contains query 5 resolution
 */
#include <stdio.h>
#include <string.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_users.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query5 operations to an entry of commits' catalogue
 * 
 * @param key Repo_id
 * @param commit_value Pointer to repo_info
 * @param traverse_data Data passed to the function
 */
void q5_func(gpointer key, gpointer commit_value, gpointer traverse_data){
    void **func_data = traverse_data;
    GHashTable *hash = func_data[0];
    char *start_date = func_data[1];
    char *end_date = func_data[2];
    Cat_Commits cat_commits = func_data[3];

    int i = 0;
    int repo_id = *(int *)key;
    R_Info repo_info = commit_value;
    int num_commits = get_repo_info_num_commits(repo_info);

    while(i < num_commits){
        Commit commit_info = search_commit(cat_commits, repo_id);

        int author_id = get_commit_author_id(commit_info);
        int committer_id = get_commit_committer_id(commit_info);
        int date_year = get_commit_date_year(commit_info);
        char date_month = get_commit_date_month(commit_info);
        char date_day = get_commit_date_day(commit_info);

        if(future_date(date_year, date_month, date_day, start_date)){
            if(previous_date(date_year, date_month, date_day, end_date)){
                if(author_id == committer_id){
                    int *p = malloc(sizeof(int)); *p = author_id;
                    if(!increment(p, hash)) free(p);
                }
                else{
                    int *p = malloc(sizeof(int)), *q = malloc(sizeof(int));
                    *p = author_id; *q = committer_id;
                    if(!increment(p, hash)) free(p);
                    if(!increment(q, hash)) free(q);
                }
            }
        }
        else {free_commit(commit_info); break;}
        i++;
        free_commit(commit_info);
    }
}


/**
 * @brief Prints query5 result on output file
 * 
 * @param list List to be printed
 * @param cat_users Users catalogue
 * @param output File to be written
 * @param N N first nodes
 */
void print_q5(GList *list, Cat_Users cat_users, FILE *output, int N){
    for(int i = 0; i < N && list; i++){
        CNT_NODE node_info = list->data;
        int id = get_cnt_node_value_int(node_info);
        int count = get_cnt_node_count(node_info);
        User user = search_user(cat_users, id);
        char *login = get_user_login(user);

        fprintf(output, "%d;%s;%d\n", id, login, count);
        free_user(user);
        free(login);

        list = list->next;
    }
}


/**
 * @brief Displays query 6 result on menu
 * 
 * @param list List
 * @param cat_users Users catalogue
 * @param page_num Page number
 */
void display_page_q5(GList *list, Cat_Users cat_users, int page_num){
    printf("------------------------------------------------------\n");
    for(int j = (page_num-1)*5; j>0 && list; j--){
        list=list->next;
    }

    for(int i = 0; i < 5 && list; i++){
        CNT_NODE node_data = list->data;
        int id = get_cnt_node_value_int(node_data);
        int count = get_cnt_node_count(node_data);
        User user = search_user(cat_users, id);
        char *login = get_user_login(user);

        printf("| %d | %s | %d |\n", id, login, count);
        printf("------------------------------------------------------\n");

        free(login);
        list = list->next;
    }
}


/**
 * @brief Query 5 : Top N of most active users on a given date range
 * 
 * @param N Number of users from input
 * @param start_date Bottom limit of date range from input
 * @param end_date Top limmit of date range from input
 * @param cat_commits Commits catalogue
 * 
 * @return Pointer to list that stores the result
 */
GList *query5(int N, char *start_date, char *end_date, Cat_Commits cat_commits){
    GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);
    void *traverse_data[4] = {hash, start_date, end_date, cat_commits};

    commits_foreach(cat_commits, q5_func, traverse_data);
    
    GList *list = to_list(hash, N);

    return list;
}