/**
 @file  stack.h
 @brief Ficheiro com funções relativas à implementação da Stack
 */

#ifndef LIPROJETO_STACK_H
#define LIPROJETO_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

/*!
 * \brief Define os vários tipos que um elemento da Stack pode assumir.
 */
typedef enum {
    Long, ///< O elemento é um long
    Double, ///< O elemento é um double
    String, ///< O elemento é uma string
    Char, ///< O elemento é um char
    Array, ///< O elemento é um array
} elemtype;

/*!
 * \brief Define qual o datatype do elemento e guarda a variável com o valor no respetivo membro da union.
 */
typedef union {
    long l; ///< A memória da union será ocupada por um long.
    double d; ///< A memória da union será ocupada por um double.
    char *str; ///< A memória da union será ocupada por uma string.
    char c; ///< A memória da union será ocupada por um char.
    struct Stack *arr; ///< A memória da union será ocupada por um array.
} elemdata;

/**
 * \brief Estrutura que devolve o tipo de um dado elemento e o seu valor.
 */
struct StackElem {
    elemtype type; ///< Tipo do elemento
    elemdata valor; ///< Valor do elemento
};

/**
 * \brief Tipo de dados da Stack, com o seu tamanho, elementos e variáveis.
 */
struct Stack{
    int size; ///< Tamanho da Stack.
    struct StackElem *p; ///< Array com os elementos da Stack.
    struct StackElem *vars; ///< Array com as variáveis.
};

/**
 * \brief   Inicializa-se a Stack com tamanho 0.
 * @returns Stack
 */
struct Stack *criar_stack();

/**
 * \brief   Função que inicializa as variáveis com o seu valor por omissão.
 * @param s Stack
 */
void criar_variaveis(struct Stack *s);

/**
 * \brief   Função que insere um elemento no topo da Stack.
 * @param s Stack
 * @param t Tipo do elemento que vamos inserir
 */
void push(struct Stack *s, elemtype t, ...);

/**
 * \brief   Função auxiliar com o mesmo efeito da push, mas com o tipo do elemento variável.
 * @param s Stack
 * @param x Tipo do elemento
 * @param y Data do elemento
 */
void pushaux(struct Stack *s, elemtype x, elemdata y);

/**
 * \brief   Função que retira o elemento do topo da Stack.
 * @param s Stack
 * @returns Elemento retirado
 */
elemdata pop(struct Stack *s);

/**
 * \brief   Função que devolve o tipo do elemento do topo da Stack.
 * @param s Stack
 * @returns Tipo do elemento do topo
 */
elemtype peek(struct Stack *s);

/**
 * \brief   Função que devolve o tipo do elemento de indice n da Stack,
 *          onde o índice 0 corresponde ao elemento do topo da Stack.
 * @param s Stack
 * @param n Índice do elemento
 * @returns Tipo do elemento de indice n 
 */
elemtype peekind(struct Stack *s, int n);

/**
 * \brief   Função que devolve o tipo do elemento de indice n da Stack,
 *          onde o índice 0 corresponde ao elemento do fundo da Stack.
 * @param s Stack
 * @param i Índice
 * @returns Tipo do elemento de índice n
 */
elemtype peekind2(struct Stack *s, int n);

/**
 * \brief   Função que remove o elemento da Stack do fundo.
 * @param s Stack
 * @returns Elemento retirado
 */
elemdata pop_bottom (struct Stack *s);

/**
 * \brief Função que imprime a Stack.
 * @param s Stack
 */
void print_stack(struct Stack *s);

#endif //LIPROJETO_STACK_H
