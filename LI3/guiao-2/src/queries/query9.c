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
 * @brief Checks if owner of the repo of that commit is included in the followers 
 * and following list of commiter or author of that commit.
 * If so, increments a counter associated with that id.
 * Optimization: if author_id and committer_id are equal, only increments one
 * 
 * @param data Commit to be checked
 * @param user_data Data to pass to this function (including repo_id, catalogues and hashtable with counters)
 */
void check_commit(gpointer data, gpointer user_data){
    void** traverse_data = (void** )user_data;
    Commit commit = data;
    GHashTable** n_commits = traverse_data[0]; Cat_Users cat_users = traverse_data[1];  Cat_Repos cat_repos = traverse_data[2];
    char* repo_id = ((void**)(user_data))[3], *author_id = get_commit_author_id(commit), *committer_id = get_commit_committer_id(commit);
    Repo repo = search_repo(repo_id, cat_repos); 
    if (repo == NULL) return;
    char* repo_owner_id = get_repo_owner_id(repo);
    User author = search_user(author_id, cat_users), committer = search_user(committer_id, cat_users);

    if (!strcmp(author_id, committer_id)){
        if (find_in_following_list(author, repo_owner_id) && find_in_follower_list(author, repo_owner_id)){
            char* login = get_user_login(author);
            increment(author_id, login, n_commits);
            free(login);
        }
    }
    else{
        if (find_in_following_list(author, repo_owner_id) && find_in_follower_list(author, repo_owner_id)){
            char* login = get_user_login(author);
            increment(author_id, login, n_commits);
            free(login);
        }
        if (find_in_following_list(committer, repo_owner_id) && find_in_follower_list(committer, repo_owner_id)){
            char* login = get_user_login(committer);
            increment(committer_id, login, n_commits);
            free(login);
        }
    }
    free(repo_owner_id);
    free(author_id);
    free(committer_id);
}

/**
 * @brief Function to traverse the list of commits from a given repo
 * 
 * @param key Repo_id
 * @param value List of commits
 * @param user_data Traverse data
 */
void traverse_commits_list_q9(gpointer key, gpointer value, gpointer user_data){
    char* mykey = (char*) key;
    void** traverse_data = (void**) user_data;
    void* traverse_data2[4] = {traverse_data[0], traverse_data[1], traverse_data[2], mykey};
    g_list_foreach(value, check_commit, traverse_data2);
}

/**
 * @brief Prints id and login on output file
 * 
 * @param data Pointer to list on final hashtable's entry
 * @param out Output txt file
 */
void print_node_q9(void* data, FILE* out){
    fprintf(out, "%s;%s\n", get_nd_key(data), (char*) get_nd_value(data));
}

/**
 * @brief Query 9 : Top N of users with more commits in repos whose owner is a friend
 * 
 * @param output Output txt file
 * @param N Number of users
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void query9(FILE* output, int N, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GHashTable* n_commits = g_hash_table_new(g_str_hash, g_str_equal);
    void* traverse_data[3] = {&n_commits, cat_users, cat_repos};

    commits_for_each(cat_commits, traverse_commits_list_q9, traverse_data);

    GList* list = present_N(n_commits, print_node_q9, N , output);

    free_hash(n_commits);
    free_list(list);
}
