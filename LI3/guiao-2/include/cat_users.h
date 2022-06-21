#ifndef CAT_USERS_
#define CAT_USERS_

typedef struct cat_users *Cat_Users;
typedef char user_type;
typedef struct user *User;

void *get_hash_from_string(char *string);

user_type check_type(char *str);

User create_user(char **fields);

Cat_Users create_users_cat();

Cat_Users insert_user(char *key, User data, Cat_Users cat_users);

User search_user(char *key, Cat_Users cat_users);

int get_cat_users_length(Cat_Users cat_users);

void users_for_each(Cat_Users cat_users, GHFunc func, gpointer traverse_data);

char *get_user_login(User data);

char get_user_type(User data);

int find_in_following_list(User us, char *id);

int find_in_follower_list(User us, char *id);

void print_users(Cat_Users cat_users);

void free_users(Cat_Users cat_users);

#endif