/**
 @file  operadores.h
 @brief Ficheiro com as funções relativas aos operadores
 */

#ifndef LIPROJETO_OPERADORES_H
#define LIPROJETO_OPERADORES_H

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"


/**
 * \brief   Função auxiliar que verifica se os 2 elementos são do tipo Long.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os 2 elementos forem do tipo Long, 0 caso contrário.
 */
int isBothLong(elemtype x, elemtype y);

/**
 * \brief   Função auxiliar que verifica se os 2 elementos são do tipo Double.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os 2 elementos forem do tipo Double, 0 caso contrário.
 */
int isBothDouble(elemtype x, elemtype y);

/**
 * \brief   Função auxiliar que verifica se os dois elementos são do tipo String.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os dois elementos forem do tipo String, 0 caso contrário.
 */
int isBothString(elemtype x, elemtype y);

/**
 * \brief   Função auxiliar que verifica se os dois elementos são do tipo Array.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os dois elementos forem do tipo Array, 0 caso contrário.
 */
int isBothArray(elemtype x, elemtype y);

/**
 * \brief   Função auxiliar que verifica se um elemento é do tipo Long.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Long, 0 caso contrário.
 */
int isLong(elemtype x);

/**
 * \brief   Função auxiliar que verifica se um elemento é do tipo Double.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Double, 0 caso contrário.
 */
int isDouble(elemtype x);

/**
 * \brief   Função auxiliar que verifica um elemento é do tipo String.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo String, 0 caso contrário.
 */
int isString(elemtype x);

/**
 * \brief   Função auxiliar que verifica um elemento é do tipo Array.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Array, 0 caso contrário.
 */
int isArray(elemtype x);

/**
 * \brief   Função auxiliar que verifica se algum dos elementos é do tipo String.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se algum dos elementos for do tipo String, 0 caso contrário.
 */
int isAnyString(elemtype x, elemtype y);

/**
 * \brief   Função auxiliar que verifica se algum dos elementos é do tipo Array.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se algum dos elementos for do tipo Array, 0 caso contrário.
 */
int isAnyArray(elemtype x, elemtype y);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da soma dos 2 elementos.
 * @param s Stack
 */
