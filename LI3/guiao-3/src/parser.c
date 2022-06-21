/**
 @file parser.c
 @brief Module responsible for input files validation and parsing with statistical queries resolution
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/parser.h"

#define __XOPEN_SOURCE


/**
 * @brief Checks if a string is a positive integer
 *
 * @param val String to check
 * 
 * @return >=0 - valid, -1 - invalid
 */
int val_num(char *val){
    return (*val == '0' || atoi(val) > 0) - 1;
}


/**
 * @brief Checks if a string is valid
 *
 * @param val String to check
 * 
 * @return >=0 - valid, -1 - invalid
 */
int val_string(char *val){
	return 0;
}


/**
 * @brief Checks if a day is valid depending on the month and if it is a leap year or not
 *
 * @param day Day
 * @param mon Month
 * @param year Year
 * 
 * @return 1 - valid, 0 - invalid
 */
int val_days(int day, int mon, int year){
    if(day<=0) return 0;

    if((mon==1 || mon==3 || mon==5 || mon==7 || mon==8 || mon==10 || mon==12) && day<=31) return 1;

    //Leap years cases
    int b = year%4==0;
    if(mon==2 && b && day<=29) return 1;
    else if(mon==2 && !b && day<=28) return 1;

    else if(mon<=12 && day<=30) return 1;

    else return 0;
}


/**
 * @brief Checks if the date is not after the current time on system
 *
 * @param day Day
 * @param mon Month
 * @param year Year
 * 
 * @return 0 - is a future date, 1 - is not
 */
int not_after_current_date(int day, int mon, int year){
    if (year < 2022) return 1;
    if (year == 2022 && mon < 2) return 1;
    if (year == 2022 && mon == 2 && day <= 5) return 1;
    return 0;
}


/**
 * @brief Checks if the date is not before April 07 2005
 *
 * @param day Day
 * @param mon Month
 * @param year Year
 * 
 * @return 0 - is a previous date, 1 - is not
 */
 int not_before_date(int day, int mon, int year){
    if(year<2005) return 0;
    else if(year==2005 && mon<4) return 0;
    else if(year==2005 && mon==4 && day<7) return 0;
    else return 1;
}


/**
 * @brief Checks if a date is valid and in the right format
 *
 * @param val String to check
 * 
 * @return >=0 - valid, -1 - invalid
 */
int val_date(char *val){
    char *test;
    struct tm date;

    test = strptime(val, "%Y-%m-%d %H:%M:%S", &date);

    if (test!=NULL && *test=='\0' && val_days(date.tm_mday, date.tm_mon+1, date.tm_year+1900) && not_before_date(date.tm_mday, date.tm_mon+1, date.tm_year+1900) && not_after_current_date(date.tm_mday, date.tm_mon+1, date.tm_year+1900))
    return 0;
    else return -1;
}


/**
 * @brief Checks if a list is valid or not
 *        For it to be valid, all elements must be integers and must be separated
 *        by commas
 *
 * @param val String to check
 * 
 * @return >= 0 - valid (also returns length of list), -1 - invalid
 */
int val_list(char *val){
    if (*val != '[') return -1;
    if (*(val+1) == ']') return 0;

    char *dup = strdup(val+1);
    char *backup = dup, *tok;
    int i=0;

    do{
        tok = strsep(&dup, ",]");
        i++;
    } while (dup != NULL && (val_num(tok)+1));

    free(backup);

    if (dup == NULL) return i-1;
    else return -1;
}


/**
 * @brief Checks if a type is valid or not
 *
 * There are 3 possible type values: User, Bot and Organization
 *
 * @param val String to check
 * 
 * @return >=0 - valid, -1 - invalid
 */
int val_type(char *val){
    return (!strcmp(val, "User") || !strcmp(val, "Bot") || !strcmp(val, "Organization")) - 1;
}


/**
 * @brief Checks if a string is a boolean value (True or False)
 *
 * @param val String to check
 * 
 * @return >=0 - valid, -1 - invalid
 */
int val_bool(char *val){
    return(!strcmp(val, "True") || !strcmp(val, "False") - 1);
}


/**
 * @brief Frees a bot key
 * 
 * @param data Key
 */
void free_bot_key(gpointer data){
    free(data);
}


/**
 * @brief Puts the fields given by the positions array into an array of fields
 *        Duplicates memory for fields
 *        Uses the input string without creating a duplicate
 *
 * @param line Line with the fields separated by some delim
 * @param fields Array to be set with the wanted fields
 * @param positions Relative positions of the desired fields in the line
 * @param num_positions Number of fields
 */
void get_fields(char* line, char** fields, int* positions, int num_positions){
    int i, j;
    char* field, *delims = ";\r\n";

    for(i=0, j=0; i<=positions[num_positions-1] && line != NULL; i++){         // i traverses the line elements
        field = strdup(strsep(&line, delims));                                 // j traverses the fields array
        if (i == positions[j])  fields[j++] = field;
        else free(field);
    }
}


