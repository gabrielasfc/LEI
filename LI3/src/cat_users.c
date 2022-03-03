/**
 @file cat_users.c
 @brief File containing structures and functions related to users catalogue
 */
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/cat_users.h"


/**
 * @brief Macro that represents a user type
 */
#define Us 0


/**
 * @brief Macro that represents a Bot type
 */
#define Bot 1


/**
 * @brief Macro that represents a Organization type
 */
#define Org 2


/**
 * @brief Users catalogue struct
 */
struct cat_users{ /** Users catalogue **/
    FILE *hash; /** Where the hashtable will be stored **/
    GHashTable *index; /** Index from the users' positions on file **/
    int file_size; /** Users' file size **/
};


/**
 * @brief User struct
 */
struct user{ /** User struct **/
    int id; /** User id (key) **/
    char *login; /** User login **/
    int login_length; /** Login string length **/
    GHashTable *following; /** Hashtable with following id's **/
    GHashTable *followers; /** Hashtable with followers id's **/
    char type; /** User type **/
};


/**
 * @brief Struct to store the following and followers hashtables and file index from an user
 */
typedef struct hash_info{ /** User info struct **/
    int index; /** File index from user **/
    GHashTable *following; /** Hashtable with following id's **/
    GHashTable *followers; /** Hashtable with followers id's **/
} *H_Info;


/**
 * @brief Creates an users catalog object
 * 
 * @return Cat_Users
 */
Cat_Users create_users_cat(){
    Cat_Users cat_users = malloc(sizeof(struct cat_users));
    cat_users->hash = fopen("saida/USERS.bin", "wb+");
    cat_users->index = g_hash_table_new(g_int_hash, g_int_equal);
    cat_users->file_size = 0;

    return cat_users;
}


/**
 * @brief Determines the type
 *
 * @param str string to be verified
 *
 * @return the Type of user (User 0, Bot 1, Organization 2)
 */
user_type check_type(char *str){ // User = 0, Bot = 1, Org = 2;
    char r;

    if(!strcmp("User", str)) r = Us;
    else if(!strcmp("Bot", str)) r = Bot;
    else if(!strcmp("Organization", str)) r = Org;

    return r;
}


/**
 * @brief Puts the elements of a string in an hash table
 * 
 * @param string String delimited by [] and elements between ','
 * 
 * @return Pointer to the hash table
 */
void *get_hash_from_string(char *string){
    void *ht = NULL; 
    char *tok, *dup = strdup(string), *backup=dup;
    int p = 1;
    dup++;
    if (*dup != ']') ht = g_hash_table_new(g_int_hash, g_int_equal);
    while((tok = strsep(&dup, ",]")) != NULL && strcmp(tok, "\0") && dup != NULL){
        int* val = malloc(sizeof(int)); *val = atoi(tok);
        g_hash_table_insert(ht, val, &p);
        dup++;
    }
    free(backup);

    return ht;
}


/**
 * @brief Creates an user object; Allocates memory
 * 
 * @param fields List of user fields in string format
 * 
 * @return struct user
 */
struct user create_user(char* fields[5]){
    struct user user;

    user.id = atoi(fields[0]);
    user.login = fields[1];
    user.login_length = strlen(fields[1]);
    user.type = check_type(fields[2]);
    user.following = get_hash_from_string(fields[3]);
    user.followers = get_hash_from_string(fields[4]);

    return user;
}


/**
 * @brief Checks if an user exists in the catalogue
 * 
 * @param cat_users Users catalogue
 * @param id id to search
 * 
 * @return Bool
 */
int check_user(Cat_Users cat_users, int id){
    void *value = g_hash_table_lookup(cat_users->index, &id);

    return value != NULL;
}


/**
 * @brief Searches an user in users catalogue
 * 
 * @param cat_users Users catalogue
 * @param id id to search
 * 
 * @return User data
 */
User search_user(Cat_Users cat_users, int id){
    H_Info h = g_hash_table_lookup(cat_users->index, &id);

    if (h != NULL){
        User user = malloc(sizeof(struct user));

        fseek(cat_users->hash, h->index, 0);

        fread(&user->id, sizeof(int), 1, cat_users->hash);

        fread(&user->login_length, sizeof(int), 1, cat_users->hash);

        user->login = malloc(sizeof(char)*(user->login_length+1));
        fread(user->login, sizeof(char), user->login_length, cat_users->hash);
        user->login[user->login_length] = '\0';

        fread(&user->type, sizeof(char), 1, cat_users->hash);
        user->followers = h->followers;
        user->following = h->following;

        return user;
    }
    return NULL;
}


/**
 * @brief Inserts an user in users catalogue
 * 
 * @param cat_users Users catalogue
 * @param fields List of user fields in string format 
 * 
 * @return 0 if succeed
 */
