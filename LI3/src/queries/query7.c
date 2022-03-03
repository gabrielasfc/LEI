/**
 @file query7.c
 @brief File that contains query 7 resolution
 */
#include <stdio.h>
#include <time.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query7 operations to an entry of commits' catalogue
 * 
 * @param key Repo_id
 * @param commit_value Data of that commit
 * @param traverse_data Data passed to the function
 */
void q7_func(gpointer key, gpointer commit_value, gpointer traverse_data){
    void **input_data = traverse_data;
    char *lmt_date = input_data[0];
    Cat_Commits cat_commits = input_data[1];
    GList *list = *(void **)input_data[2];

    int repo_id = *(int *)key;
    R_Info repo_info = commit_value;
    int num_commits = get_repo_info_num_commits(repo_info);

    for(int i=0; i<num_commits; i++){
        Commit commit_info = search_commit(cat_commits, repo_id);
        int date_year = get_commit_date_year(commit_info);
        char date_month = get_commit_date_month(commit_info);
        char date_day = get_commit_date_day(commit_info);

        if(future_date(date_year, date_month, date_day, lmt_date)) {free(commit_info); break;} //ativo
        else{ //inativo
            int *data = malloc(sizeof(int));
            *data = repo_id;
            list = g_list_prepend(list, data);
            free(commit_info);
            break;
        }
    }

    *(void **)input_data[2] = list;
}


/**
 * @brief Prints the list
 * 
 * @param list List with repo ids
 * @param Cat_Repos Repos catalogue to get descriptions
 * @param output File where we want to print
 */
void print_q7(GList *list, Cat_Repos cat_repos, FILE *output){
    while(list){
        int repo_id = *(int *)list->data;
        Repo repo = search_repo(cat_repos, repo_id);
        if(repo != NULL){
            char *desc = get_repo_description(repo);
            fprintf(output, "%d;%s\n", repo_id, desc);
            free(desc);
        }

        free_repo(repo);
        list = list->next;
    }
}


/**
 * @brief Frees a query7 list node
 * 
 * @param data Pointer to data from that node
 */
void free_node_q7(gpointer data){
    free(data);
}


/**
 * @brief Displays query 7 result on menu
 * 
 * @param list List
 * @param cat_repos Repos catalogue
 * @param page_num Page number
 */
void display_page_q7(GList* list, Cat_Repos cat_repos, int page_num){
    printf("------------------------------------------------------\n");
    for(int j = (page_num-1)*5; j>0 && list; j--){
        list=list->next;
    }

    for(int i = 0; i < 5 && list; i++, list = list->next){
        int repo_id = *(int *)(list->data);
        Repo repo = search_repo(cat_repos, repo_id);
        char *desc = get_repo_description(repo);

        printf("| %d | %s |\n", repo_id, desc);
        printf("------------------------------------------------------\n");

        free(desc);
    }
}


/**
 * @brief Frees query7 list
 * 
 * @param list List that stores the inactive repo ids
 */
void free_q7_list(GList *list){
    g_list_free_full(list, free_node_q7);
}


/**
 * @brief Query 7 : List of inactive repos from a given date (indicated by parameter)
 * 
 * @param lmt_date Limit date from input
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return Pointer to list that stores inactive repo ids
 */
GList *query7(char *lmt_date, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GList *list = NULL;
    void *traverse_data[3] = {lmt_date, cat_commits, &list};

    commits_foreach(cat_commits, q7_func, traverse_data);

    return list;
}