/**
 @file cat_users.c
 @brief File containing structure of users catalog
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
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
 * @brief User struct
 */
struct user{ /** Struct for user **/
    char *login; /** Login of a user **/
    GHashTable *following; /** Hashtable with following id's **/
    GHashTable *followers; /** Hashtable with followers id's **/
    char type; /** Type of a user **/
};


/**
 * @brief Users catalog (currently an hashtable from glib)
 */
struct cat_users{ /** Users catalogue **/
    GHashTable *users; /** Hashtable for users **/
};


/**
 * @brief Puts the elements of a string in an hash table
 * 
 * @param string String delimited by [] and elements between ','
 * 
 * @return Pointer to the hash table
 */
void *get_hash_from_string(char *string){
    void *ht = g_hash_table_new(g_str_hash, g_str_equal);
    char *tok, *dup = strdup(string), *backup, *dTok;
    int p = 1;
    backup = dup;
    dup++;
    while((tok = strsep(&dup, ",]")) != NULL && strcmp(tok, "\0") && dup != NULL){
        dTok = strdup(tok);
        g_hash_table_insert(ht, dTok, &p);
        dup++;
    }
    free(backup);
    return ht;
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
 * @brief Creates an user object; Allocates memory
 * 
 * @param fields List of user fields in string format
 * 
 * @return User
 */
User create_user(char **fields){
    User user = malloc(sizeof(struct user));
    
    user->login = fields[1];
    user->type = check_type(fields[2]);
    user->followers = get_hash_from_string(fields[3]);
    user->following = get_hash_from_string(fields[4]);

    return user;
}


/**
 * @brief Creates an users catalog object
 * 
 * @return Cat_Users
 */
Cat_Users create_users_cat(){
    Cat_Users cat_users = malloc(sizeof(struct cat_users));
    cat_users->users = g_hash_table_new(g_str_hash, g_str_equal);

    return cat_users;
}


/**
 * @brief Inserts an user in users catalog
 * 
 * @param key Id from user to insert
 * @param data User data to insert
 * @param cat_users Users catalog
 * 
 * @return Updated users catalog
 */
Cat_Users insert_user(char *key, User data, Cat_Users cat_users){
    g_hash_table_insert(cat_users->users, key, data);

    return cat_users;
}


/**
 * @brief Searches an user in users catalog
 * 
 * @param key User id to search
 * @param cat_users Users catalog
 * 
 * @return User data
 */
User search_user(char *key, Cat_Users cat_users){
    return(g_hash_table_lookup(cat_users->users, key));
}


/**
 * @brief Gets the length of the hash in users catalog
 * 
 * @param cat_users Users catalog
 * 
 * @return Hash size
 */
int get_cat_users_length(Cat_Users cat_users){
    return g_hash_table_size(cat_users->users);
}


/**
 * @brief Applies a function to all entries of users hash
 * 
 * @param cat_users Users catalog
 * @param func Func to be applied
 * @param traverse_data Data to be passed to the function
 */
void users_for_each(Cat_Users cat_users, GHFunc func, gpointer traverse_data){
    g_hash_table_foreach(cat_users->users, func, traverse_data);
}


/**
 * @brief Gets login from an user; Allocates memory
 * 
 * @param data User data
 * 
 * @return Login
 */
char *get_user_login(User data){
    return strdup(data->login); 
}


/**
 * @brief Gets user_type from an user; Allocates memory
 * 
 * @param data User data
 * 
 * @return User type
 */
char get_user_type(User data){
    return data->type;
}


/**
 * @brief Searches an user by id in a following list from other user
 * 
 * @param us User that has the following list
 * @param id User id to search
 * 
 * @return 1 if id is in the list, 0 otherwise
 */
int find_in_following_list(User us, char *id){
    return g_hash_table_lookup(us->following, id) != NULL;
}


/**
 * @brief Searches an user by id in a followers list from other user
 * 
 * @param us User that has the followers list
 * @param id User id to search
 * 
 * @return 1 if id is in the list, 0 otherwise
 */
int find_in_follower_list(User us, char *id){
    return g_hash_table_lookup(us->followers, id) != NULL;
}


/**
 * @brief Prints user type
 * 
 * @param type User type
 */ 
void print_user_type(char type){
    if (type=='0') printf("User;");
    if (type=='1') printf("Bot;");
    if (type=='2') printf("Organization;");
}


/**
 * @brief Prints an user
 * 
 * @param key User id
 * @param user_data User data
 * @param traverse_data Data passed to the function
 */ 
void print_users_aux(void *key, void *user_data, void *traverse_data){
    User data = user_data;
    printf("%s;", (char*)key);
    printf("%s;", data->login);
    print_user_type(data->type);
    printf("\n"); //Missing followers and following hashtables
}


/**
 * @brief Prints users catalog data
 * 
 * @param cat_users Users catalog
 */
void print_users(Cat_Users cat_users){
    g_hash_table_foreach(cat_users->users, print_users_aux, NULL);
}


/**
 * @brief Frees followers and following hashtables
 * 
 * @param key Followers or following hashtables
 * @param value Value of each entry
 * @param hash_data Data to be passed to the function
 */
void free_follow_hash(void *key, void *value, void *hash_data){
    free(key);
}


/**
 * @brief Frees user struct
 * 
 * @param key Users hashtable
 * @param value User
 * @param user_data Data to be passed to the function
 */
void free_users_aux(void *key, void *value, void *user_data){
    User user = value;

    free((char*) user->login);
    
    if(g_hash_table_size(user->followers)){ g_hash_table_foreach(user->followers, free_follow_hash, NULL); g_hash_table_destroy(user->followers);}
    else g_hash_table_destroy(user->followers);

    if(g_hash_table_size(user->following)){ g_hash_table_foreach(user->following, free_follow_hash, NULL); g_hash_table_destroy(user->following);}
    else g_hash_table_destroy(user->following);

    free(key);
    free(user);
}


/**
 * @brief Frees users catalogue
 * 
 * @param cat_users Users catalogue
 */
void free_users(Cat_Users cat_users){
    g_hash_table_foreach(cat_users->users, free_users_aux, NULL);
    g_hash_table_destroy(cat_users->users);
    free(cat_users);
}