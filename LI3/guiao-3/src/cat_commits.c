/**
 @file cat_commits.c
 @brief File containing structures and functions related to commits catalogue
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/cat_commits.h"


/**
 * @brief Date struct
 */
typedef struct date{ /** Date struct **/
    char day; /** Day **/
    char month; /** Month **/
    int year; /** Year **/
} *Date;


/**
 * @brief Commits catalogue struct
 */
struct cat_commits{ /** Commits catalogue **/
    FILE *hash; /** Where the hashtable will be stored **/
    GHashTable *index; /** Index from the commits' positions on file **/
    GList *aux_list; /** Array that will be sorted after all insertions and sent to the file **/
    int file_size; /** Commits' file size **/
};


/**
 * @brief Commit struct
 */
struct commit{ /** Commit struct **/
    int repo_id; /** Repo id (key) **/
    int author_id; /** Author id **/
    int committer_id; /** Commiter id **/
    char commit_date_day; /** Commit Day **/
    char commit_date_month; /** Commit Month **/
    int commit_date_year; /** Commit Year **/
    int msg_ln; /** Commit message length **/
};


/**
 * @brief Struct to store number of commits and start position index from repository on commits file
 */
struct repo_info{ /** Repo info struct **/
    int start_pos; /** First commit index **/
    char num_commits; /** Number of commits **/
};


/**
 * @brief Creates commits catalogue
 *
 * @return The newly created commits cat
 */
Cat_Commits create_commits_cat(){
    Cat_Commits cat_commits = malloc(sizeof(struct cat_commits));
    cat_commits->hash = NULL;
    cat_commits->index = g_hash_table_new(g_int_hash, g_int_equal);
    cat_commits->aux_list = NULL;
    cat_commits->file_size = 0;

    return cat_commits;
}


/**
 * @brief Create a commit with given fields; Allocates memory
 *
 * @param fields Array of strings containing the fields to be passed to the commit object
 * 
 * @return The newly created commit
 */
Commit create_commit(char* fields[5]){
    Commit commit = malloc(sizeof(struct commit));
    commit->repo_id = atoi(fields[0]);
    commit->author_id = atoi(fields[1]);
    commit->committer_id = atoi(fields[2]);
    commit->msg_ln = strlen(fields[4]);

    char* str_date = strdup(fields[3]);
    char* backup = str_date;
    commit->commit_date_year= atoi(strsep(&str_date, "-"));
    commit->commit_date_month = (char)atoi(strsep(&str_date, "-"));
    commit->commit_date_day = (char)atoi(strsep(&str_date, " \0"));

    free(backup);

    return commit;
}


/**
 * @brief Checks if a commit exists in commits catalogue
 * 
 * @param cat_commits Commits catalogue
 * @param repo_id Repo_id to search
 * 
 * @return 1 if the given repo_id is found, 0 otherwise
 */
int check_commit(Cat_Commits cat_commits, int repo_id){
    return g_hash_table_lookup(cat_commits->index, &repo_id) != NULL;
}


/**
 * @brief Search a given repo_id in the catalogue
 *
 * @param cat_commits Reference to the commits catalogue
 * @param repo_id Repo id from the commit to be found
 * 
 * @return First commit from that repo (the one with the oldest commit)
 */
Commit search_commit(Cat_Commits cat_commits, int repo_id){
    R_Info r_info = g_hash_table_lookup(cat_commits->index, &repo_id);

    Commit commit_check = malloc(sizeof(struct commit));
    fread(commit_check, sizeof(struct commit), 1, cat_commits->hash);

    if(commit_check != NULL && commit_check->repo_id == repo_id){
        return commit_check;
    }

    free(commit_check);
    
    if (r_info != NULL){
        Commit commit = malloc(sizeof(struct commit));
        fseek(cat_commits->hash, r_info->start_pos, 0);
        fread(commit, sizeof(struct commit), 1, cat_commits->hash);
        return commit;
    }

    return NULL;
}


/**
 * @brief Insert a commit in the catalogue in memory
 *
 * @param cat_commits Reference to the commits catalogue
 * @param fields Array of strings containing the fields to be passed to the commit object
 * 
 * @return 0 - Success
 */
int insert_commit(Cat_Commits cat_commits, char* fields[4]){
    Commit commit = create_commit(fields);
    cat_commits->aux_list = g_list_prepend(cat_commits->aux_list, commit);

    return 0;
}


/**
 * @brief Applies a function to all entries of commits indexes hash
 * 
 * @param cat_commits Commits catalog
 * @param func Function to be applied
 * @param data Data passed to the function
 */
void commits_foreach(Cat_Commits cat_commits, GHFunc func, gpointer data){
    g_hash_table_foreach(cat_commits->index, func, data);
}