/**
 * @brief Checks the type of each user, increments in the array and insert the bots in an hash
 * 
 * @param fields Array with the fields
 * @param type_array Array to be incremented
 * @param id_bots Hashtable with the bots ids
 */
void type_interpreter(char **fields, int *type_array, GHashTable *id_bots){
    char type = check_type(fields[2]);

    if(type == 0) type_array[0]++;
    else if(type == 1){ 
        int *p = malloc(sizeof(int));
	    *p = atoi(fields[0]); 
        g_hash_table_insert(id_bots, p, p); 
        type_array[1]++;
    }
    else if(type == 2) type_array[2]++;
}


/**
 * @brief Validates a line
 * 
 * @param line Line
 * @param N Number of fields to validate
 * @param validators Functions to validate the fields
 * 
 * @return 0 if invalid, else valid 
 */
int validate_line(char *line, int N, int (*validators[])(char *val)){
    int is_valid = 1, x, i=0, y;

    char *dup = strdup(line), *token, *backup; // We cannot change the buffer
    backup = dup; // And we have to store the beginning of the line because strsep changes the pointer

    for (i=0; i<N; i++){
        token = strsep(&dup, "\r;\n");
        if ((token == NULL || *(token) == '\0') && (N!=5 || i!=4) && (N!=14 || i!= 5)) { is_valid = 0; break; }
        else {
            x = validators[i](token);
            is_valid = is_valid && x+1;
        }
        if (i<N-1 && validators[i+1] == val_list) y = atoi(token);
        if (validators[i] == val_list)
            is_valid = is_valid && x == y;
    }

    free(backup);

    return is_valid;
}


/**
 * @brief Makes the data crossing with commits
 * 
 * @param line Line
 * @param cat_users Users catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return 0 if invalid, else valid
 */
int data_crossing_commits(char *line, Cat_Users cat_users, Cat_Repos cat_repos){
    int ret = 0;
    char *dup = strdup(line), *backup;
    backup = dup;

    char *repo_id, *id1, *id2;

    repo_id = strsep(&dup, ";");
    id1 = strsep(&dup, ";"); //author_id
    id2 = strsep(&dup, ";"); //committer_id

	if(!strcmp(id1,id2) && check_user(cat_users, atoi(id1)) && check_repo(cat_repos, atoi(repo_id))) ret=1;
    else if(strcmp(id1,id2) && check_user(cat_users, atoi(id1)) && check_user(cat_users, atoi(id2)) && check_repo(cat_repos, atoi(repo_id))) ret=1;

    free(backup);

    return ret;
}


/**
 * @brief GHFunc used in the repositories data crossing
 * 
 * @param key Key
 * @param value Value associated to the key
 * @param data Data to be passed to the function
 * 
 * @return 1 if valid else 0
 */
gboolean cross_repos(gpointer key, gpointer value, gpointer data){
    void **traverse_data = data;
    Cat_Commits cat_commits = traverse_data[0];
    Cat_Users cat_users = traverse_data[1];
    Cat_Repos cat_repos = traverse_data[2];
    Repo repo = search_repo(cat_repos, *(int* )key);

    if(!check_commit(cat_commits, *(int *)key) || !check_user(cat_users, get_repo_owner_id(repo)) ) { free_repo(repo); return 1; }

    free_repo(repo);

    return 0;
}


/**
 * @brief Makes the data crossing with repositories
 * 
 * @param cat_commits Commits catalogue
 * @param cat_repos Repositories catalogue
 * @param cat_users Users catalogue
 */
void data_crossing_repos(Cat_Commits cat_commits, Cat_Repos cat_repos, Cat_Users cat_users){
    void *traverse_data[3] = {cat_commits, cat_users, cat_repos};

    repos_foreach_remove(cat_repos, cross_repos, traverse_data);
}


/**
 * @brief Parses the user files, copies the important data to a structure and calculates the statistical values for queries 1-> 4
 *
 * @param user_types Array to store the number of Users, Bots and Orgs found
 * @param idbots Array containing the ids (user_ids) of the bots
 * @param cat_users Users catalog
 */
void users_to_catalogue_with_parsing(int *user_types, GHashTable *idbots, Cat_Users cat_users){  // adicionar estrutura de dados para armazenar os ids dos bots
    FILE *f_users = fopen("entrada/users-g3.csv", "r");

    if (f_users == NULL) { puts("Missing file in users parser"); return; }

    int (*user_validators [10]) (char *val) = {val_num, val_string, val_type, val_date, val_num, val_list, val_num, val_list, val_num, val_num};
    char buffer[1000000];
    int num_fields = 5;
    char* fields[num_fields]; // Array of strings: fields to be sent to structure
    int fields_pos[] = {0, 1, 2, 5, 7}; // Relative position of the desired fields in the line

    for(int i=0; i<3; i++) user_types[i] = 0; // 0's the array of frequencies of Users, Bots and Orgs

    fgets(buffer, 1000000, f_users); // Gets first line

    while(fgets(buffer, 1000000, f_users)!=NULL){
        if(validate_line(buffer, 10, user_validators)){
            get_fields(buffer, fields, fields_pos, num_fields);
            insert_user(cat_users, fields);
            type_interpreter(fields, user_types, idbots);

            free(fields[0]);
            free(fields[1]);
            free(fields[2]);
            free(fields[3]);
            free(fields[4]);
        }
    }

    fclose(f_users);
}