int insert_user(Cat_Users cat_users, char* fields[5]){
    struct user user = create_user(fields);

    H_Info h = malloc(sizeof(struct hash_info));
    int *id = malloc(sizeof(int));
    *id = user.id;

    h->index = cat_users->file_size;
    h->followers = user.followers;
    h->following = user.following;

    fwrite(&user.id, sizeof(int), 1 , cat_users->hash);
    fwrite(&user.login_length, sizeof(int), 1, cat_users->hash);
    fwrite(user.login, sizeof(char), user.login_length, cat_users->hash);
    fwrite(&user.type, sizeof(char), 1, cat_users->hash);

    g_hash_table_insert(cat_users->index, id, h);

    cat_users->file_size += 2*sizeof(int) + (user.login_length+1)*sizeof(char);

    return 0;
}


/**
 * @brief Frees an user
 * 
 * @param user User to be freed
 */
void free_user(User user){
    free(user->login);
    free(user);
}


/**
 * @brief Frees an entry in the followers/following hash
 * 
 * @param key Entry key
 * @param value Entry value
 * @param data Data to pass to the function
 */
void free_hash_follow(gpointer key, gpointer value, gpointer data){
    free(key);
}


/**
 * @brief Frees an entry in the index hash
 * 
 * @param key Entry key
 * @param value Entry value
 * @param data Data to pass to the function
 */
void free_cat_users_entry(gpointer key, gpointer value, gpointer data){
    H_Info user_info = (H_Info) value;
    if(user_info->followers){
        g_hash_table_foreach(user_info->followers, free_hash_follow, NULL);
        g_hash_table_destroy(user_info->followers);
    }
    if(user_info->following){
        g_hash_table_foreach(user_info->following, free_hash_follow, NULL);
        g_hash_table_destroy(user_info->following);
    }
    free(user_info);
    free(key);
}


/**
 * @brief Frees an user catalogue
 * 
 * @param cat_users Users catalogue to be freed
 */
void free_cat_users(Cat_Users cat_users){
    g_hash_table_foreach(cat_users->index, free_cat_users_entry, NULL);
    g_hash_table_destroy(cat_users->index);
    free(cat_users->hash);
    free(cat_users);
}


/**
 * @brief Gets the size of index's hash
 * 
 * @param cat_users Users catalogue
 */
int get_cat_users_size(Cat_Users cat_users){
    return g_hash_table_size(cat_users->index);
}


/**
 * @brief Gets user id from an user;
 * 
 * @param user User data
 * 
 * @return ID
 */
int get_user_id(User user){
    return user->id;
}


/**
 * @brief Gets login from an user; Allocates memory
 * 
 * @param user User data
 * 
 * @return Login
 */
char *get_user_login(User user){
    return strdup(user->login);
}


/**
 * @brief Gets user_type from an user;
 * 
 * @param user User data
 * 
 * @return User type
 */
char get_user_type(User user){
    return user->type;
}


/**
 * @brief Searches an user by id in a following list from other user
 * 
 * @param user User that has the following list
 * @param id User id to search
 * 
 * @return 1 if id is in the list, 0 otherwise
 */
int find_in_following_list(User user, int id){
    if (!user) { printf("User inválido"); return -1; }
    if (user->following == NULL) return 0;
    int r = g_hash_table_lookup(user->following, &id) != NULL;
    return r;
}


/**
 * @brief Searches an user by id in a followers list from other user
 * 
 * @param user User that has the followers list
 * @param id User id to search
 * 
 * @return 1 if id is in the list, 0 otherwise
 */
int find_in_follower_list(User user, int id){
    if (!user) { printf("User inválido"); return -1; }
    if (user->followers == NULL) return 0;
    int r = g_hash_table_lookup(user->followers, &id) != NULL;
    return r;
}


/**
 * @brief Prints an hash entry
 * 
 * @param key Entry key
 * @param value Entry value
 * @param data Data to be passed to the function
 */
void print_node(void* key, void* value, void* data){
    printf("%d - %d\n", *(int*)key, *(int*)value);
}


/**
 * @brief Prints an hash
 * 
 * @param hash Hash to be printed
 */
void print_hash(GHashTable* hash){
    if (hash)
    g_hash_table_foreach(hash, print_node, NULL);
}


/**
 * @brief Prints user type
 * 
 * @param type User type
 */ 
void print_type(char type){
    switch (type){
      case 0: printf("User\n"); break;
      case 1: printf("Bot\n"); break;
      case 2: printf("Organization"); break;
      default: printf("Tipo inválido\n");
    }
}


/**
 * @brief Prints an user
 * 
 * @param user User to be printed
 */
void print_user(User user){
    if (user != NULL){
      printf("Id: %d\n", user->id);
      printf("Login: %s\n", user->login);
      printf("Type: "); print_type(user->type);
    }
    else printf("User inválido\n");
}