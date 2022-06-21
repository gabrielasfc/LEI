/**
 @file parser.c
 @brief File containing input files parsing and responsible for statistical queries
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/cat_commits.h"
#include "../include/cat_repos.h"
#include "../include/cat_users.h"
#include "../include/parser.h"


/**
 * @brief Puts the fields given by the positions array into an array of fields
 * Duplicates memory for fields
 * Uses the input string without creating a duplicate
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
        field = strdup(strsep(&line, delims));          // j traverses the fields array
        if (i == positions[j])  fields[j++] = field;
        else free(field);
    }
}


/**
 * @brief Parses the user files, copies the important data to a structure and calculates the statistical values for queries 1-> 4 
 * 
 * @param user_types Array to store the number of Users, Bots and Orgs found
 * @param idbots Array containing the ids (user_ids) of the bots
 * @param cat_users Users catalog
 */
void parser_users(int *user_types, GHashTable *idbots, Cat_Users cat_users){  // adicionar estrutura de dados para armazenar os ids dos bots
    FILE *f_users = fopen("entrada/users-g2.csv", "r");

    if (f_users == NULL) { puts("Missing file in users parser"); return; }

    int count_user = 0, count_bot = 0, count_org = 0, num_fields = 5, us_type;
    char buffer[1000000];
    char* fields[num_fields]; // Array of strings: fields to be sent to structure
    int fields_pos[] = {0, 1, 2, 5, 7}; // Relative position of the desired fields in the line
    User data;

    for(int i=0; i<3; i++) user_types[i] = 0; // 0's the array of frequencies of Users, Bots and Orgs

    fgets(buffer, 1000000, f_users); // Gets first line

    while(fgets(buffer, 1000000, f_users)!=NULL){
        get_fields(buffer, fields, fields_pos, num_fields); //Gets the useful fields into fields array
        data = create_user(fields); // Creates a user given those fields
        insert_user(fields[0], data, cat_users); // Inserts the user into the hash


        us_type = check_type(fields[2]);
        if(us_type == 0) count_user++;
        else if(us_type == 1){ g_hash_table_insert(idbots, fields[0], fields[0]); count_bot++; } // We must get all bots ids for query 3
        else if(us_type == 2) count_org++;
        free(fields[2]); free(fields[3]); free(fields[4]); // Free the non string fields in user
    }


    user_types[0] = count_user;
    user_types[1] = count_bot;
    user_types[2] = count_org;

    fclose(f_users);
}


/**
 * @brief Parses the repos files, copies the important data to a structure and calculates the statistical values for queries 1 -> 4 
 * 
 * @param info Array to store info from statistical queries
 * @param idbots Array containing the ids (user_ids) of the bots
 * @param cat_commits Commits catalog
 * @param cat_repos Repositories catalog
 */
void parser_repos(int *info, GHashTable *idbots, Cat_Commits cat_commits, Cat_Repos cat_repos){
    FILE *f_repos = fopen("entrada/repos-g2.csv", "r");

    if (f_repos == NULL) { puts("Missing file in repos parser"); return; }
    
    int count_repos = 0, repos_with_bot = 0, num_fields = 4;
    int fields_pos[] = {0, 1, 5, 6};
    char buffer[1000000];
    char* fields[num_fields];
    void* data;

    fgets(buffer, 1000000, f_repos); // Gets first line

    while (fgets(buffer, 1000000, f_repos) != NULL){
        get_fields(buffer, fields, fields_pos, num_fields);
        data = create_repo(fields);
        insert_repo(fields[0], data, cat_repos);

        if(has_bots_in_repo(fields[0], cat_commits, idbots)) repos_with_bot++;
        count_repos++;
    }

    info[0] = count_repos;
    info[1] = repos_with_bot;

    fclose(f_repos);
}


/**
 * @brief Parses the commits files, copies the important data to a structure and calculates the statistical values for queries 1-> 4 
 * 
 * @param count_commits Integer to store the number of commits
 * @param count_collabs Integer to store the numbers of collabs
 * @param cat_commits Commits catalogue
 */
void parser_commits(int *count_commits, int *count_collabs, Cat_Commits cat_commits){
    FILE* commits_input = fopen("entrada/commits-g2.csv", "r");

    if (commits_input == NULL) { puts("Missing file in commits parser"); return; }
    
    char buffer[1000000];
    int n_commits = 0, num_fields = 5, collabs=0;
    int fields_pos[] = {0, 1, 2, 3, 4};
    char *fields[num_fields];
    Commit commit;

    fgets(buffer, 1000000, commits_input);

    while(fgets(buffer, 1000000, commits_input)!=NULL) {
        get_fields(buffer, fields, fields_pos, num_fields);

        collabs += collabs_counter(fields[0], fields[1], fields[2], cat_commits);

        commit = create_commit(fields);
        insert_commit(fields[0], commit, cat_commits);

        n_commits++;
        free(fields[4]);
    }
    *count_commits = n_commits;
    *count_collabs = collabs;

    fclose(commits_input);
}


/**
 * @brief Parses all the files and computes statistics
 * 
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void* parser(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    int* user_types = malloc(3*sizeof(int)); //Stores the number of users, bots and organizations
    int* info_repos = malloc(2*sizeof(int)); // 1st pos : number of repos, 2nd pos : number of bots in repos
    float query2 = 0, query4 = 0;
    int count_commits = 0, query3 = -1, count_collabs = 0;
    GHashTable *idbots = g_hash_table_new(g_str_hash, g_str_equal);

    parser_users(user_types, idbots, cat_users);
    parser_commits(&count_commits, &count_collabs, cat_commits); //colisao de keys
    parser_repos(info_repos, idbots, cat_commits, cat_repos);

    int count_total = user_types[0] + user_types[1] + user_types[2];

    query2 = (float)count_collabs / (float)info_repos[0];
    query3 = info_repos[1];
    query4 = (float)count_commits / (float)count_total;

    void** queries = malloc(4*sizeof(void*));
    queries[0] = user_types;
    queries[1] = &query2;
    queries[2] = &query3;
    queries[3] = &query4;
    
    g_hash_table_destroy(idbots);
    free(info_repos);

    return queries;
}