/**
 * @brief Parses the repos files, copies the important data to a structure and calculates the statistical values for queries 1 -> 4
 *
 * @param idbots Array containing the ids (user_ids) of the bots
 * @param cat_commits Commits catalogue
 * @param cat_repos Repositories catalogue
 * @param cat_users Users catalogue
 */
void repos_to_catalogue_with_parsing(GHashTable *idbots, Cat_Commits cat_commits, Cat_Repos cat_repos, Cat_Users cat_users){
    FILE *f_repos = fopen("entrada/repos-g3.csv", "r");

    if (f_repos == NULL) { puts("Missing file in repos parser"); return; }

    int (*repo_validators [14]) (char *val) = {val_num, val_num, val_string, val_string, val_bool, val_string, val_string, val_string, val_date, val_date, val_num, val_num, val_num, val_num};
    int num_fields = 4;
    char buffer[1000000];
    char* fields[num_fields];
    int fields_pos[] = {0, 1, 5, 6};

    fgets(buffer, 1000000, f_repos); //Gets first line

    while (fgets(buffer, 1000000, f_repos) != NULL){
        if (validate_line(buffer, 14, repo_validators)){
            get_fields(buffer, fields, fields_pos, num_fields);
            if (check_user(cat_users, atoi(fields[1]))){
                insert_repo(cat_repos, fields);
            }
            free(fields[0]);
            free(fields[1]);
            free(fields[2]);
            free(fields[3]);
        }
    }

    fclose(f_repos);
}


/**
 * @brief Parses the commits files, copies the important data to a structure and calculates the statistical values for queries 1-> 4
 *
 * @param count_commits Integer to store the number of commits
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void commits_to_catalogue_with_parsing(int *count_commits, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    FILE* commits_input = fopen("entrada/commits-g3.csv", "r");

    if (commits_input == NULL) { puts("Missing file in commits parser"); return; }

    int (*commit_validators [5]) (char *val) = {val_num, val_num, val_num, val_date, val_string};
    char buffer[1000000];
    int num_fields = 5;
    int fields_pos[] = {0, 1, 2, 3, 4};
    char *fields[num_fields];

    fgets(buffer, 1000000, commits_input);

    while(fgets(buffer, 1000000, commits_input)!=NULL) {
        if(validate_line(buffer, 5, commit_validators) && data_crossing_commits(buffer, cat_users, cat_repos)){
            get_fields(buffer, fields, fields_pos, 5);
            insert_commit(cat_commits, fields);
            (*count_commits)++;

            free(fields[0]);
            free(fields[1]);
            free(fields[2]);
            free(fields[3]);
            free(fields[4]);
        }
    }

    fclose(commits_input);
}


/**
 * @brief Parser function that insert data in the catalogues
 * 
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repositories catalogue
 *
 * @return Array with the statistical queries
 */
void **data_to_catalogues_with_parsing(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    int *user_types = calloc(3, sizeof(int)); //Stores the number of users, bots and organizations
    int query3 = -1, count_commits = 0, count_collabs = 0, count_repos = 0, count_users = 0;
    float query2 = 0, query4 = 0;
    GHashTable *id_bots = g_hash_table_new_full(g_int_hash, g_int_equal, free_bot_key, NULL);

    users_to_catalogue_with_parsing(user_types, id_bots, cat_users);
    repos_to_catalogue_with_parsing(id_bots, cat_commits, cat_repos, cat_users);
    commits_to_catalogue_with_parsing(&count_commits, cat_users, cat_commits, cat_repos);

    commits_memory_to_file(cat_commits);

    data_crossing_repos(cat_commits, cat_repos, cat_users);

    count_collabs = count_total_collabs(cat_commits);
    count_repos = get_cat_repos_size(cat_repos);
    query2 = (float)count_collabs / (float)count_repos;
    
    query3 = count_repos_with_bots(cat_commits, id_bots);

    count_users = get_cat_users_size(cat_users);
    query4 = (float)count_commits / (float)count_users;


    void **queries = malloc(4*sizeof(void*));
    queries[0] = user_types;
    queries[1] = (float*)&query2;
    queries[2] = &query3;
    queries[3] = (float*)&query4;

    g_hash_table_remove_all(id_bots);
    g_hash_table_destroy(id_bots);
    
    return queries;
}
