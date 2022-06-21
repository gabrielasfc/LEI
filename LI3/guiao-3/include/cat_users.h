#ifndef CAT_USERS
#define CAT_USERS

typedef struct cat_users *Cat_Users;
typedef struct user *User;
typedef char user_type;

Cat_Users create_users_cat();

user_type check_type(char *str);

int check_user(Cat_Users cat_users, int id);

User search_user(Cat_Users cat_users, int id);

int insert_user(Cat_Users cat_users, char* fields[5]);

void print_user(User us);

void free_cat_users(Cat_Users cat_users);

int get_cat_users_size(Cat_Users cat_users);

int get_user_id(User user);

char *get_user_login(User user);

char get_user_type(User user);

int find_in_following_list(User user, int id);

int find_in_follower_list(User user, int id);

void free_user(User user);

#endif