void soma(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o que se obtém ao subtrair o elemento do topo ao elemento a seguir.
 * @param s Stack
 */
void subtracao(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da multiplicação dos 2 primeiros elementos do topo da Stack.
 * @param s Stack
 */
void mult(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da divisão do 2º elemento do topo pelo elemento do topo.
 * @param s Stack
 */
void divisao(struct Stack *s);

/**
 * \brief   Função que decrementa 1 valor ao elemento do topo da Stack.
 * @param s Stack
 */
void parentesesAberto(struct Stack *s);

/**
 * \brief   Função que incrementa 1 valor ao elemento do topo da Stack.
 * @param s Stack
 */
void parentesesFechado(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          a potência que tem como base o topo da Stack e como expoente o elemento a seguir.
 * @param s Stack
 */
void exponenciacao(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca
 *          o resto da divisão inteira do 2º elemento pelo 1º elemento do topo.
 * @param s Stack
 */
void modulo(struct Stack *s);

/**
 * \brief   Operador bitwise que retira o topo da Stack e coloca na Stack
 *          o valor 1 quando ambos os bits forem 1 e 0 caso contrário.
 *
 *       Exemplo: 2 3 &
 *
 *                2 -> 10
 *
 *                3 -> 11
 *
 *                Output -> 10
 * @param s Stack
 */
void conjuncao(struct Stack *s);

/**
 * \brief   Operador bitwise que retira o topo da Stack e coloca na Stack 
 *          o valor 1 quando um dos bits for 1 e 0 caso contrário.
 *
 *       Exemplo: 2 4 |
 *
 *                2 -> 010
 *
 *                4 -> 100
 *
 *                Output -> 110
 * @param s Stack
 */
void disjuncao(struct Stack *s);

/**
 * \brief   Operador bitwise que retira o topo da Stack e coloca na Stack
 *          o valor 1 quando os bits comparados forem diferentes e 0 caso contrário.
 * @param s Stack
 */
void xor(struct Stack *s);

/**
 * \brief   Operador bitwise que retira o topo da Stack e colocar na Stack o seu valor representado em Complemento2.
 * @param s Stack
 */
void not(struct Stack *s);

/**
 * \brief   Função que troca os três elementos do topo da stack entre si.
 *
 *       Exemplos: Input  -> 123
 *
 *                 Output -> 231
 *
 *                 Input  -> 465
 *
 *                 Output -> 654
 * @param s Stack
 */
void arroba(struct Stack *s);

/**
 * \brief   Função que troca os dois elementos do topo da stack.
 * @param s Stack
 */
void switchtop(struct Stack *s);

/**
 * \brief   O objetivo desta função é duplicar o topo da stack.
 * @param s Stack
 */
void underscore(struct Stack *s);

/**
 * \brief   Função que tem como objetivo procurar ao longo da stack o número de índice 'n'
 *          e repeti-lo no fim da stack.
 * @param s Stack
 */
void tpindex(struct Stack *s);

/**
 * \brief   Função que lê uma linha e a coloca no topo da Stack.
 * @param s Stack
 */
void leitura(struct Stack *s);

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo long.
 * @param s Stack
 */
void trsint(struct Stack *s);

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo double.
 * @param s Stack
 */
void trsdouble(struct Stack *s);

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo char.
 * @param s Stack
 */
void trschar(struct Stack *s);


/**
 * \brief   Função que retira os 2 elementos do topo da Stack e 
 *          se forem iguais coloca 1 na stack ou 0 caso contrário.
 * @param s Stack
 */
void igual(struct Stack *s);

/**
 * \brief   Função que devolve 1 se o 2º elemento for maior que o do topo da Stack ou 0, caso contrário.
 * @param s Stack
 */
void maior(struct Stack *s);

/**
 * \brief   Função que devolve 1 se o 2º elemento for menor que o do topo da Stack ou 0, caso contrário.
 * @param s Stack
 */
void menor(struct Stack *s);

/**
 * \brief   Função que retira o elemento do topo da Stack e
 *          coloca na Stack o resultado do seu valor lógico invertido.
 */
void invertevl(struct Stack *s);

/**
 * \brief   Função auxiliar que recebe o tipo e o data de um elemento e devolve o data em Double.
 * @param t Tipo do elemento
 * @param v Data do elemento
 * @returns Valor do elemento no tipo Double.
 */
double elemDouble(elemtype t, elemdata v);

/**
 * \brief   Retira os 2 elementos do topo da Stack e
 *          coloca o valor do 1º elemento caso ambos sejam verdadeiros
 *          ou 0, caso contrário.
 * @param s Stack
 */
void econjuncao(struct Stack *s);

/** 
 * \brief   Retira os 2 elementos do topo da Stack e:
 *          Coloca 0 na Stack se os 2 elementos forem falsos,
 *          o 2º elemento caso sejam ambos verdadeiros 
 *          ou o elemento de valor lógico 1 caso algum deles seja falso.
 * @param s Stack
 */
void edisjuncao(struct Stack *s);

/** 
 * \brief   Retira os 2 elementos do topo da Stack e coloca o elemento maior na Stack.
 * @param s Stack
 */
void emaior(struct Stack *s);

/**
 * \brief   Retira os 2 elementos do topo da Stack e coloca o elemento menor na Stack.
 * @param s Stack
 */
void emenor(struct Stack *s);

/**
 * \brief   Função que retira os 3 elementos do topo da Stack e:
 *          Se o 3º elemento do topo for verdadeiro, volta a colocar o 2º elemento na Stack.
 *          Caso contrário, volta a colocar o elemento do topo na Stack.
 * @param s Stack
 */
void ifthenelse(struct Stack *s);

/**
 * \brief     Função que coloca a variável na Stack.
 * @param s   Stack
 * @param var Variável
 */
void pushvar(struct Stack *s,char var);

/**
 * \brief     Função que altera o valor e o tipo da variável para os do topo da Stack.
 * @param s   Stack
 * @param var Variável
 */
void copiatopo(struct Stack *s,char var);

/**
 * \brief     Função que altera o valor e o tipo da variável para os do topo da Stack.
 * @param s   Stack
 * @param var Variável
 */
void copy(struct Stack *s, char var);

/**
 * \brief   Função que retira o elemento do topo da Stack e:
 *          Caso seja uma string ou um array, coloca o seu comprimento na Stack;
 *          Caso seja um número, coloca na Stack um array inicializado a 0 com todos os inteiros até n,
 *          sendo n o elemento do topo da Stack.
 * @param s Stack
 */
void virgula(struct Stack *s);

/**
 * \brief   Função auxiliar que transforma um char numa String apenas com esse char.
 * @param x Char
 * @param s String
 */
void trsstring(char x, char *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e:
 *          Caso sejam os 2 arrays, concatena os arrays;
 *          Caso o elemento do topo seja um array, adiciona o 2º elemento da Stack ao início do array e coloca o array resultante na Stack;
 *          Caso o 2º elemento do topo seja um array, adiciona o elemento do topo ao fim do array e coloca o array resultante na Stack;
 * @param s Stack
 */
void concat_arrays(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e:
 *          Caso sejam os 2 strings, concatena as strings;
 *          Caso o elemento do topo seja uma string, adiciona o 2º elemento da Stack ao início da string e coloca a string resultante na Stack;
 *          Caso o 2º elemento do topo seja uma string, adiciona o elemento do topo ao fim da string e coloca a string resultante na Stack.
 * @param s Stack
 */
void concat_strings(struct Stack *s);

/**
 * \brief   Função que invoca o respetivo concat de strings ou arrays.
 * @param s Stack
 */
void concat(struct Stack *s);

/**
 * \brief   Função geral do operador '+' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_mais(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack o array/string resultante da concatenação.
 * @param s Stack
 */
void operador_mais(struct Stack *s);

/**
 * \brief   Função que retira da Stack o elemento do topo da Stack(Array) e coloca na Stack todos os seus elementos.
 * @param s Stack
 */
void til(struct Stack *s);

/**
 * \brief   Função geral do operador '~' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_til(struct Stack *s);

/**
 * \brief   Função que retira o elemento do topo da Stack (array/string) e
 *          retira-lhe o último elemento (se for array, o do topo) e coloca-o na Stack.
 * @param s Stack
 */
void take_last(struct Stack *s);

/**
 * \brief   Função geral do operador ')' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_pFechado(struct Stack *s);

/**
 * \brief   Função que retira o elemento do topo da Stack (array/string) e
 *          retira-lhe o 1º elemento (se for array, o do fundo) o e coloca-o na Stack.
 * @param s Stack
 */
void take_fst(struct Stack *s);

/**
 * \brief   Função geral do operador '(' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_pAberto(struct Stack *s);

/**
 * \brief   Função que retira os 2 primeiros elementos da Stack (Strings) e coloca na Stack
 *          o índice na String (2º elemento do topo) onde se inicia a Substring (elemento do topo)
 *          ou -1 caso não exista Substring.
 * @param s Stack
 */
void procura_substr(struct Stack *s);

/**
 * \brief   Função geral do operador '#' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_cardinal(struct Stack *s);

/**
 * \brief   Função que lê todo o input de uma string.
 * @param s Stack
 */
void lermtlinhas(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde o do topo é o índice
 *          e o 2º um array/string. Procura o elemento do índice dado na string/array e coloca-o na Stack.
 * @param s Stack
 */
void procura_por_indice(struct Stack *s);

/**
 * \brief   Função geral do operador '=' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_igual(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e concatena recursivamente o
 *          array/string do 2º elemento do topo da Stack n vezes, onde n é o elemento do topo da Stack.
 * @param s Stack
 */
void concat_xvezes(struct Stack *s);

/**
 * \brief   Função geral do operador '*' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_asterisco(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack (strings) e, sendo o elemento do topo a substring, separa 
 *          o 2º elemento do topo (string) por essa substring-
 * @param s Stack
 */
void sepstr_substr(struct Stack *s);

/**
 * \brief   Função geral do operador '/' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_barra(struct Stack *s);

/**
 * \brief   Função que retira o elemento do topo da Stack (string) e separa essa string pela ocorrência de whitespaces.
 * @param s Stack
 */
void sepstr_whitespc(struct Stack *s);

/**
 * \brief   Função que retira o elemento do topo da Stack (string) e separa essa string pela ocorrência de newlines.
 * @param s Stack
 */
void sepstr_newlns(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde n é o elemento do topo
 *          e o 2º elemento do topo o array/string, e coloca na Stack os n elementos do início do array/string.
 * @param s Stack
 */
void buscaInicio(struct Stack *s);

/**
 * \brief   Função geral do operador '<' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_menor(struct Stack *s);

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde n é o elemento do topo
 *          e o 2º elemento do topo o array/string, e coloca na Stack os n elementos do fim do array/string.
 * @param s Stack
 */
void buscaFim(struct Stack *s);

/**
 * \brief   Função geral do operador '>' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_maior(struct Stack *s);

#endif //LIPROJETO_OPERADORES_H
