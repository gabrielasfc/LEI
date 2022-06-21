/**
 @file queries_aux.c
 @brief File that contains auxiliar functions used in more than 1 query resolution
 */
#include <glib.h>
#include "../../include/queries_aux.h"
#include "../../include/cat_commits.h"


/**
 * @brief Checks if the date is not after the limit date
 * 
 * @param day Day
 * @param mon Month
 * @param year Year
 * @param day_lmt Limit day
 * @param mon_lmt Limit month
 * @param year_lmt Limit year
 * 
 * @return 0 - is a future date, 1 - is not
 */
int not_future_date(int day, int mon, int year, int day_lmt, int mon_lmt, int year_lmt){   
    if (year < year_lmt) return 1;
    if (year == year_lmt && mon < mon_lmt) return 1;
    if (year == year_lmt && mon == mon_lmt && day <= day_lmt) return 1;
    return 0;
}


/**
 * @brief Checks if the date is not before the limit date
 * 
 * @param day Day
 * @param mon Month
 * @param year Year
 * @param day_lmt Limit day
 * @param mon_lmt Limit month
 * @param year_lmt Limit year
 * 
 * @return 0 - is a previous date, 1 - is not
 */
 int not_prev_date(int day, int mon, int year, int day_lmt, int mon_lmt, int year_lmt){
    if(year < year_lmt) return 0;
    else if(year == year_lmt && mon < mon_lmt) return 0;
    else if(year == year_lmt && mon == mon_lmt && day < day_lmt) return 0;
    else return 1;
}


/**
 * @brief Puts all entries of an hash in a linked list from GLib
 * 
 * @param key Key
 * @param data Data to list
 * @param traverse_data Pointer to first node of the new list
 */
void hash_to_list(void *key, void *data, void *traverse_data){
    void **pointer = traverse_data;
    GList *list = pointer[0];
    int (*cmpfnc) (const void*, const void*) = pointer[1];
    if(list->data==NULL){ 
        list->data = data;
    }
    else{
        pointer[0] = g_list_insert_sorted(list, data, cmpfnc);
    }
}


/**
 * @brief Checks if there is a commit in a repo after the limit date given
 * 
 * @param list List of commits with the same repo_id
 * @param lmt_date Limit date
 * 
 * @return 1 if there is a commit, 0 otherwise (repo is inactive from that date)
 */
int check_commit_after(GList *list, char *lmt_date){
    int r=0;
    
    struct tm LimitDate;
    strptime(lmt_date, "%Y-%m-%d", &LimitDate);
    
    while(list && r==0){
        void *data = list->data;
        char *commit_date = get_commit_commit_at(data);

        struct tm CommitDate;
        strptime(commit_date, "%Y-%m-%d", &CommitDate);

        if(not_prev_date(CommitDate.tm_mday, CommitDate.tm_mon+1, CommitDate.tm_year+1900, LimitDate.tm_mday, LimitDate.tm_mon+1, LimitDate.tm_year+1900)){
            r++;
        }
        list = list->next;

        free(commit_date);
    }

    return r;
}