/**
 * @brief Traverses the commits file applying a function to each commit
 * 
 * @param cat_commits Commits catalogue
 * @param func Function that will be applied to each commit
 * @param traverse_data Data to be passed to the function
 */
void traverse_commits(Cat_Commits cat_commits, void (*func)(Commit, void*), void* traverse_data){
    FILE* commits = cat_commits->hash;
    fseek(commits, 0, SEEK_SET);
    int i=0;
    struct commit commit;

    while (i<cat_commits->file_size){
        fread(&commit, sizeof(struct commit), 1, commits);
        func(&commit, traverse_data);
        i++;
    }
}


/**
 * @brief Frees a commit
 * 
 * @param data Commit to be freed
 */
void free_commit(gpointer data){
    Commit commit = (Commit)data;
    free(commit);
}


/**
 * @brief Frees an entry in the indexes hash
 * 
 * @param key Entry key
 * @param value Entry value
 * @param data Data to pass to the function
 */
void free_cat_commits_entry(gpointer key, gpointer value, gpointer data){
    R_Info repo_info = (R_Info) value;
    free(repo_info);
    free(key);
}


/**
 * @brief Frees commits catalogue
 * 
 * @param cat_commits Commits catalogue
 */
void free_cat_commits(Cat_Commits cat_commits){
    g_hash_table_foreach(cat_commits->index, free_cat_commits_entry, NULL);
    g_hash_table_destroy(cat_commits->index);
    free(cat_commits->hash);
    free(cat_commits);
}


/**
 * @brief Auxiliar function that compare dates to be used in the cmpfunc
 * 
 * @param d1_year Date 1 year
 * @param d1_month Date 1 month
 * @param d1_day Date 1 day
 * @param d2_year Date 2 year
 * @param d2_month Date 2 month
 * @param d2_day Date 2 day
 */
int cmp_dates(int d1_year, char d1_month, char d1_day, int d2_year, char d2_month, char d2_day){
    int diffD, diffM, diffY;

    diffY = d2_year - d1_year;
    if (diffY) return diffY;

    diffM = d2_month - d1_month;
    if (diffM) return diffM;

    diffD = d2_day - d1_day;
    if (diffD) return diffD;

    return 0; // Datas iguais
}


/**
 * @brief Utility function to sort the structure in memory
 *
 * @param a Reference to the first commit
 * @param b Reference to the second commit
 * 
 * @return Difference between their repo_ids or between their message lengths
 */
int cmpfunc (const void * a, const void * b) {
    Commit c_a = (Commit)(a);
    Commit c_b = (Commit)(b);


    int r = c_a->repo_id - c_b->repo_id;
    if (r == 0){
        r = cmp_dates(c_a->commit_date_year, c_a->commit_date_month, c_a->commit_date_day, c_b->commit_date_year, c_b->commit_date_month, c_b->commit_date_day);
    }

   return r; 
}


/**
 * @brief Puts all important data from the stored commits into a file (binary)
 *        Inserts the data in sorted order
 *
 * @param cat_commits Reference to the commits catalogue
 * 
 * @return 0 - Success
 */
int commits_memory_to_file(Cat_Commits cat_commits){
    FILE* fp = cat_commits->hash = fopen("saida/COMMITS.bin", "wb+");
    GList* l = cat_commits->aux_list, *free_list;

    l = g_list_sort(l, cmpfunc);
    free_list = l;
    
    fseek(fp, 0, SEEK_SET);

    int i=0; // The total number of commits
    char commit_count=0; // The number of commits of the current repo
    int* repo_id = malloc(sizeof(int)); *repo_id = ((Commit)(l->data))->repo_id; // Current repo_id
    long int file_pos = 0; // Position of the beginning of the commits from that repo
    int num_repos=0;
    
    while (l){
        if (((Commit)(l->data))->repo_id != *repo_id){ // OTIMIZAR         

            R_Info repo_info = malloc(sizeof(struct commit));
            repo_info->num_commits = commit_count;
            repo_info->start_pos = file_pos;

            g_hash_table_insert(cat_commits->index, repo_id, repo_info);
            num_repos++;

            commit_count = 0;

            repo_id = malloc(sizeof(int));
            *repo_id = ((Commit)(l->data))->repo_id;
            
            file_pos = ftell(fp);
        }

        Commit curr_commit = (Commit)(l->data); 
        fwrite(curr_commit, sizeof(struct commit), 1, fp);

        commit_count++; i++;
        l = l->next;
    }

    R_Info repo_info = malloc(sizeof(struct commit));
    repo_info->num_commits = commit_count;
    repo_info->start_pos = file_pos;

    g_hash_table_insert(cat_commits->index, repo_id, repo_info);

    cat_commits->file_size = i;

    g_list_free_full(free_list, free_commit);

    return 0;
}


