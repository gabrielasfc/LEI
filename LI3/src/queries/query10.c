/**
 @file query10.c
 @brief File that contains query 10 resolution
 */
#include <stdio.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_users.h"


/**
 * @brief Displays query 10 result on menu
 * 
 * @param list List
 * @param page_num Page number
 */
void display_page_query_10(GList* list, int page_num){
    printf("------------------------------------------------------\n");
    for(int j = (page_num-1)*5; j>0 && list; j--){
        list=list->next;
    }
    for(int i = 0; i < 5 && list; i++, list = list->next){
        char* line = list->data;
        char* dup = strdup(line), *backup;
        backup = dup;
        char* id = strsep(&dup, " ;\n"), *login = strsep(&dup, " ;\n"), *msg_ln = strsep(&dup, " ;\n"), *repo_id;
        if (*id == 'n') {
            repo_id = strsep(&dup, " ;\n");
            printf("---------------- Repositório %s ---------------\n", repo_id);
            id++;
        }
        printf("| %s | %s | %s |\n", id, login, msg_ln);
        printf("------------------------------------------------------\n");
        free(backup);
    }
}


/**
 * @brief Prints the output of query 10 (a list)
 * 
 * @param list List with the output
 * @param output Where we want to print
 */
void print_q10(GList *list, FILE *output){
    while (list){
        char* print = (char*) list->data;
        if (*print == 'n') print++;
        fprintf(output, "%s", print);
        list = list->next;
    }
}


/**
 * @brief Query 10 function - in first call sorts commits by message length and puts the results in a file
 * In subsequent calls, gets the query result from that file
 * 
 * @param N Number of commits per repo
 * @param cat_users Users catalog
 * @param cat_commits Commits catalog
 * @param is_first_time Pointer to a boolean that stores if is the first time that we call this query or not
 * 
 * @return The output of this query as a list
 */
GList* query10(int N, Cat_Users cat_users, Cat_Commits cat_commits, char* is_first_time){
    if (*is_first_time == 1){
        FILE* aux_file = fopen("saida/query_10_aux.txt", "w");
        int num_repos;
        GList* commits_by_msg_ln[800000] = {0};
        GList *prev = NULL, *l = NULL;
        
        num_repos = sort_by_msg_ln(cat_commits, commits_by_msg_ln, 800000);

        for(int i=0; i<num_repos; i++){
            fprintf(aux_file, "%s", "n");
            for(l = commits_by_msg_ln[i]; l; prev = l, l = l->next){
                Commit commit = (Commit) (l->data);
                int author_id = get_commit_author_id(commit);
                int committer_id = get_commit_committer_id(commit);
                User user = search_user(cat_users, author_id);
                char *login = get_user_login(user);
                
                fprintf(aux_file, "%d;%s;%d;%d\n", author_id, login, get_commit_msg_ln(commit), get_commit_repo_id(commit));

                if (author_id != committer_id){
                    User user = search_user(cat_users, committer_id);
                    char *login = get_user_login(user);

                    fprintf(aux_file, "%d;%s;%d;%d\n", committer_id, login, get_commit_msg_ln(commit), get_commit_repo_id(commit));

                    free(login);
                    free_user(user);
                }

                g_list_free_1(prev);

                free(login);
                free_user(user);
                free_commit(commit);
            }
        }
        
        *is_first_time = 0;
        fclose(aux_file);
    }
    
    FILE* aux_file = fopen("saida/query_10_aux.txt", "r");
    fseek(aux_file, 0, 0);
    char* buffer = malloc(100*sizeof(char));
    GList* ret = NULL;
    int cnt;

    while (fgets(buffer, 100, aux_file)){
        if (buffer[0] == 'n') cnt=0;
        if (cnt < N) {
            ret = g_list_prepend(ret, buffer);
            buffer = malloc(100*sizeof(char));
            cnt++;
        }
    }
    ret = g_list_reverse(ret);

    free(buffer);

    return ret;
}
