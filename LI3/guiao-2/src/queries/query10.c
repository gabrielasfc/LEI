/**
 @file query10.c
 @brief File that contains query 10 resolution
 */
#include <stdio.h>
#include "../../include/cat_commits.h"
#include "../../include/cat_users.h"

/**
 * @brief Auxiliar struct to solve query10
 */
typedef struct q10_info{
    char* id;
    int msg_ln;
}*Q10_INF;


/**
 * @brief Get id from Q10 struct
 * 
 * @param q10_inf Q10 struct
 * 
 * @return Id as string
 */
char* get_q10_inf_id(Q10_INF q10_inf){
    return q10_inf->id;
}


/**
 * @brief Get message length from Q10 struct
 * 
 * @param q10_inf Q10 struct
 * 
 * @return Message length
 */
int get_q10_inf_msg_ln(Q10_INF q10_inf){
    return q10_inf->msg_ln;
}


/**
 * @brief Create Q10 struct node
 * 
 * @param id Id to insert
 * @param msg_len Message length to insert
 * 
 * @return New Q10 struct
 */
Q10_INF create_q10_node(char* id, int msg_ln){
    Q10_INF node = malloc(sizeof(struct q10_info));

    node->id = strdup(id);
    node->msg_ln = msg_ln;

    return node;
}


/**
 * @brief Finds a certain id in a list
 * 
 * @param id Id to find
 * @param list List to lookup
 * 
 * @return 1 if found else 0
 */
int find_id_in_list(char* id, GList* list){
    while (list){
        Q10_INF node = list->data;
        if (!strcmp(node->id, id)) break;
        list = list->next;
    }

    return list != NULL;
}


/**
 * @brief Get first N elements in the list
 * 
 * @param key Key 
 * @param value Pointer to the beggining of the list
 * @param user_data Data to be passed to the function
 */
void get_init_N(gpointer key, gpointer value, gpointer user_data){
    char* repo_id = (char* )key;
    void** traverse_data = (void**) user_data;
    GHashTable* new_hash = traverse_data[0];
    int N = *((int*)(traverse_data[1]));
    GList* commits_from_repo_id = (GList* )value;
    GList* newList = NULL;

    for(int i=0; commits_from_repo_id != NULL && i<N; ){
        Commit orig = (Commit) commits_from_repo_id->data;
        
        char *author_id = get_commit_author_id(orig);
        char *committer_id = get_commit_committer_id(orig);
        int msg_ln = get_commit_msg_ln(orig);


        if (!strcmp(committer_id, author_id)){
            if (!find_id_in_list(author_id, newList)){
                Q10_INF node = create_q10_node(author_id, msg_ln);
                newList = g_list_prepend(newList, node);
                i++;
            }
        }
        else {
            if (!find_id_in_list(author_id, newList)){
                Q10_INF node = create_q10_node(author_id, msg_ln);
                newList = g_list_prepend(newList, node);
                i++;
            }
            if (i != N && !find_id_in_list(committer_id, newList)){
                Q10_INF node = create_q10_node(committer_id, msg_ln);
                newList = g_list_prepend(newList, node);
                i++;
            }
        }

        free(author_id);
        free(committer_id);
        
        commits_from_repo_id = commits_from_repo_id->next;
    }

    g_hash_table_insert(new_hash, repo_id, newList);
}


/**
 * @brief Duplicates for a new hash with essential information
 * 
 * @param cat_commits Commits catalogue
 * @param N N first elements
 * 
 * @return Hashtable duplicated
 */
GHashTable* commits_duplicate_init_N(Cat_Commits cat_commits, int N){
    GHashTable* newHash = g_hash_table_new(g_str_hash, g_str_equal);
    void* traverse_data[2] = {newHash, &N};

    commits_for_each(cat_commits, get_init_N, traverse_data);

    return newHash;
}


/**
 * @brief Function used to print the query10 output
 * 
 * @param data Data to be printed
 * @param user_data Data to be passed to the function
 */
void print_commit_q10(gpointer data, gpointer user_data){
    void** t_data = (void** )user_data;
    void** traverse_data = (void**) t_data[0];
    FILE* output = traverse_data[1];
    Cat_Users cat_users = traverse_data[0];
    Q10_INF q10_inf = data;
    char* id = get_q10_inf_id(q10_inf);
    User user = search_user(id, cat_users);

    if (user != NULL){
        char* login = get_user_login(user);
        fprintf(output, "%s;%s;%d;%s\n", id, login, get_q10_inf_msg_ln(q10_inf), (char*) t_data[1]);
        free(login);
    }
    free(id);
    free(q10_inf);
}


/**
 * @brief Prints a list with Q10 structs
 * 
 * @param key Key
 * @param value Pointer to the list
 * @param user_data Data to be passed to the function (users catalogue and output file)
 */
void print_commits_list_q10(gpointer key, gpointer value, gpointer user_data){
    void* new_user_data[2] = {user_data, key};
    g_list_foreach(value, print_commit_q10, new_user_data);
    g_list_free(value);
}


/**
 * @brief Query 10 : Top N users with the biggest messages in each repository
 * 
 * @param output Output txt file
 * @param cat_users User catalogue
 * @param cat_commits Commits catalogue
 */
void query10(FILE* output, int N, Cat_Users cat_users, Cat_Commits cat_commits){
    GHashTable* dup_N = commits_duplicate_init_N(cat_commits, N);

    void* traverse_data[2] = {cat_users, output};
    g_hash_table_foreach(dup_N, print_commits_list_q10, traverse_data);
    g_hash_table_destroy(dup_N);
}