/**
 * @brief Counts the number of repos with bots as collaborators
 * @note A collaborator is a user that is either an author or a committer
 *       of at least a commit in the repository
 * 
 * @param cat_commits Commits catalogue
 * @param id_bots HashTable containing the ids of all the bots found in users.csv
 * 
 * @return The number of repos with bots as collaborators
 */
int count_repos_with_bots(Cat_Commits cat_commits, GHashTable *id_bots){
    int cnt=0, i=0;
    FILE* commits = cat_commits->hash;
    GHashTable* repos_with_bots = g_hash_table_new(g_int_hash, g_int_equal);

    struct commit commit;
    fseek(commits, 0, 0);

    while (i < cat_commits->file_size){
        fread(&commit, sizeof(struct commit), 1, commits);
        if (!g_hash_table_lookup(repos_with_bots, &commit.repo_id) && (g_hash_table_lookup(id_bots, &commit.author_id) != NULL || g_hash_table_lookup(id_bots, &commit.committer_id) != NULL)) {
            g_hash_table_insert(repos_with_bots, &commit.repo_id, &commit.repo_id);
            cnt++;
        }
        i++;
    }
    g_hash_table_destroy(repos_with_bots);
    return cnt;
} 


/**
 * @brief Counts the total of collaborators in the commits catalogue
 * 
 * @param cat_commits Commits catalogue
 * 
 * @return Number of collaborators
 */
int count_total_collabs(Cat_Commits cat_commits){
    int total_collabs=0, i=0;
    FILE* commits = cat_commits->hash;

    struct commit commit;
    fseek(commits, 0, SEEK_SET);

    fread(&commit, sizeof(struct commit), 1, commits);

    while (i < cat_commits->file_size){
        GHashTable* collabs_of_repo = g_hash_table_new(g_int_hash, g_int_equal);
        int repo_id = commit.repo_id; // Id do primeiro commit referente a esse repositório

        do { // Avança até ao fim do ficheiro ou até ao próximo repositório
          if (commit.author_id == commit.committer_id && g_hash_table_lookup(collabs_of_repo, &commit.author_id) == NULL){
              total_collabs++;
              g_hash_table_insert(collabs_of_repo, &commit.author_id, &commit.author_id);
          } else {
              if (g_hash_table_lookup(collabs_of_repo, &commit.author_id) == NULL) { total_collabs++; g_hash_table_insert(collabs_of_repo, &commit.author_id, &commit.author_id); }
              if (g_hash_table_lookup(collabs_of_repo, &commit.committer_id) == NULL) { total_collabs++; g_hash_table_insert(collabs_of_repo, &commit.committer_id, &commit.committer_id); }
          }
          i++;
          if (i >= cat_commits->file_size) {g_hash_table_destroy(collabs_of_repo); return total_collabs;}
          else fread(&commit, sizeof(struct commit), 1, commits);
        } while (commit.repo_id == repo_id);

        g_hash_table_destroy(collabs_of_repo);
    }

    return total_collabs;
}


/**
 * @brief Converts a date string to struct Date
 * 
 * @param date String with date to convert
 * 
 * @return Date
 */
Date string_to_date(char *date){
    char *buffer = strdup(date);
    char *backup = buffer;
    Date final_date = malloc(sizeof(struct date));

    final_date->year= atoi(strsep(&buffer, "-"));
    final_date->month = (char)atoi(strsep(&buffer, "-"));
    final_date->day = (char)atoi(strsep(&buffer, " \0"));

    free(backup);
    return final_date;
}


/**
 * @brief Checks if a date is before the limit date
 * 
 * @param date_year Year from the date
 * @param date_month Month from the date
 * @param date_day Day from the date
 * @param lmt_date String with the limit date
 * 
 * @return 1 if the date is before, 0 otherwise
 */
int previous_date(int date_year, char date_month, char date_day, char *lmt_date){
    Date start_date = string_to_date(lmt_date);

    if(date_year > start_date->year){
        free(start_date);
        return 0;
    }
    if(date_year == start_date->year && date_month > start_date->month){
        free(start_date);
        return 0;
    }
    if(date_year == start_date->year && date_month == start_date->month && date_day > start_date->day){
        free(start_date);
        return 0;
    }

    free(start_date);
    return 1;
}


/**
 * @brief Checks if a date is after the limit date
 * 
 * @param date_year Year from the date
 * @param date_month Month from the date
 * @param date_day Day from the date
 * @param lmt_date String with the limit date
 * 
 * @return 1 if the date is after, 0 otherwise
 */
