/**
 @file  parser.h
 @brief Ficheiro com as funções relativas ao parse
 */

#ifndef LIPROJETO_PARSER_H
#define LIPROJETO_PARSER_H

#include "operadores.h"


/**
 * \brief       Função que invoca, consoante o token, as operações matemáticas simples ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token Operador
 */
void operadores_mat(struct Stack *s, char token);

/**
 * \brief       Função que invoca, consoante o token, as operações bitwise ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token Operador
 */
void operadores_bitwise(struct Stack *s, char token);

/**
 * \brief       Função que invoca, consoante o token, as operações de conversão.
 * @param s     Stack
 * @param token Operador
 */
void operadores_conversoes(struct Stack *s, char token);

/**
 * \brief       Função que invoca, consoante o token, as operações relativas à manipulação da Stack.
 * @param s     Stack
 * @param token Operador
 */
void operadores_stack(struct Stack *s, char token);

/**
 * \brief       Função que invoca, consoante o char a seguir ao "e", as operações lógicas.
 * @param s     Stack
 * @param token Operador
 */
void operadores_e(struct Stack *s, char token);

/**
 * \brief       Função que invoca, consoante o token, as operações lógicas ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_logica(struct Stack *s, char *token);

/**
 * \brief       Função que invoca, consoante o token, as respetivas operações das variáveis.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_variaveis(struct Stack *s, char *token);

/**
 * \brief       Função que invoca, consoante o token, as novas operações relativas a arrays/strings do guião 4.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_arrstr(struct Stack *s, char *token);

/**
 * \brief       Função que invoca, consoante o token, a função geral do respetivo tipo de operação.
 * @param s     Stack
 * @param token String com o operador
 */
void operacoes(struct Stack *s, char *token);

/**
 * \brief       Função auxiliar que devolve o token até ao delimitador dado.
 * @param line  Linha
 * @param delim Delimitador
 * @returns     Token
 */
char *get_token(char **line, char *delim);

/**
 * \brief      Função auxiliar que tem o mesmo efeito que a get_token, mas dedicada a arrays,
 *             analisando quantos arrays podem existir dentro desse array.
 * @param line Linha
 * returns     Token
 */
char *get_token_arr(char **line);

/**
 * \brief       Função que coloca na Stack os números recebidos no token ou 
 *              invoca as operações, recorrendo à função auxiliar "operacoes".
 * @param s     Stack
 * @param Token Token
 */
void numberoroperation(struct Stack *s, char *token);

/**
 * \brief   Função que copia as variéveis da Stack para o Array.
 * @param s Stack
 * @returns Devolve o Array com as variáveis já introduzidas.
 */
struct Stack *copiavars(struct Stack *s);

/**
 * \brief     Função que copia as variéveis do Array para a Stack.
 * @param s   Stack
 * @param arr Array 
 */
void copiavars2(struct Stack *s, struct Stack *arr);

/**
 * \brief      Função principal que analisa a linha recebida no input e faz o seu parse.
 * @param s    Stack
 * @param line Linha
 */
void parse(struct Stack *s, char *line);

#endif //LIPROJETO_PARSER_H