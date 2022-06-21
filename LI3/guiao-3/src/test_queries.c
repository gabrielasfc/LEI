/**
 @file test_queries.c
 @brief Module responsible for testing queries (compare outputs and run time)
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/command_interpreter.h"
#include "../include/cat_repos.h"
#include "../include/cat_users.h"
#include "../include/cat_commits.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"
#include "../include/query10.h"
#include "../include/parser.h"


/**
 * @brief Calls query print function by given id
 * 
 * @param query_id Query id
 * @param query_args Array with query arguments
 * @param output Output file to write
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 */
void call_query(int query_id, char* query_args[], FILE* output, Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    char* x;
    int num;
    printf("Query... %d\n", query_id);
    switch(query_id){
        case 5: print_q5(query5(atoi(query_args[0]), query_args[1], query_args[2], cat_commits), cat_users, output, atoi(query_args[0])); break;
        case 6: print_q6(query6(atoi(query_args[0]), query_args[1], cat_commits, cat_repos), cat_users, output, atoi(query_args[0])); break;
        case 7: print_q7(query7(query_args[0], cat_commits, cat_repos), cat_repos, output); break;
        case 8: print_q8(query8(atoi(query_args[0]), query_args[1], cat_commits, cat_repos), output, atoi(query_args[0])); break;
        case 9: x = query_args[0]; num = atoi(x);
                print_q9(query9(num, cat_users, cat_commits, cat_repos, query_args[1]), output); break;
        case 10: x = query_args[0]; num = atoi(x);
                print_q10(query10(num, cat_users, cat_commits, query_args[1]), output); break;
    }
}


/**
 * @brief Compares expected output with obtained query result
 * 
 * @param expected File with expected output
 * @param query_result File with obtained output executing the query
 * 
 * @return 0 if files are different, 1 otherwise
 */
int compare_files(FILE* expected, FILE* query_result){
    int r=1;
    char buffer1[100], buffer2[100];
    char* test1 = NULL, *test2 = NULL;
    int i=0;

    while (((test1 = fgets(buffer1, 100, expected)) && (test2 = fgets(buffer2, 100, query_result))) && r){
        r = strcmp(buffer1, buffer2) == 0;
        i++;
    }
    if (((!test1 && test2) || (test1 && !test2)) && r == 1){
        if (i == 0) r = 0; // An empty file and a non empty file
        if (test2) test2 = fgets(buffer2, 100, query_result);
        if (test2) { 
            printf("Resultados parcialmente corretos. Um ficheiro tem mais linhas que outro!\n");
            r = 0;
        }
    }
    return r;
}


/**
 * @brief Gets the run time from the query and compares expected and obtained outputs
 * 
 * @param query_id Query id
 * @param query_args Array with query arguments
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repos catalogue
 * @param test_num Number of tests done before
 */
void test_query(char* query_id, char* query_args[], Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos, int test_num){
    FILE* output = fopen("testing/query_output.txt", "w");
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int query_id_int = atoi(query_id);
    call_query(query_id_int, query_args, output, cat_users, cat_commits, cat_repos);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f\n", cpu_time_used );
    fclose(output);

    // Compare results
    char path_to_expected[100] = "testing/expected_results/query_";
    strcat(path_to_expected, query_id);
    char test_num_str[2]; sprintf(test_num_str, "%d", test_num);
    strcat(path_to_expected, "_");
    strcat(path_to_expected, test_num_str);
    strcat(path_to_expected, ".txt");
    FILE* expected = fopen(path_to_expected, "r");
    output = fopen("testing/query_output.txt", "r");
    fseek(output, 0, SEEK_SET);
    int r = compare_files(expected, output);
    if (r == 1) printf("Resultados da query %s válidos!\n", query_id);
    else printf("Resultados da query %s inválidos!\n", query_id);
    
}


/**
 * @brief Main function responsible for testing queries
 * 
 * @param argc Arguments count
 * @param argv Arguments values
 * 
 * @return 0 (no errors)
 */
int main(int argc, const char** argv){
    Cat_Users cat_users = create_users_cat();
    Cat_Commits cat_commits = create_commits_cat();
    Cat_Repos cat_repos = create_repos_cat();

    char is_query_10_first_time = 1;
    char is_query_9_first_time = 1;

    void** queries_data = data_to_catalogues_with_parsing(cat_users, cat_commits, cat_repos);

    char* query5_args1[3] = {"100", "2014-12-25", "2015-01-01"};
    char* query6_args1[2] = {"100", "haskell"};
    char* query7_args1[1] = {"2014-04-25"};
    char* query7_args2[1] = {"2000-02-05"};
    char* query8_args1[2] = {"3", "2000-10-05"};
    char* query8_args2[2] = {"200", "2016-10-05"};
    char* query9_args1[2] = {"2000", &is_query_9_first_time};
    char* query9_args2[2] = {"100", &is_query_9_first_time};
    char* query10_args1[2] = {"1", &is_query_10_first_time};
    char* query10_args2[2] = {"50", &is_query_10_first_time};

    test_query("5", query5_args1,cat_users, cat_commits, cat_repos, 1);
    test_query("6", query6_args1,cat_users, cat_commits, cat_repos, 1);
    test_query("7", query7_args1, cat_users, cat_commits, cat_repos, 1);
    test_query("7", query7_args2, cat_users, cat_commits, cat_repos, 2);
    test_query("8", query8_args1, cat_users, cat_commits, cat_repos, 1);
    test_query("8", query8_args2, cat_users, cat_commits, cat_repos, 2);
    test_query("9", query9_args1, cat_users, cat_commits, cat_repos, 1);
    test_query("9", query9_args2, cat_users, cat_commits, cat_repos, 2);
    test_query("10", query10_args1, cat_users, cat_commits, cat_repos, 1);
    test_query("10", query10_args2, cat_users, cat_commits, cat_repos, 2);
}