/**
 @file query8.c
 @brief File that contains query 8 resolution
 */
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query6 operations to an entry of commits' catalogue
 * 
 * @param key Repo_id
 * @param value Data of that commit
 * @param traverse_data Data passed to the function
 */
void q8_func(gpointer key, gpointer value, gpointer traverse_data){
    void **input_data = traverse_data;
    char *lmt_date = input_data[0];
    Cat_Repos cat_repos = input_data[1];
    Cat_Commits cat_commits = input_data[2];
    GHashTable *final_hash = input_data[3];

    int repo_id = *(int *)key;
    R_Info repo_info = value;
    int num_commits = get_repo_info_num_commits(repo_info);

    for(int i=0; i<num_commits; i++){
        Commit commit_info = search_commit(cat_commits, repo_id);
        int date_year = get_commit_date_year(commit_info);
        char date_month = get_commit_date_month(commit_info);
        char date_day = get_commit_date_day(commit_info);

        if(future_date(date_year, date_month, date_day, lmt_date)){
            Repo repo = search_repo(cat_repos, repo_id);
            char *repo_lang = get_repo_language(repo);

            if(strcasecmp(repo_lang,"None")!=0){
                if(!increment(repo_lang, final_hash)) free(repo_lang);
            }
            else free(repo_lang);

            free_repo(repo);
        }
        else {free_commit(commit_info); break;}

        free_commit(commit_info);
    }
}


/**
 * @brief Prints query8 result on output file
 * 
 * @param list List to be printed
 * @param output File to be written
 * @param N N first nodes
 */
void print_q8(GList *list, FILE *output, int N){
    for(int i = 0; i < N && list; i++){
        CNT_NODE node_info = list->data;
        char *lang = get_cnt_node_value_str(node_info);
        fprintf(output, "%s\n", lang);
        free(lang);
        list = list->next;
    }
}


/**
 * @brief Displays query 8 result on menu
 * 
 * @param list List
 * @param page_num Page number
 */
void display_page_q8(GList *list, int page_num){
    printf("------------------------------------------------------\n");
    for(int j = (page_num-1)*5; j>0 && list; j--){
        list=list->next;
    }

    for(int i = 0; i<5 && list; i++, list = list->next){
        CNT_NODE node = list->data;
        char *lang = get_cnt_node_value_str(node);
        printf("| %s |\n", lang);
        printf("------------------------------------------------------\n");

        free(lang);
    }
}


/**
 * @brief Query 8 : Top N of most used languages ​​since a given date
 * 
 * @param N Number of languages from input
 * @param lmt_date Limit date from input
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return Pointer to list that stores the result
 */
GList *query8(int N, char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);
    void *traverse_data[4] = {lmt_date, cat_repos, cat_commits, hash};

    commits_foreach(cat_commits, q8_func, traverse_data);

    GList *list = to_list(hash, N);

    return list;
}