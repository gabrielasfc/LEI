/**
 @file query9.c
 @brief File that contains query 9 resolution
 */
#include <stdio.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_users.h"
#include "../../include/cat_repos.h"
#include "../../include/counter_hash.h"


/**
 * @brief Displays query 9 result on menu
 * 
 * @param list List
 * @param page_num Page number
 */
void display_page_query_9(GList* list, int page_num){
    printf("------------------------------------------------------\n");
    for(int j = (page_num-1)*5; j>0 && list; j--){
        list=list->next;
    }
    for(int i = 0; i < 5 && list; i++, list = list->next){
        char* line = list->data;
        char* dup = strdup(line), *backup;
        backup = dup;
        char* id = strsep(&dup, " ;\n"); char* login = strsep(&dup, " ;\n");
        printf("| %s | %s |\n", id, login);
        printf("------------------------------------------------------\n");
        free(backup);
    }
}


/**
 * @brief Checks if owner of the repo of that commit is included in the followers 
 *        and following list of commiter or author of that commit.
 *        If so, increments a counter associated with that id.
 *        Optimization: if author_id and committer_id are equal, only increments one
 * 
 * @param data Commit to be checked
 * @param user_data Data to pass to this function (including repo_id, catalogues and hashtable with counters)
 */
void check_commit_friends(Commit commit, void* user_data){
    void** traverse_data = (void** )user_data;
    GHashTable* n_commits = traverse_data[0]; Cat_Users cat_users = traverse_data[1];  Cat_Repos cat_repos = traverse_data[2];
    int repo_id = get_commit_repo_id(commit);
    int author_id = get_commit_author_id(commit), committer_id = get_commit_committer_id(commit);
    Repo repo = search_repo(cat_repos, repo_id);

    if (repo == NULL) { printf("Repo não %d encontrado\n", repo_id); return; }
    
    int repo_owner_id = get_repo_owner_id(repo);
    User author = search_user(cat_users, author_id), committer = search_user(cat_users, committer_id);
    
    if (author_id == committer_id){
        if (find_in_following_list(author, repo_owner_id) && find_in_follower_list(author, repo_owner_id)){
            int *p = malloc(sizeof(int)); *p = author_id;
            if(!increment(p, n_commits)) free(p);;
        }
    }
    else{
        if (find_in_following_list(author, repo_owner_id) && find_in_follower_list(author, repo_owner_id)){
            int *p = malloc(sizeof(int)); *p = author_id;
            if(!increment(p, n_commits)) free(p);
        }
        if (find_in_following_list(committer, repo_owner_id) && find_in_follower_list(committer, repo_owner_id)){
            int *p = malloc(sizeof(int)); *p = committer_id;
            if(!increment(p, n_commits)) free(p);
        }
    }

    free_user(author);
    free_user(committer);
    free_repo(repo);
}


/**
 * @brief Prints id and login on output file
 * 
 * @param data Pointer to list on final hashtable's entry
 * @param out Output txt file
 */
void print_node_q9(FILE* output, void* value, int cnt, void* traverse_data){
    Cat_Users cat_users = (Cat_Users) traverse_data;
    User user = search_user(cat_users, *(int*)value);
    if (user == NULL) {printf("User %d não encontrado\n", *(int*)value); return; }
    char *login = get_user_login(user);

    fprintf(output, "%d;%s\n", *(int*)value, login);

    free(login);
    free_user(user);
}


/**
 * @brief Prints the output of query 9 (a list)
 * 
 * @param list What we want to print
 * @param output Where we want to print (file)
 */
void print_q9(GList* list, FILE* output){
    while (list){
        fprintf(output, "%s", (char*)(list->data));
        list = list->next;
    }
}


/**
 * @brief Query 9 : Top N of users with more commits in repos whose owner is a friend
 * 
 * @param N Number of users
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return Pointer to list that stores the result
 */
GList* query9(int N, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, char* is_first_time){
    if (*is_first_time){
        FILE* aux_file = fopen("saida/query_9_aux.txt", "w");
        GHashTable* n_commits = g_hash_table_new(g_int_hash, g_int_equal);
        void* traverse_data[3] = {n_commits, cat_users, cat_repos};

        traverse_commits(cat_commits, check_commit_friends, traverse_data);
        GList* ordered_list = to_list(n_commits, 0);
        print_list(ordered_list, aux_file, print_node_q9, cat_users);
        free_list(ordered_list);

        *is_first_time = 0;
        fclose(aux_file);
    }

    FILE* aux_file = fopen("saida/query_9_aux.txt", "r");
    fseek(aux_file, 0, 0);
    char* buffer = malloc(100*sizeof(char));
    GList* ret = NULL;
    int i=0;

    while (fgets(buffer, 100, aux_file) && i<N){
        ret = g_list_prepend(ret, buffer);
        buffer = malloc(100*sizeof(char));
        i++;
    }

    free(buffer);

    return ret;
}
