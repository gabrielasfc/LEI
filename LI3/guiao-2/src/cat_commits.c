/**
 @file cat_commits.c
 @brief File containing structure of commits catalog
 */
#include <glib.h>
#include <string.h>
#include <stdio.h>
#include "../include/cat_commits.h"


/**
 * @brief Commits catalog (currently an hashtable from glib)
 */
struct cat_commits{ /** Commits catalogue **/
    GHashTable* commits; /** Hashtable for commits **/
};


/**
 * @brief Commit struct
 */
struct commit{ /** Commit struct **/
    char* author_id; /** Author id of a commit **/
    char* committer_id; /** Committer id of a commit **/
    char* commit_at; /** Date of a commit **/
    int msg_ln; /** Message length of a commit **/ 
};


/**
 * @brief Create a commit object
 * 
 * @param fields List of commit fields in string format
 * 
 * @return Commit struct
 */
Commit create_commit(char** fields){
    Commit commit = malloc(sizeof(struct commit));

    commit->author_id = fields[1];
    commit->committer_id = fields[2];
    commit->commit_at = fields[3];
    commit->msg_ln = strlen(fields[4]);

    return commit;
}


/**
 * @brief Create a commits catalog object
 * 
 * @return Cat_Commits 
 */
Cat_Commits create_commits_cat(){
    Cat_Commits cat_commits = malloc(sizeof(struct cat_commits));
    cat_commits->commits = g_hash_table_new(g_str_hash, g_str_equal);

    return cat_commits;
}


/**
 * @brief Utility function to compare two commits based on both message lengths
 * Used for decreasing order insertion in list of commits for a certain repo
 * 
 * @param commit_a Commit1
 * @param commit_b Commit2
 * 
 * @return diference between length of msg from a and length of msg from b
 */
gint compare_msg_size(gconstpointer commit_a, gconstpointer commit_b){  
    Commit c_a = (Commit) commit_a;
    Commit c_b = (Commit) commit_b;

    return c_b->msg_ln - c_a->msg_ln;
}


/**
 * @brief Insert commit in commits catalog
 * Inserts commit in the list of commits for that repo_id
 * List is sorted decreasingly
 * 
 * @param key Repo id from commit to insert
 * @param commit Commit data to insert
 * @param cat_commits Commits catalog
 * @return Updated commits catalog
 */
Cat_Commits insert_commit(void *key, Commit commit, Cat_Commits cat_commits){
    int flag = 0;

    GList* commits_from_repo_id = g_hash_table_lookup(cat_commits->commits, (gconstpointer) key);

    if(commits_from_repo_id != NULL) flag=1;

    commits_from_repo_id = g_list_insert_sorted(commits_from_repo_id, commit, compare_msg_size);
    g_hash_table_insert(cat_commits->commits, key, commits_from_repo_id);

    if(flag) free(key);

    return cat_commits;
}


/**
 * @brief Searches a commit in commits catalog
 * 
 * @param key Repo id to search
 * @param cat_commits Commits catalog
 * 
 * @return Commit data
 */
Commit search_commit(char *key, Cat_Commits cat_commits){
    return(g_hash_table_lookup(cat_commits->commits, key));
}


/**
 * @brief Gets the length of the hash in commits catalog
 * 
 * @param cat_commits Commits catalog
 * 
 * @return Hash size
 */
int get_cat_commits_length(Cat_Commits cat_commits){
    return g_hash_table_size(cat_commits->commits);
}


/**
 * @brief Applies a function to all entries of commits hash
 * 
 * @param cat_commits Commits catalog
 * @param func Func to be applied
 * @param traverse_data Data passed to the function
 */
void commits_for_each(Cat_Commits cat_commits, GHFunc func, gpointer traverse_data){
    g_hash_table_foreach(cat_commits->commits, func, traverse_data);
}


/**
 * @brief Gets author id from a commit; Allocates memory
 * 
 * @param data Commit data
 * 
 * @return Commit author id
 */
char* get_commit_author_id(Commit data){
    return strdup(data->author_id);
}


/**
 * @brief Gets committer id from a commit; Allocates memory
 * 
 * @param data Commit data
 * 
 * @return Commit committer id
 */
char* get_commit_committer_id(Commit data){
    return strdup(data->committer_id);
}


/**
 * @brief Gets commit at from a commit; Allocates memory
 * 
 * @param data Commit data
 * 
 * @return Commit commit_at
 */
char *get_commit_commit_at(Commit data){
    return strdup(data->commit_at);
}


/**
 * @brief Gets message length from a commit
 * 
 * @param data Commit data
 * 
 * @return Message length
 */
