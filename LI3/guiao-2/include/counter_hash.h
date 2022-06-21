#ifndef COUNTER_HASH_
#define COUNTER_HASH_

typedef struct value_count* CNT_VALUE;
typedef struct list_node* L_NODE;

int increment(char* key, void* inc_data, GHashTable** hash);
GList* present_N(GHashTable* hash, void (*print_node)(void*, FILE* ), int N, FILE* output);
void print_hash(GHashTable *hash, FILE *output);
void *get_value_from_list_node(L_NODE node);
int get_count_from_list_node(L_NODE node);
char* get_nd_key(L_NODE node);
void* get_nd_value(L_NODE node);
int get_nd_count(L_NODE node);
void free_hash(GHashTable *hash);
void free_list(GList *list);

#endif