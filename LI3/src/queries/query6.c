/**
 @file query6.c
 @brief File that contains query 6 resolution
 */
#include <stdio.h>
#include <strings.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_repos.h"
#include "../../include/cat_users.h"
#include "../../include/counter_hash.h"


/**
 * @brief Applies query6 operations to an entry of commits' catalogue
 * 
 * @param key Repo_id
 * @param repo_value Data of that repository
 * @param traverse_data Data passed to the function
 */
void q6_func(gpointer key, gpointer commit_value, gpointer traverse_data){
    void **func_data = traverse_data;
    GHashTable *hash = func_data[0];
    char *language = func_data[1];
    Cat_Commits cat_commits = func_data[2];
    Cat_Repos cat_repos = func_data[3];

    int repo_id = *(int *)key;
    R_Info repo_info = commit_value;
    int num_commits = get_repo_info_num_commits(repo_info);

    Repo repo = search_repo(cat_repos, repo_id);
    char *check_language = get_repo_language(repo);

    if(!strcasecmp(language, check_language)){
        for(int i=0; i < num_commits; i++){
            Commit commit_info = search_commit(cat_commits, repo_id);

            int author_id = get_commit_author_id(commit_info);
            int committer_id = get_commit_committer_id(commit_info);
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

            free_commit(commit_info);
        }
    }

    free_repo(repo);
    free(check_language);
}


/**
 * @brief Prints query6 result on output file
 * 
 * @param list List to be printed
 * @param cat_users Users catalogue
 * @param output File to be written
 * @param N N first nodes
 */
void print_q6(GList *list, Cat_Users cat_users, FILE *output, int N){
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
void display_page_q6(GList *list, Cat_Users cat_users, int page_num){
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
 * @brief Query 6 : Top N of users with more commits in repositories of a given language
 * 
 * @param N Number of users from input
 * @param language Repository language from input
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return Pointer to list that stores the result
 */
GList *query6(int N, char *language, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable *hash = g_hash_table_new(g_int_hash, g_int_equal);
    void *traverse_data[4] = {hash, language, cat_commits, cat_repos};

    commits_foreach(cat_commits, q6_func, traverse_data);

    GList *list = to_list(hash, N);

    return list;
}