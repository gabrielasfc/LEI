#ifndef COUNTER_HASH_
#define COUNTER_HASH_

#include <glib.h>
#include <stdio.h>

typedef struct count_node* CNT_NODE;

int increment(void* key, GHashTable* hash);

GList* to_list(GHashTable* old, int N);

void free_list(GList* l);

void free_string_list(GList* list);

void print_n_first(GList* list, int N, FILE* output, void (*print_func)(FILE*, void*, int, void*), void* traverse_data);

void print_list(GList* list, FILE* output, void (*print_func)(FILE*, void*, int, void*), void* traverse_data);

char* get_cnt_node_value_str(CNT_NODE node);

int get_cnt_node_value_int(CNT_NODE node);

int get_cnt_node_count(CNT_NODE node);

GList* list_with_n_nodes(GList *list, int N);

struct count_node* to_arr(GHashTable* old, int N, int* num_elems);

void print_arr(struct count_node* arr, int N, void (*print_fn)(FILE*, void*, int, void*), FILE* output, void* traverse_data);

void free_arr(struct count_node* arr, int occupied);

#endif