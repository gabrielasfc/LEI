/**
 @file menus.c
 @brief File responsible for interaction on terminal
        Reads commands, applies the relative query resolution and print outputs on terminal
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/cat_repos.h"
#include "../include/cat_users.h"
#include "../include/cat_commits.h"
#include "../include/counter_hash.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"
#include "../include/query10.h"
#include "../include/menus.h"


/**
 * @brief Prints menu with queries display
 *
*/
void display_queries_menu(){
    printf("—------------------------------------------------------------------------------\n");
    printf("|  1 | Quantidade de bots, organizações e utilizadores                        |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  2 | Número médio de colaboradores por repositório                          |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  3 | Quantidade de repositórios com bots                                    |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  4 | Média de Commits por utilizador                                        |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  5 | Top N de utilizadores mais ativos entre duas datas                     |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  6 | Top N de utilizadores com mais commits de uma determinada linguagem    |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  7 | Repositórios inativos a partir de uma determinada data                 |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  8 | Top N de linguagens mais utilizadas a partir de uma data               |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  9 | Top N de utilizadores com mais commits em repositórios de um amigo seu |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("| 10 | Top N de utilizadores por cada repositório                             |\n");
    printf("—------------------------------------------------------------------------------\n");
    printf("|  0 | Sair                                                                   |\n");
    printf("—------------------------------------------------------------------------------\n");
}


/**
 * @brief Prints sub menu
 * 
 * @param page_num Actual page number
 * @param page_lim Limit page number
 * 
 * @return 1 if pagination continues, 0 if leave
 */
int display_sub_menu(int *page_num, int page_lim){
    printf("------------------- Página %d de %d ------------------\n", *page_num, page_lim);
    printf("P      -> Próxima\n");
    printf("A      -> Anterior\n");
    printf("S <N>  -> Saltar para página\n\n");
    printf("Q      -> Sair\n");
    printf("Insira opção:\n");

    char str[20];
    fgets(str, 20, stdin); // VERIFICAR SE A STRING É VAZIA A PARTIR DO 1 CARACTER
    if (str[0] == 'P' && *page_num < page_lim) { (*page_num)++; return 1; }
    else if (str[0] == 'A' && *page_num > 1) { (*page_num)--; return 1; }
    else if (str[0] == 'S' && atoi(&str[2]) <= page_lim){
        *page_num = atoi(&str[2]);
        return 1;
    }
    else if (str[0] == 'Q') return 0;

    return 1;
}


/**
 * @brief Prints statistical queries sub menu
 * 
 * @return 0 if succeed
 */
int display_sub_menu_statistical(){
    printf("\nN      -> Avançar\n\n");
    printf("Insira opção:\n");

    char c;
    scanf(" %c", &c);
    if(c == 'N') return 0;
    return 0;
}


/**
 * @brief Ask number of users
 * 
 * @param num_users String to store the number of users
 * 
 * @return 0 if succeed
 */
int ask_num_users(char* num_users){
    printf("Insira número de utilizadores: \n");
    scanf("%49s", num_users);
    return 0;
}


/**
 * @brief Ask number of languages
 * 
 * @param num_languages String to store the number os languages
 * 
 * @return 0 if succeed
 */
int ask_num_languages(char* num_languages){
    printf("Insira número de linguagens: \n");
    scanf("%49s", num_languages);
    return 0;
}


/**
 * @brief Ask the language
 * 
 * @param language String to store the language
 * 
 * @return 0 if succeed
 */
int ask_language(char* language){
    printf("Insira linguagem: \n");
    scanf("%49s", language);
    return 0;
}


/**
 * @brief Ask the date
 * 
 * @param date String to store the date
 * 
 * @return 0 if succeed
 */
int ask_date(char* date){
    printf("Insira data (YYYY-MM-DD): \n");
    scanf("%49s", date);
    return 0;
}


/**
 * @brief Ask the initial date
 * 
 * @param date String to store the date
 * 
 * @return 0 if succeed
 */
int ask_init_date(char* date){
    printf("Insira data inicial (YYYY-MM-DD): \n");
    scanf("%49s", date);
    return 0;
}


/**
 * @brief Ask the final date
 * 
 * @param date String to store the date
 * 
 * @return 0 if succeed
 */
int ask_final_date(char* date){
    printf("Insira data final (YYYY-MM-DD): \n");
    scanf("%49s", date);
    return 0;
}


/**
 * @brief Asks for query and query input(parameters)
 *
 * @param query_info String with parameters
 * 
 * @return Query Id
 */
int ask_for_query_info(char* query_info[3]){
    int query_id, aux;
    printf("Insira opção: \n");
    scanf("%d", &query_id);
    query_info[0] = malloc(50*sizeof(char* ));
    query_info[1] = malloc(50*sizeof(char* ));
    query_info[2] = malloc(50*sizeof(char* ));

    switch(query_id){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            ask_num_users(query_info[0]);
            do{
                aux = ask_init_date(query_info[1]);
            } while (aux != 0);
            do{
                aux = ask_final_date(query_info[2]);
            } while (aux != 0);
            break;
        case 6:
            ask_num_users(query_info[0]);
            ask_language(query_info[1]);
            break;
        case 7:
            do {
                aux = ask_date(query_info[0]);
            } while (aux != 0);
            break;
        case 8:
            ask_num_languages(query_info[0]);
            do{
                aux = ask_date(query_info[1]);
            } while (aux != 0);
            break;
        case 9:
            ask_num_users(query_info[0]);
            free(query_info[1]); free(query_info[2]);
            break;
        case 10:
            ask_num_users(query_info[0]);
            free(query_info[1]); free(query_info[2]);            
            break;
        default: query_id = -1; break;
    }
    return query_id;
}


/**
 * @brief Calls the function to free according to the query id
 *
 * @param query_id Query id
 * @param list List to be freed
 */
void free_query_caller(int query_id, GList *list){
    if (query_id == 9 || query_id == 10) free_string_list(list);
    else if(query_id != 7) free_list(list);
    else free_q7_list(list);
}


/**
 * @brief Calls the query function
 * 
 * @param id Query id
 * @param query_input Query arguments
 * @param cat_users Users catalogue
 * @param cat_commits Commits catalogue
 * @param cat_repos Repository catalogue
 * 
 * @return List with query result
 */
GList* query_caller(int id, char *query_input[3], Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos){
    GList *list = NULL;
    if(id == 5){
        int N = atoi(query_input[0]);
        char *start_date = query_input[1];
        char *final_date = query_input[2];
        list = query5(N, start_date, final_date, cat_commits);
        list = list_with_n_nodes(list, N);
    }
    else if(id == 6){
        int N = atoi(query_input[0]);
        char *language = query_input[1];
        list = query6(N, language, cat_commits, cat_repos);
        list = list_with_n_nodes(list, N);
    }
    else if(id == 7){
        char *date = query_input[0];
        list = query7(date, cat_commits, cat_repos);
    }
    else if(id == 8){
        int N = atoi(query_input[0]);
        char *date = query_input[1];
        list = query8(N, date, cat_commits, cat_repos);
        list = list_with_n_nodes(list,N);
    }
    else if(id == 9){
        int N = atoi(query_input[0]);
        list = query9(N, cat_users, cat_commits, cat_repos, query_input[1]);
    }
    else if(id == 10){
        int N = atoi(query_input[0]);
        list = query10(N, cat_users, cat_commits, query_input[1]);
    }

    return list;
}


/**
 * @brief Display a certain page of a query result
 * 
 * @param q_id Query id
 * @param list List with the query result
 * @param page_num Actual page number
 * @param page_lim Limit page number
 * @param query1 Query 1 result
 * @param query2 Query 2 result
 * @param query3 Query 3 result
 * @param query4 Query 4 result
 * @param cat_users Users catalogue
 * @param cat_repos Repos catalogue
 * 
 * @return 1 if pagination continues, 0 if leave
 */
int display_page(int q_id, GList *list, int* page_num, int page_lim, void *query1, float query2, int query3, float query4, Cat_Users cat_users, Cat_Repos cat_repos){
    int ret = 0;

    if (q_id == 1){
        int* user_types = (int*)query1;
        printf("\nBot: %d\nOrganization: %d\nUser: %d\n", user_types[1], user_types[2], user_types[0]);
        ret = display_sub_menu_statistical();
    }
    else if (q_id == 2){
        printf("\nMédia de colaboradores por repositório: %.2f\n", query2);
        ret = display_sub_menu_statistical();
    }
    else if (q_id == 3){
        printf("\nNº de repositórios com bots: %d\n", query3);
        ret = display_sub_menu_statistical();
    }
    else if (q_id == 4){
        printf("\nMédia de commits por utilizador: %.2f\n", query4);
        ret = display_sub_menu_statistical();
    }
    else if(q_id == 5){
        display_page_q5(list, cat_users, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    else if(q_id == 6){
        display_page_q6(list, cat_users, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    else if(q_id == 7){
        display_page_q7(list, cat_repos, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    else if(q_id == 8){
        display_page_q8(list, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    else if(q_id == 9){
        display_page_query_9(list, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    else if(q_id==10){
        display_page_query_10(list, *page_num);
        ret = display_sub_menu(page_num, page_lim);
    }
    system("clear");

    return ret;
}
