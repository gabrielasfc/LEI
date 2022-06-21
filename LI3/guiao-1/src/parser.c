/**
 * @file parser.c
 * @brief Set of functions to parse the lines of a .csv file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "arv.h"

#define __XOPEN_SOURCE

char *strptime(const char *s, const char *format, struct tm *tm);


/**
 * @brief Checks if a string is a positive integer
 * 
 * @param val String to check
 * @return >=0 - valid, -1 - invalid
 */
int valNum(char *val){
	return (*val == '0' || atoi(val) > 0) - 1; 
}


/**
 * @brief Checks if a string is valid
 * 
 * @param val String to check
 * @return >=0 - valid, -1 - invalid
 */
int valString(char *val){
	return 0;
}


/**
 * @brief Checks if a day is valid depending on the month and if it is a leap year or not
 * 
 * @param day Day
 * @param mon Month
 * @param year Year
 * @return 1 - valid, 0 - invalid
 */
int valDays(int day, int mon, int year){
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
 * @return 0 - is a future date, 1 - is not
 */
int notFutureDate(int day, int mon, int year){   
    if (year < 2021) return 1;
    if (year == 2021 && mon < 11) return 1;
    if (year == 2021 && mon == 11 && day <= 10) return 1;
    return 0;
}


/**
 * @brief Checks if the date is not before April 07 2005
 * 
 * @param day Day
 * @param mon Month
 * @param year Year
 * @return 0 - is a previous date, 1 - is not
 */
 int notPrevDate(int day, int mon, int year){
    if(year<2005) return 0;
    else if(year==2005 && mon<4) return 0;
    else if(year==2005 && mon==4 && day<7) return 0;
    else return 1;
}


/**
 * @brief Checks if a date is valid and in the right format
 * 
 * @param val String to check
 * @return >=0 - valid, -1 - invalid
 */
int valDate(char *val){
    char *test;
    struct tm date;

    test = strptime(val, "%Y-%m-%d %H:%M:%S", &date);

    if (test!=NULL && *test=='\0' && valDays(date.tm_mday, date.tm_mon+1, date.tm_year+1900) && notPrevDate(date.tm_mday, date.tm_mon+1, date.tm_year+1900) && notFutureDate(date.tm_mday, date.tm_mon+1, date.tm_year+1900))
    return 0;
    else return -1;
}


/**
 * @brief Checks if a list is valid or not
 * 
 * For it to be valid, all elements must be integers and must be separated
 * by commas
 * 
 * @param val String to check
 * @return >= 0 - valid (also returns length of list), -1 - invalid
 */
int valList(char *val){
    if (*val != '[') return -1;
    if (*(val+1) == ']') return 0;

    char *dup = strdup(val+1);
    char *backup = dup, *tok;
    int i=0;
    
    do{
        tok = strsep(&dup, ",]");
        int x = atoi(tok);
        i++;
    } while (dup != NULL && (valNum(tok)+1));

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
 * @return >=0 - valid, -1 - invalid
 */
int valType(char *val){
    return (!strcmp(val, "User") || !strcmp(val, "Bot") || !strcmp(val, "Organization")) - 1;
}


/**
 * @brief Checks if a string is a boolean value (True or False)
 * 
 * @param val String to check
 * @return >=0 - valid, -1 - invalid
 */
int valBool(char *val){
    return(!strcmp(val, "True") || !strcmp(val, "False") - 1);
}


void parse(FILE* input, int (*validators[])(char *val), int N, FILE *output){
    char *buffer = malloc(1000000), *dup, *backup, *token;
    int isValid, i, x, y;

    //Print first line
    fgets(buffer, 1000, input);
    fprintf(output, "%s", buffer);

    while (fgets(buffer, 1000000, input) != NULL){
        isValid = 1;
        i = 0;

        dup = strdup(buffer); // We cannot change the buffer
        backup = dup; // And we have to store the beginning of the line
                      // because strsep changes to pointer

        for (i=0; i<N; i++){
            token = strsep(&dup, "\r;\n");
            if ((token == NULL || *(token) == '\0') && (N!=5 || i!=4) && (N!=14 || i!= 5)) { isValid = 0; break; }
            else {
                x = validators[i](token);
                isValid = isValid && x+1;
            }
            if (i<N-1 && validators[i+1] == valList) y = atoi(token);
            if (validators[i] == valList) 
                isValid = isValid && x == y;
        }

        if (isValid) fprintf(output, "%s", buffer);

        free(backup);
    }
    free(buffer);
}


/**
 * @brief Discard lines that do not respect the formats of the respective fields
 */
void exercicio1(){
    FILE *usersF, *commitsF, *reposF; //ficheiros de entrada
	FILE *usersOK, *commitsOK, *reposOK; //ficheiros intermédios

    int (*userValidators [10]) (char *val) = {valNum, valString, valType, valDate, valNum, valList, valNum, valList, valNum, valNum};
    int (*commitValidators [5]) (char *val) = {valNum, valNum, valNum, valDate, valString};
    int (*repoValidators [14]) (char *val) = {valNum, valNum, valString, valString, valBool, valString, valString, valString, valDate, valDate, valNum, valNum, valNum, valNum};

    // Entry Files
    usersF = fopen("entrada/users.csv", "r");
    commitsF = fopen("entrada/commits.csv", "r");
    reposF = fopen("entrada/repos.csv", "r");

    // Output Files
    usersOK = fopen("saida/users-ok.csv", "w");
    commitsOK = fopen("saida/commits-ok.csv", "w");
    reposOK = fopen("saida/repos-ok.csv", "w");

    parse(usersF, userValidators, 10, usersOK);
    parse(commitsF, commitValidators, 5, commitsOK);
    parse(reposF, repoValidators, 14, reposOK);

    fclose(usersF); fclose(commitsF); fclose(reposF);
    fclose(usersOK); fclose(commitsOK); fclose(reposOK);
}


/**
 * @brief Cross-checks the data between the files, filtering invalid data
 */
void exercicio2(){
    FILE *usersOK, *commitsOK, *reposOK; //ficheiros intermédios
	FILE *reposf, *commitsf, *usersf; //ficheiros finais

    int i=0;

    usersOK = fopen("saida/users-ok.csv", "r");
    commitsOK = fopen("saida/commits-ok.csv", "r");
    reposOK = fopen("saida/repos-ok.csv", "r");
		
    reposf = fopen("saida/repos-final.csv", "w");
    commitsf = fopen("saida/commits-final.csv", "w");
    usersf = fopen("saida/users-final.csv", "w");

    BTree users = NULL;
    BTree reposC = NULL;
    BTree reposR = NULL;

    char *buffer = malloc(1000000); 

    while(fgets(buffer, 1000000, usersOK)!=NULL){
        char *dup = strdup(buffer), *backup = dup, *found;

        fprintf(usersf, "%s", buffer);

        found = strsep(&dup, ";");
        users = bt_insert(users, atoi(found));

        free(backup);
    }

    reposR = fieldToBT(reposOK, 1);

    fseek(reposOK, 0, SEEK_SET); // mete o cursor no inicio
    fseek(usersOK, 0, SEEK_SET); // mete o cursor no inicio

    while(fgets(buffer, 1000000, commitsOK)!=NULL){ // percorre o ficheiro dos commits e filtra
        char *dup = strdup(buffer), *backup=dup;
        char *found1, *found2, *found3;

        found1 = strsep(&dup, ";"); // repo_id
        int repo_id = atoi(found1);
                
        found2 = strsep(&dup, ";"); // author_id
        int id1 = atoi(found2);

        found3 = strsep(&dup, ";"); // committer_id
        int id2 = atoi(found3);

        if(id1==id2 && bTSearch(users, id1) && bTSearch(reposR, repo_id)){ //percorremos menos uma vez
            fprintf(commitsf, "%s", buffer);  
            reposC = bt_insert(reposC, repo_id);
        }
        else if (id1!=id2 && bTSearch(reposR, repo_id) && bTSearch(users, id1) && bTSearch(users, id2)){
            fprintf(commitsf, "%s", buffer);
            reposC = bt_insert(reposC, repo_id);
        }

        free(backup);
    }

    while(fgets(buffer, 1000000, reposOK) != NULL){ // percorre o repos-ok.csv e filtra
        char *dup = strdup(buffer), *backup=dup;

        char *found1, *found2;

        found1 = strsep(&dup, ";");
        found2 = strsep(&dup, ";");

        int repo_id = atoi(found1);
        int owner_id = atoi(found2);

        if (bTSearch(users, owner_id) && bTSearch(reposC, repo_id))
            fprintf(reposf, "%s", buffer);

        free(backup);
    }

    free(buffer); freeBT(users); freeBT(reposC); freeBT(reposR); // libertar os arrays ??
    fclose(usersOK); fclose(reposOK); fclose(commitsOK);
    fclose(reposf); fclose(commitsf); fclose(usersf);
}

