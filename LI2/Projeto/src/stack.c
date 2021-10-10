/**
 @file  stack.c
 @brief Ficheiro com funções relativas à implementação da Stack
 */

#include "stack.h"

/**
 * \brief   Inicializa-se a Stack com tamanho 0.
 * @returns Stack
 */
struct Stack *criar_stack() {
    struct Stack *s;
    s = (struct Stack *) malloc(0 * sizeof(struct StackElem)); //alocar mem
    s->size = 0;
    return s;
}

/**
 * \brief   Função que inicializa as variáveis com o seu valor por omissão.
 * @param s Stack
 */
void criar_variaveis(struct Stack *s){
    s->vars = (struct StackElem *) malloc(26 * sizeof(struct StackElem)); //alocar mem do array com as vars
    s->vars[0].valor.l = 10; s->vars[0].type = Long;
    s->vars[1].valor.l = 11; s->vars[1].type = Long;
    s->vars[2].valor.l = 12; s->vars[2].type = Long;
    s->vars[3].valor.l = 13; s->vars[3].type = Long;
    s->vars[4].valor.l = 14; s->vars[4].type = Long;
    s->vars[5].valor.l = 15; s->vars[5].type = Long;
    s->vars[6].valor.l = 0; s->vars[6].type = Long;
    s->vars[7].valor.l = 0; s->vars[7].type = Long;
    s->vars[8].valor.l = 0; s->vars[8].type = Long;
    s->vars[9].valor.l = 0; s->vars[9].type = Long;
    s->vars[10].valor.l = 0; s->vars[10].type = Long;
    s->vars[11].valor.l = 0; s->vars[11].type = Long;
    s->vars[12].valor.l = 0; s->vars[12].type = Long;
    s->vars[13].valor.c = '\n'; s->vars[13].type = Char;
    s->vars[14].valor.l = 0; s->vars[14].type = Long;
    s->vars[15].valor.l = 0; s->vars[15].type = Long;
    s->vars[16].valor.l = 0; s->vars[16].type = Long;
    s->vars[17].valor.l = 0; s->vars[17].type = Long;
    s->vars[18].valor.c = ' ' ; s->vars[18].type = Char;
    s->vars[19].valor.l = 0; s->vars[19].type = Long;
    s->vars[20].valor.l = 0; s->vars[20].type = Long;
    s->vars[21].valor.l = 0; s->vars[21].type = Long;
    s->vars[22].valor.l = 0; s->vars[22].type = Long;
    s->vars[23].valor.l = 0; s->vars[23].type = Long;
    s->vars[24].valor.l = 1; s->vars[24].type = Long;
    s->vars[25].valor.l = 2; s->vars[25].type = Long;
}

/**
 * \brief   Função que insere um elemento no topo da Stack.
 * @param s Stack
 * @param t Tipo do elemento que vamos inserir
 */
void push(struct Stack *s, elemtype t, ...) {
    int newsize = s->size + 1;
    s->p = realloc(s->p, newsize * sizeof(struct StackElem)); //alocar + mem
    va_list x;
    va_start(x, t);
    s->p[s->size].type = t;
    switch (t) {
        case Long:
            s->p[s->size].valor.l = va_arg(x,long); break;
        case Double:
            s->p[s->size].valor.d = va_arg(x,double); break;
        case String:
            s->p[s->size].valor.str = va_arg(x,char*); break;
        case Char:
            s->p[s->size].valor.c = (char) va_arg(x,int); break;
        case Array:
            s->p[s->size].valor.arr = va_arg(x,struct Stack*); break;
        default: break;
    }
    s->size++;
    va_end(x);
}

/**
 * \brief   Função auxiliar com o mesmo efeito da push, mas com o tipo do elemento variável.
 * @param s Stack
 * @param x Tipo do elemento
 * @param y Data do elemento
 */
void pushaux(struct Stack *s, elemtype x, elemdata y) {
    switch (x) {
        case (Long) :
            push(s, Long, y.l); break;
        case (Double) :
            push(s, Double, y.d); break;
        case (String) :
            push(s, String, y.str); break;
        case (Char) :
            push(s, Char, y.c); break;
        case (Array) : 
            push (s, Array, y.arr); break;
        default : break;
    }
}

/**
 * \brief   Função que retira o elemento do topo da Stack.
 * @param s Stack
 * @returns Elemento retirado
 */
elemdata pop(struct Stack *s) {
    assert(s->p != 0); //verificar se a stack não é vazia
    elemdata top = s->p[s->size - 1].valor; //elemento que vamos remover
    int newsize = s->size - 1;
    s->p = realloc(s->p, newsize * sizeof(struct StackElem)); //alocar -mem
    s->size--;
    return top;
}

/**
 * \brief   Função que remove o elemento da Stack do fundo.
 * @param s Stack
 * @returns Elemento retirado
 */
elemdata pop_bottom (struct Stack *s){
    elemdata v =(s->p[0].valor);
    s->p++;
    s->size--;
    return v;
}

/**
 * \brief   Função que devolve o tipo do elemento do topo da Stack.
 * @param s Stack
 * @returns Tipo do elemento do topo
 */
elemtype peek(struct Stack *s) {
    return s->p[s->size - 1].type;
}

/**
 * \brief   Função que devolve o tipo do elemento de indice n da Stack,
 *          onde o índice 0 corresponde ao elemento do topo da Stack.
 * @param s Stack
 * @param n Índice do elemento
 * @returns Tipo do elemento de indice n 
 */
elemtype peekind(struct Stack *s, int n) {
    return s->p[s->size - n - 1].type;
}

/**
 * \brief   Função que devolve o tipo do elemento de indice n da Stack,
 *          onde o índice 0 corresponde ao elemento do fundo da Stack.
 * @param s Stack
 * @param i Índice
 * @returns Tipo do elemento de índice n
 */
elemtype peekind2(struct Stack *s, int n){
    return (s->p[n].type);
}

/**
 * \brief Função que imprime a Stack.
 * @param s Stack
 */
void print_stack(struct Stack *s) {
    for (int i = 0; i < s->size; i++)
        switch (s->p[i].type) {
            case Long:
                printf("%ld", s->p[i].valor.l); break;
            case Double:
                printf("%g", s->p[i].valor.d); break;
            case String:
                printf("%s", s->p[i].valor.str); break;
            case Char:
                printf("%c", s->p[i].valor.c); break;
            case Array:
                print_stack(s->p[i].valor.arr); break;
            default: break;
        }
}
