/**
 @file counter_hash.c
 @brief Module to help on queries envolving counting to present top N
 */
#include <glib.h>
#include <stdio.h>
#include "../include/counter_hash.h"

/**
 * @brief Struct to store the hash_value
 * 
 */
struct value_count{ /** Value count **/
    char* value; /** Pointer to a string **/
    int cnt; /** Count **/
};

/**
 * @brief Struct to store the list_value
 * 
 */
struct list_node{ /** Node of a list **/
    char* key; /** Key as string **/
    char* value; /** Pointer to a string **/
    int cnt; /** Count **/
};


/**
 * @brief Gets node key
 * 
 * @param node Node 
 * 
 * @return Key as string
 */
char* get_nd_key(L_NODE node){
    return node->key;
}


/**
 * @brief Gets node value
 * 
 * @param node Node
 * 
 * @return Pointer to node value
 */
void* get_nd_value(L_NODE node){
    return node->value;
}


/**
 * @brief Gets node count
 * 
 * @param node Node
 * 
 * @return Count of node
 */
int get_nd_count(L_NODE node){
    return node->cnt;
}


/**
 * @brief Create a hash_value object
 * 
 * @param data Data to be stored in hash along with a counter
 * @return CNT_VALUE Object created
 */
CNT_VALUE create_cnt_value(void* data){
    CNT_VALUE new = malloc(sizeof(struct value_count));
    char *string = data;
    if(data!=NULL) new->value = strdup(string);
    else new->value = data;
    new->cnt = 1;

    return new;
}


/**
 * @brief Increment the counter of inc_data object or creates a new entry in the hash with counter equal to 1
 * 
 * @param key Key of inc_data
 * @param inc_data Data to be incremented or inserted
 * @param hash Hash where we increment
 * @return 1 if new entry created, 0 if only counter is incremented
 */
int increment(char* key, void* inc_data, GHashTable** hash){
    int r = 0;
    if (key != NULL){
        CNT_VALUE found = g_hash_table_lookup(*hash, key);
        
        if (found == NULL){
            CNT_VALUE new = create_cnt_value(inc_data);
            g_hash_table_insert(*hash, strdup(key), new);
            r = 1;
        }
        else found->cnt++;
    }
    return r;
}


/**
 * @brief Convert a hash_value object to a list_value object
 * 
 * @param key Key associated with that hash object
 * @param hash_value Hash object (Value from key)
 * @return List_value object created
 */
L_NODE hash_value_to_list_value(char* key, CNT_VALUE hash_value){
    L_NODE new = malloc(sizeof(struct list_node));

    new->key = strdup(key);
    if(hash_value->value!=NULL) new->value = strdup(hash_value->value);
    else new->value = NULL;
    new->cnt = hash_value->cnt;

    return new;
}


/**
 * @brief Prints the value from hash
 * 
 * @param key Key
 * @param value CNT_VALUE
 * @param traverse_data In this case, file where we want to print
 */
void print_hash_cnt(void *key, void *value, void *traverse_data){
    FILE *output = traverse_data;
    CNT_VALUE cnt_val = value;
    char *cnt_val_data = cnt_val->value;
    fprintf(output, "%s;%s\n", (char *)key, cnt_val_data);    
}


/**
 * @brief Prints hash data to output file
 * 
 * @param hash Hashtable
 * @param output File where we want to print
 */
void print_hash(GHashTable *hash, FILE *output){
    g_hash_table_foreach(hash, print_hash_cnt, output);
}


/**
 * @brief Prints the first N elements of a list according to print_node function
 * 
 * @param list List to be printed
 * @param print_node Function to print the nodes
 * @param N Number of elements we want to print
 * @param output File where we want to print
 */
void print_n_first(GList* list, void (*print_node)(void*, FILE* ), int N, FILE* output){
    int i=0;
    if (N==-1){
        while (list){
            L_NODE node = list->data;
            print_node(node, output);
            list = list->next;
        }
    }
    else{
        while (list && i<N){
            L_NODE node = list->data;
            print_node(node, output);
            list = list->next; i++;
        }
    }
}


/**
 * @brief Utility function for insertion or sorting in/of the list
 * 
 * @param node1 First node to be compared
 * @param node2 Second node to be compared
 * @return Difference between counts (0 if counts equal, > 0 if cnt2 > cnt1, < 0 if cnt1 > cnt2)
 */
gint cmp_count(gconstpointer node1, gconstpointer node2){
    return ((L_NODE)(node2))->cnt - ((L_NODE)(node1))->cnt;
}


/**
 * @brief Utility function to convert a hash to list
 * 
 * @param key Key from the hash
 * @param value Value associated with that key
 * @param user_data Pointer to the list we want to form
 */
void hash_node_to_list(gpointer key, gpointer value, gpointer user_data){
    L_NODE new = hash_value_to_list_value(key, value);
    GList** list = user_data;
    *list = g_list_insert_sorted(*list, new, cmp_count);
}


/**
 * @brief Present the N nodes with greated counters
 * Firstly converts hash to list for sorting
 * Then, prints list in descending order
 * 
 * @param hash Original hash
 * @param print_node Function to print nodes
 * @param N Number of nodes we want to print
 * @param output Where we want to print
 */
GList* present_N(GHashTable* hash, void (*print_node)(void*, FILE* ), int N, FILE* output){
    GList* print_list = NULL;
    g_hash_table_foreach(hash, hash_node_to_list, &print_list);
    print_n_first(print_list, print_node, N, output);
    return print_list;
}


/**
 * @brief Frees an hashtable entry
 * 
 * @param key Key of entry
 * @param value Data to be freed
 * @param user_data Data to be passed to the function
 */
void free_func_hash(gpointer key, gpointer value, gpointer user_data){
    CNT_VALUE data = value;
    free(data->value);
    free(value);
    free(key);
}


/**
 * @brief Frees an hash
 * 
 * @param hash Hash to be freed
 */
void free_hash(GHashTable *hash){
    g_hash_table_foreach(hash, free_func_hash, NULL);
    g_hash_table_destroy(hash);
}


/**
 * @brief Free a node of a list
 * 
 * @param data Data to be freed
 */
void free_func_list(gpointer data){
    L_NODE value = data;
    free(value->key);
    free(value->value);
    free(data);
}


/**
 * @brief Frees a list
 *
 * @param list Pointer to the beginning of list
 */
void free_list(GList *list){
    g_list_free_full(list, free_func_list);
}