int future_date(int date_year, char date_month, char date_day, char *lmt_date){
    Date final_date = string_to_date(lmt_date);

    if(date_year > final_date->year){
        free(final_date);
        return 1;
    }
    if(date_year == final_date->year && date_month > final_date->month){
        free(final_date);
        return 1;
    }
    if(date_year == final_date->year && date_month == final_date->month && date_day >= final_date->day){
        free(final_date);
        return 1;
    }

    free(final_date);
    return 0;
}


/**
 * @brief Prints a commit and its information
 *
 * @param commit Commit to be printed
 */
void print_commit(Commit commit){
    if(commit != NULL){
        printf("Repo_id: %d\nAuthor_id: %d\nCommitter_id: %d\nMsg_ln: %d\n", commit->repo_id, commit->author_id, commit->committer_id, commit->msg_ln);
        printf("Date: %c - %c - %d\n", commit->commit_date_day, commit->commit_date_month, commit->commit_date_year);
        putchar('\n');
    }
    else printf("Commit inválido!\n");
}


/**
 * @brief Prints the commits catalog in order of repo_ids
 * 
 * @param cat_commits Commits catalog
 */
void print_cat_commits(Cat_Commits cat_commits){
    FILE* commits = cat_commits->hash;
    fseek(commits, 0, SEEK_SET);

    printf("Este ficheiro tem %d commits\n\n", cat_commits->file_size);
    
    for(int i=0; i<cat_commits->file_size; i++){
        struct commit com;
        fread(&com, sizeof(struct commit), 1, commits);
        print_commit(&com);
        putchar('\n');
    }
}


/**
 * @brief Gets the size of indexes hash
 * 
 * @param cat_commits Commits catalogue
 * 
 * @return Size
 */
int get_cat_commits_size(Cat_Commits cat_commits){
    return g_hash_table_size(cat_commits->index);
}


/**
 * @brief Gets number of commits from repo
 * 
 * @param repo_info Repo data
 * 
 * @return Number of commits
 */
int get_repo_info_num_commits(R_Info repo_info){
    return repo_info->num_commits;
}


/**
 * @brief Gets repo id from a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Repo_id
 */
int get_commit_repo_id(Commit commit_info){
    return commit_info->repo_id;
}


/**
 * @brief Gets author id from a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Author_id
 */
int get_commit_author_id(Commit commit_info){
    return commit_info->author_id;
}


/**
 * @brief Gets committer id from a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Committer_id
 */
int get_commit_committer_id(Commit commit_info){
    return commit_info->committer_id;
}


/**
 * @brief Gets message length from a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Message length
 */
int get_commit_msg_ln(Commit commit_info){
    return commit_info->msg_ln;
}


/**
 * @brief Gets the year from the date of a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Year when the commit was made
 */
int get_commit_date_year(Commit commit_info){
    return commit_info->commit_date_year;
}


/**
 * @brief Gets the month from the date of a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Month when the commit was made
 */
char get_commit_date_month(Commit commit_info){
    return commit_info->commit_date_month;
}


/**
 * @brief Gets the day from the date of a commit
 * 
 * @param commit_info Commit data
 * 
 * @return Day when the commit was made
 */
char get_commit_date_day(Commit commit_info){
    return commit_info->commit_date_day;
}


/**
 * @brief Auxiliar function that compares two commits by message lengths
 * 
 * @param a First commit
 * @param b Second commit
 * 
 * @return Difference beetwen message lengths
 */
int cmp_msg_ln(const void* a, const void* b){
    Commit c_a = (Commit) a;
    Commit c_b = (Commit) b;
    return c_b->msg_ln - c_a->msg_ln;
}


/**
 * @brief Builds an array of lists sorted by message length
 * 
 * @param cat_commits Commits catalogue
 * @param arr Array of lists
 * @param N First N
 * 
 * @return Number of repositories
 */
int sort_by_msg_ln(Cat_Commits cat_commits, GList* arr[], int N){
    FILE* commits = cat_commits->hash;
    fseek(commits, 0, SEEK_SET);
    int file_index = 0; int array_index=0;
    int curr_repo;

    while (file_index < cat_commits->file_size){
        Commit commit = malloc(sizeof(struct commit));
        fread(commit, sizeof(struct commit), 1, commits);
        if (file_index == 0) curr_repo = commit->repo_id;
        if (commit->repo_id != curr_repo){
            arr[array_index] = g_list_sort(arr[array_index], cmp_msg_ln);
            curr_repo = commit->repo_id;
            array_index++;
        }
        arr[array_index] = g_list_prepend(arr[array_index], commit); 
        file_index++;
    }
    arr[array_index] = g_list_sort(arr[array_index], cmp_msg_ln);
    array_index++;
    return array_index;
}