int get_commit_msg_ln(Commit data){
    return data->msg_ln;
}


/**
 * @brief Prints a commit
 * 
 * @param data Commit data without repo_id
 * @param user_data NULL
 */
void print_commit(gpointer data, gpointer user_data){
    Commit commit = data;
    printf("Author_id: %s\nCommitter_id: %s\nCommit_at: %s\nMsg_length: %d\n---------------\n", 
        commit->author_id, 
        commit->committer_id, 
        commit->commit_at, 
        commit->msg_ln);
}


/**
 * @brief Prints the list of commits for a given repo
 * 
 * @param key Repo_id
 * @param value List of commits
 * @param user_data NULL
 */
void print_commits_list(gpointer key, gpointer value, gpointer user_data){
    char* repo_id = (char* )key;
    GList* commits_from_repo_id = (GList* )value;

    printf("Commits for %s: \n---------------\n", repo_id);
    g_list_foreach(commits_from_repo_id, print_commit, NULL);
}


/**
 * @brief Prints all commits from all repos
 * 
 * @param cat_commits Commits catalog
 */
void print_commits(Cat_Commits cat_commits){
    g_hash_table_foreach(cat_commits->commits, print_commits_list, NULL);
}


/**
 * @brief Free a commit value
 * Frees all dynamically allocated fields (author_id, committer_id, commit_at)
 * 
 * @param data Commit data to be freed
 * @param traverse_data NULL
 */
void free_commit_value(void *data, void *traverse_data){
    Commit commit = data;
    free(commit->author_id);
    free(commit->committer_id);
    free(commit->commit_at);
    free(commit);
}

/**
 * @brief Free a list of commits from a repo
 * Frees repo_id (string) and all commits related to that repo
 * 
 * @param key Repo_id
 * @param value List of commits
 * @param user_data NULL
 */
void free_commits_from_repo(gpointer key, gpointer value, gpointer user_data){
    free((char*)key);
    g_list_foreach((GList* ) value, free_commit_value, NULL);
    g_list_free((GList* ) value);
}


/**
 * @brief Free commits catalog
 * 
 * @param cat_commits Commits catalog
 */
void free_commits(Cat_Commits cat_commits){
    g_hash_table_foreach(cat_commits->commits, free_commits_from_repo, NULL);
    g_hash_table_destroy(cat_commits->commits);
    free(cat_commits);
}


/**
 * @brief Checks if there is a commit from a Bot in a repository
 * 
 * @param repo_id Repo_id from given repository
 * @param cat_commits Commits catalog
 * @param id_bots Hashtable with bots' ids
 * 
 * @return 1 if there is a commit by a Bot, 0 otherwise
 */
int has_bots_in_repo(char* repo_id, Cat_Commits cat_commits, GHashTable* id_bots){
    int has_bot = 0;
    GList* commits_from_repo = g_hash_table_lookup(cat_commits->commits, repo_id);
    while(commits_from_repo && has_bot == 0){
        Commit commit = commits_from_repo->data;

        if (g_hash_table_lookup(id_bots, commit->author_id) != NULL || g_hash_table_lookup(id_bots, commit->committer_id) != NULL) has_bot = 1; // Bot could be either author or committer
        commits_from_repo = commits_from_repo->next;
    }

    return has_bot;
}


/**
 * @brief Counts the collaborators in a commit from a given repository 
 * 
 * @param repo_id Given repo_id from repository
 * @param author_id Author_id from given user to check commits
 * @param committer_id Committer_id from given user to check commits
 * @param cat_commits Commits catalog
 * 
 * @return 1 if author_id and committer_id have the same values
 *         2 if author_id and committer_id do not have the same values
 *         0 if we already counted that collaborator on other commit with the same repo id
 */
int collabs_counter(char *repo_id, char *author_id, char *committer_id, Cat_Commits cat_commits){
    void *lookup = g_hash_table_lookup(cat_commits->commits, repo_id);
    int r=0, flag=1;

    if(lookup != NULL){
        GList *list = lookup;

        while(list && flag){
            Commit value = list->data;
            if(!strcmp(value->author_id, author_id) || !strcmp(value->author_id, committer_id) || !strcmp(value->committer_id, author_id) || !strcmp(value->committer_id, committer_id)) 
                flag = 0;
            list = list->next;
        }

        if(flag && !strcmp(author_id, committer_id)) r=1;
        else if(flag) r=2;
        else if(!strcmp(author_id, committer_id)) r=0;
        else r=1;
    }
    else{
        if(!strcmp(author_id, committer_id)) r=1;
        else r=2;
    }

    return r;
}

