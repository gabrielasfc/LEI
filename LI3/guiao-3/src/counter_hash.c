/**
 @file counter_hash.c
 @brief Module to help on queries envolving counting to present top N
 */
#include <glib.h>
#include <stdio.h>
#include "../include/counter_hash.h"

/**
 * @brief Struct to store all relevant information for the counter_hash:
 *        value - a primitive data type stored dynamically (the key)
 *        count - how many elements of that value
 */
struct count_node{ /** Struct count node **/
    void* value; /** Pointer to data **/
    int cnt; /** Count **/
};


/**
 * @brief Create a count node object
 * 
 * @param value The value associated with that count
 * @param cnt How many elements for that value we will store
 * 
 * @return The newly created object
 */
CNT_NODE create_count_node(void* value, int cnt){
    CNT_NODE r = malloc(sizeof(struct count_node));
    r->value = value;
    r->cnt = cnt;

    return r;
}


/**
 * @brief Increment the counter of inc_data object or creates a new entry in the hash with counter equal to 1
 * 
 * @param key Data to be incremented or inserted
 * @param hash HashTable where we increment
 * 
 * @return 1 if new entry created, 0 if only the counter is incremented
 */
int increment(void* key, GHashTable* hash){
    int r = 0;
    int* found = g_hash_table_lookup(hash, key);
        
    if (found == NULL){
        int* new_count = malloc(sizeof(int)); *new_count = 1;
        g_hash_table_insert(hash, key, new_count);
        r = 1;
    }
    else (*found)++;
    return r;
}


/**
 * @brief Print the first N elements of a list according to supplied print function and traverse_data
 * 
 * @param list List we want to print
 * @param N Number of elements we want to print from the beginning
 * @param output Where we want to print
 * @param print_func How we want to print our data (data is in CNT_NODE format)
 * @param traverse_data Useful data that can be passed to our printing function at the time of printing
 */
void print_n_first(GList* list, int N, FILE* output, void (*print_func)(FILE*, void*, int, void*), void* traverse_data){
    int i=0;
    while (list && i<N){
        CNT_NODE c = (CNT_NODE) (list->data);
        print_func(output, c->value, c->cnt, traverse_data);
        list = list->next; i++;
    }
}


/**
 * @brief Prints the list given according to supplied print function and traverse_data
 * 
 * @param list List we want to print
 * @param output Where we want to print
 * @param print_func How we want to print out data (data is in CNT_NODE format)
 * @param traverse_data Useful data that can be passed to out printing function at the time of printing
 */
void print_list(GList* list, FILE* output, void (*print_func)(FILE*, void*, int, void*), void* traverse_data){
    while (list){
        CNT_NODE c = (CNT_NODE) (list->data);
        print_func(output, c->value, c->cnt, traverse_data);
        list = list->next;
    }
}


/**
 * @brief Compares the count of two nodes (for sorting)
 * 
 * @param node1 First node
 * @param node2 Second node
 * 
 * @return The difference between the first and the second counts
 */
gint cmp_count(gconstpointer node1, gconstpointer node2){
    return ((CNT_NODE)(node2))->cnt - ((CNT_NODE)(node1))->cnt;
}


/**
 * @brief Sort insertion of a given number of nodes on a list
 * 
 * @param list List where we are going to insert
 * @param node Node to insert
 * @param N Length of list
 * 
 * @return Updated list
 */
GList* g_list_insert_sorted_n(GList *list, CNT_NODE node, int N){
    GList *prev = NULL, *backup = list;

    if(list == NULL){
        list = g_list_alloc();
        list->data = node;
        list->prev = list->next = NULL;
        
        return list;
    }

    for(int i = 0; i < N && list; i++){
        CNT_NODE node_cmp = list->data;

        if(node->cnt >= node_cmp->cnt){
            GList *new = g_list_alloc();
            new->data = node;
            new->next = list;
            new->prev = prev;

            if(prev) prev->next = new;
            if(list) list->prev = new;
            if(new->prev == NULL) backup = new;

            return backup;
        }

        prev = list;
        list = list->next;
    }

    free(node->value);
    free(node);
    return backup;
}


/**
 * @brief Utility function to convert a hash to list (used in the traversal of the hash table)
 * 
 * @param key Key from the hash
 * @param value Value associated with that key
 * @param user_data Pointer to the list we want to form
 */
void node_to_list(gpointer key, gpointer value, gpointer user_data){
    void **traverse_data = user_data;
    GList** list = traverse_data[0];
    int *N = traverse_data[1];

    CNT_NODE new = create_count_node(key, *(int*)value);
    if(*N==0){
        *list = g_list_insert_sorted(*list, new, cmp_count);
    }
    else{
        *list = g_list_insert_sorted_n(*list, new, *N);
    }
    free((int*) value); // Frees the cnt of the old node because it is already in the list and we will not have a reference to it anymore
}


/**
 * @brief Creates a sorted list of counter nodes from an unsorted hash table
 *        Also frees memory allocated for the hash table (excluding the keys)
 * 
 * @param old Hashtable
 * @param N Length of list
 * 
 * @return The created sorted list
 */
GList* to_list(GHashTable* old, int N){
    GList* new = NULL;
    void *user_data[2] = {&new, &N};

    g_hash_table_foreach(old, node_to_list, user_data);
    g_hash_table_destroy(old);

    return new;
}


/**
 * @brief Frees a count_node object
 * 
 * @param data Count node object
 */
void free_count_node(gpointer data){
    free(((CNT_NODE)data)->value);
    free(data);
}


/**
 * @brief Frees a string
 * 
 * @param data Pointer to string
 */
void free_string(gpointer data){
    free(data);
}


/**
 * @brief Frees the list containing all count_node objects
 * 
 * @param l List we will free
 */
void free_list(GList* l){
    g_list_free_full(l, free_count_node);
}


/**
 * @brief Frees a list with strings
 * 
 * @param list List
 */
void free_string_list(GList* list){
    g_list_free_full(list, free_string);
}


/**
 * @brief Auxiliar function to free list node
 * 
 * @param data Data to free
 */
void free_func(gpointer data){
    free(data);
}


/**
 * @brief Given a list, reduces the length of that list and frees the removed nodes
 * 
 * @param list List
 * @param N New length of list
 * 
 * @return Updated list
 */
GList* list_with_n_nodes(GList *list, int N){
    GList *new = list, *ant=NULL;

    for(int i = 0; i < N && list; i++){

        ant = list;
        list=list->next;
    }

    if(ant) ant->next = NULL;
    if(list) list->prev = NULL;

    g_list_free_full(list, free_func);

    return new;
}


// Consequências nas queries: é preciso dereferenciar o apontador e libertar a memória
/**
 * @brief Get the value (a string) of a count node structure object
 * 
 * @param node Node we have
 * 
 * @return the duplicated value
 */
char* get_cnt_node_value_str(CNT_NODE node){
    return strdup(node->value);
}


/**
 * @brief Get the value (an int) of a count node structure object
 * 
 * @param node Node we have
 * 
 * @return the value
 */
int get_cnt_node_value_int(CNT_NODE node){
    return *(int*)node->value;
}


/**
 * @brief Get the count from a count_node
 * 
 * @param node Node we have
 * 
 * @return The count
 */
int get_cnt_node_count(CNT_NODE node){
    return node->cnt;
}