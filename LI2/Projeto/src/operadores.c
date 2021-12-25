/**
 @file  operadores.c
 @brief Ficheiro com as funções relativas aos operadores
 */

#include "../include/operadores.h"
#include "../include/parser.h"

/**
 * \brief   Função auxiliar que verifica se os 2 elementos são do tipo Long.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os 2 elementos forem do tipo Long, 0 caso contrário.
 */
int isBothLong(elemtype x, elemtype y) {
    return (x == Long && y==Long);
}

/**
 * \brief   Função auxiliar que verifica se os 2 elementos são do tipo Double.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os 2 elementos forem do tipo Double, 0 caso contrário.
 */
int isBothDouble(elemtype x, elemtype y) {
    return (x == Double && y==Double);
}

/**
 * \brief   Função auxiliar que verifica se os dois elementos são do tipo String.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os dois elementos forem do tipo String, 0 caso contrário.
 */
int isBothString(elemtype x, elemtype y){
    return (x==String && y ==String);
}

/**
 * \brief   Função auxiliar que verifica se os dois elementos são do tipo Array.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se os dois elementos forem do tipo Array, 0 caso contrário.
 */
int isBothArray(elemtype x, elemtype y){
    return (x==Array && y ==Array);
}

/**
 * \brief   Função auxiliar que verifica se um elemento é do tipo Long.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Long, 0 caso contrário.
 */
int isLong(elemtype x) {
    return (x == Long);
}

/**
 * \brief   Função auxiliar que verifica se um elemento é do tipo Double.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Double, 0 caso contrário.
 */
int isDouble(elemtype x) {
    return (x == Double);
}

/**
 * \brief   Função auxiliar que verifica um elemento é do tipo String.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo String, 0 caso contrário.
 */
int isString(elemtype x){
    return (x==String);
}

/**
 * \brief   Função auxiliar que verifica um elemento é do tipo Array.
 * @param x Tipo do elemento
 * @returns 1 se o elemento for do tipo Array, 0 caso contrário.
 */
int isArray(elemtype x){
    return (x==Array);
}

/**
 * \brief   Função auxiliar que verifica se algum dos elementos é do tipo String.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se algum dos elementos for do tipo String, 0 caso contrário.
 */
int isAnyString(elemtype x, elemtype y){
    return (x==String || y==String);
}

/**
 * \brief   Função auxiliar que verifica se algum dos elementos é do tipo Array.
 * @param x Tipo do elemento
 * @param y Tipo do elemento
 * @returns 1 se algum dos elementos for do tipo Array, 0 caso contrário.
 */
int isAnyArray(elemtype x, elemtype y){
    return (x==Array || y==Array);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da soma dos 2 elementos.
 * @param s Stack
 */
void soma(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothLong(t_top, t_snd)) push(s, Long, v_top.l + v_snd.l);
    else if (isBothDouble(t_top, t_snd)) push(s, Double, v_top.d + v_snd.d);
    else if (isDouble(t_top) && isLong(t_snd)) push(s, Double, v_top.d + v_snd.l);
    else push(s, Double, v_top.l + v_snd.d); 
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o que se obtém ao subtrair o elemento do topo ao elemento a seguir.
 * @param s Stack
 */
void subtracao(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothLong(t_top, t_snd)) push(s, Long, v_snd.l - v_top.l);
    else if (isBothDouble(t_top, t_snd)) push(s, Double, v_snd.d - v_top.d);
    else if (isDouble(t_top) && isLong(t_snd)) push(s, Double, v_snd.l - v_top.d);
    else push(s, Double, v_snd.d - v_top.l);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da multiplicação dos 2 primeiros elementos do topo da Stack.
 * @param s Stack
 */
void mult(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothLong(t_top, t_snd)) push(s, Long, v_top.l * v_snd.l);
    else if (isBothDouble(t_top, t_snd)) push(s, Double, v_top.d * v_snd.d);
    else if (isDouble(t_top) && isLong(t_snd)) push(s, Double, v_top.d * v_snd.l);
    else push(s, Double, v_top.l * v_snd.d); 
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          o resultado da divisão do 2º elemento do topo pelo elemento do topo.
 * @param s Stack
 */
void divisao(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothLong(t_top, t_snd)) push(s, Long, v_snd.l / v_top.l);
    else if (isBothDouble(t_top, t_snd)) push(s, Double, v_snd.d / v_top.d);
    else if (isDouble(t_top) && isLong(t_snd)) push(s, Double, v_snd.l / v_top.d);
    else push(s, Double, v_snd.d / v_top.l);
}

/**
 * \brief   Função que decrementa 1 valor ao elemento do topo da Stack.
 * @param s Stack
 */
void parentesesAberto(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    switch (t_top) {
        case Long:
            push(s, Long, v_top.l - 1); break;
        case Double:
            push(s, Double, v_top.d - 1); break;
        case Char:
            push(s, Char, v_top.c - 1); break;
        default: break;
    }
}

/**
 * \brief   Função que incrementa 1 valor ao elemento do topo da Stack.
 * @param s Stack
 */
void parentesesFechado(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    switch (t_top) {
        case Long:
            push(s, Long, v_top.l + 1); break;
        case Double:
            push(s, Double, v_top.d + 1); break;
        case Char:
            push(s, Char, v_top.c + 1); break;
        default: break;
    }
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca na Stack
 *          a potência que tem como base o topo da Stack e como expoente o elemento a seguir.
 * @param s Stack
 */
void exponenciacao(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothLong(t_top, t_snd)) push(s, Long, (long) pow((double) v_snd.l, (double) v_top.l));
    else if (isBothDouble(t_top, t_snd)) push(s, Double, pow(v_snd.d, v_top.d));
    else if (isDouble(t_top) && isLong(t_snd)) push(s, Double, pow((double) v_snd.l, v_top.d));
    else push(s, Double, pow(v_snd.d, (double) v_top.l));
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e coloca
 *          o resto da divisão inteira do 2º elemento pelo 1º elemento do topo.
 * @param s Stack
 */
void modulo(struct Stack *s) {
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    push(s, Long, v_snd.l % v_top.l);
}

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
void conjuncao(struct Stack *s) {
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    push(s, Long, v_top.l & v_snd.l);
}

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
void disjuncao(struct Stack *s) {
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    push(s, Long, v_top.l || v_snd.l);
}

/**
 * \brief   Operador bitwise que retira o topo da Stack e coloca na Stack
 *          o valor 1 quando os bits comparados forem diferentes e 0 caso contrário.
 * @param s Stack
 */
void xor(struct Stack *s) {
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    push(s, Long, v_top.l ^ v_snd.l);
}

/**
 * \brief   Operador bitwise que retira o topo da Stack e colocar na Stack o seu valor representado em Complemento2.
 * @param s Stack
 */
void not(struct Stack *s) {
    elemdata v_top = pop(s);
    push(s, Long, ~(v_top.l));
}

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
void arroba(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    elemtype t_trd = peek(s);
    elemdata v_trd = pop(s);
    pushaux(s, t_snd, v_snd);
    pushaux(s, t_top, v_top);
    pushaux(s, t_trd, v_trd);
}

/**
 * \brief   Função que troca os dois elementos do topo da stack.
 * @param s Stack
 */
void switchtop(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    pushaux(s, t_top, v_top);
    pushaux(s, t_snd, v_snd);
}

/**
 * \brief   O objetivo desta função é duplicar o topo da stack.
 * @param s Stack
 */
void underscore(struct Stack *s) {
    elemtype t_top = peek(s);
    elemdata v_top = s->p[s->size - 1].valor;
    pushaux(s, t_top, v_top);
}

/**
 * \brief   Função que tem como objetivo procurar ao longo da stack o número de índice 'n'
 *          e repeti-lo no fim da stack.
 * @param s Stack
 */
void tpindex(struct Stack *s) {
    elemdata v_n = pop(s);
    elemtype t_n = peekind(s, v_n.l);
    switch (t_n) {
        case Long:
            push(s, Long, s->p[(s->size) - 1 - v_n.l].valor.l); break;
        case Double:
            push(s, Double, s->p[(s->size) - 1 - v_n.l].valor.d); break;
        case String:
            push(s, String, s->p[(s->size) - 1 - v_n.l].valor.str); break;
        case Char:
            push(s, Char, s->p[(s->size) - 1 - v_n.l].valor.c); break;
        default : break;
    }
}

/**
 * \brief   Função que lê uma linha e a coloca no topo da Stack.
 * @param s Stack
 */
void leitura(struct Stack *s) {
    char *x = (char *) malloc(10000 * sizeof(char)); //aloca mem
    assert(scanf("\n%100[^\n]", x) == 1); //lê só uma linha
    push(s, String, x);
}

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo long.
 * @param s Stack
 */
void trsint(struct Stack *s) {
    elemtype t_n = peek(s);
    elemdata v_n = pop(s);
    switch (t_n) {
        case Double:
            push(s, Long, (int) v_n.d); break;
        case String:
            push(s, Long, atoi(v_n.str)); break;
        case Char:
            push(s, Long, (int) v_n.c); break;
        default : break;
    }
}

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo double.
 * @param s Stack
 */
void trsdouble(struct Stack *s) {
    elemtype t_n = peek(s);
    elemdata v_n = pop(s);
    switch (t_n) {
        case Long:
            push(s, Double, (double) v_n.l); break;
        case String:
            push(s, Double, atof(v_n.str)); break;
        case Char:
            push(s, Double, (double) v_n.c); break;
        default : break;
    }
}

/**
 * \brief   Função que transforma um elemento de qualquer tipo para o tipo char.
 * @param s Stack
 */
void trschar(struct Stack *s) {
    elemtype t_n = peek(s);
    elemdata v_n = pop(s);
    switch (t_n) {
        case Long:
            push(s, Char, (char) v_n.l); break;
        case Double:
            push(s, Char, (char) v_n.d); break;
        default : break;
    }
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e 
 *          se forem iguais coloca 1 na stack ou 0 caso contrário.
 * @param s Stack
 */
void igual(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothString(t_top, t_snd))
        push(s, Long, !strcmp(v_top.str, v_snd.str));
    else
    push(s, Long, elemDouble(t_top, v_top) == elemDouble(t_snd, v_snd));
}

/**
 * \brief   Função que devolve 1 se o 2º elemento for maior que o do topo da Stack ou 0, caso contrário.
 * @param s Stack
 */
void maior(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothString(t_top, t_snd))
        push(s, Long, strcmp(v_top.str, v_snd.str) < 0);
    else
    push(s, Long, elemDouble(t_snd, v_snd) > elemDouble(t_top, v_top));
}

/**
 * \brief   Função que devolve 1 se o 2º elemento for menor que o do topo da Stack ou 0, caso contrário.
 * @param s Stack
 */
void menor(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothString(t_top, t_snd))
        push(s, Long, strcmp(v_top.str, v_snd.str) > 0);
    else
    push(s, Long, elemDouble(t_snd, v_snd) < elemDouble(t_top, v_top));
}

/**
 * \brief   Função que retira o elemento do topo da Stack e
 *          coloca na Stack o resultado do seu valor lógico invertido.
 * @param s Stack
 */
void invertevl(struct Stack *s){
    elemdata v_top = pop(s);
    if (v_top.l == 0) push(s, Long, 1);
    else push(s, Long, 0);
}

/**
 * \brief   Função auxiliar que recebe o tipo e o data de um elemento e devolve o data em Double.
 * @param t Tipo do elemento
 * @param v Data do elemento
 * @returns Valor do elemento no tipo Double.
 */
double elemDouble(elemtype t, elemdata v) {
  switch (t) {
    case Long:
          return v.l*1.0; break;
    case Double: 
          return v.d; break;
    default: return -1;
  }
}

/**
 * \brief   Retira os 2 elementos do topo da Stack e
 *          coloca o valor do 1º elemento caso ambos sejam verdadeiros
 *          ou 0, caso contrário.
 * @param s Stack
 */
void econjuncao(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (elemDouble(t_top, v_top) && elemDouble(t_snd, v_snd)) pushaux(s, t_top, v_top);
    else push(s, Long, 0);
}

/** 
 * \brief   Retira os 2 elementos do topo da Stack e:
 *          Coloca 0 na Stack se os 2 elementos forem falsos,
 *          o 2º elemento caso sejam ambos verdadeiros 
 *          ou o elemento de valor lógico 1 caso algum deles seja falso.
 * @param s Stack
 */
void edisjuncao(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if ((int)elemDouble(t_snd, v_snd)) pushaux(s, t_top, v_top);
    else pushaux(s, t_snd, v_snd);
}

/** 
 * \brief   Retira os 2 elementos do topo da Stack e coloca o elemento maior na Stack.
 * @param s Stack
 */
void emaior(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothString(t_top, t_snd)){
        if (strcmp(v_top.str, v_snd.str) < 0)
            push(s, String, v_snd.str);
        else push(s, String, v_top.str);
    }
    else{
        switch (elemDouble(t_top, v_top) > elemDouble(t_snd, v_snd)) {
        case 1: 
            pushaux(s, t_top, v_top); break;
        default: 
            pushaux(s, t_snd, v_snd); break;
        }
    }
}

/**
 * \brief   Retira os 2 elementos do topo da Stack e coloca o elemento menor na Stack.
 * @param s Stack
 */
void emenor(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isBothString(t_top, t_snd)){
        if (strcmp(v_top.str, v_snd.str) > 0)
            push(s, String, v_snd.str);
        else push(s, String, v_top.str);
    }
    else{
        switch (elemDouble(t_top, v_top) < elemDouble(t_snd, v_snd)) {
            case 1: 
                pushaux(s, t_top, v_top); break;
            default: 
                pushaux(s, t_snd, v_snd); break;
        }
    }
}

/**
 * \brief   Função que retira os 3 elementos do topo da Stack e:
 *          Se o 3º elemento do topo for verdadeiro, volta a colocar o 2º elemento na Stack.
 *          Caso contrário, volta a colocar o elemento do topo na Stack.
 * @param s Stack
 */
void ifthenelse(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    elemtype t_trd = peek(s);
    elemdata v_trd = pop(s);
    if(isArray(t_trd)){
        if ((v_trd.arr)->size == 0) pushaux(s, t_top, v_top);
        else{
             if ((int)elemDouble(t_trd, v_trd)) pushaux(s, t_snd, v_snd);
             else pushaux(s, t_top, v_top);
        }
    }
    else{
        if ((int)elemDouble(t_trd, v_trd)) pushaux(s, t_snd, v_snd);
        else pushaux(s, t_top, v_top);
    }
}

/**
 * \brief     Função que coloca a variável na Stack.
 * @param s   Stack
 * @param var Variável
 */
void pushvar (struct Stack *s,char var) {
    char *varstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    switch (strchr(varstr, var) != NULL) {
        case 1:
            pushaux(s, s->vars[var-65].type, s->vars[var-65].valor); break;
        default: break;
    }
}

/**
 * \brief     Função que altera o valor e o tipo da variável para os do topo da Stack.
 * @param s   Stack
 * @param var Variável
 */
void copiatopo(struct Stack *s,char var){
    char *varstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    switch (strchr(varstr, var) != NULL){
        case 1:
            copy(s, var);
        break;
        default: break;
    }
}

/**
 * \brief     Função que altera o valor e o tipo da variável para os do topo da Stack.
 * @param s   Stack
 * @param var Variável
 */
void copy (struct Stack *s, char var){
    elemtype t_top = peek(s);
    elemdata v_top = s->p[s->size - 1].valor;
    int i;
    switch (t_top){
        case (String):
            s->vars[var-65].valor.str = strdup(v_top.str) ;
        break;
        case (Array):
            s->vars[var-65].valor.arr = criar_stack();
            for (i=0;i<(v_top.arr)->size; i++){
                pushaux (s->vars[var-65].valor.arr, (v_top.arr)->p[i].type,(v_top.arr)->p[i].valor );
            }
        break;
        default: 
            s->vars[var-65].valor = v_top;
        break;
    }
    s->vars[var-65].type = t_top;
}

/**
 * \brief   Função que retira o elemento do topo da Stack e:
 *          Caso seja uma string ou um array, coloca o seu comprimento na Stack;
 *          Caso seja um número, coloca na Stack um array inicializado a 0 com todos os inteiros até n,
 *          sendo n o elemento do topo da Stack.
 * @param s Stack
 */
void virgula(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    struct Stack *s_array;
    long i;
    switch (t_top) {
        case (String) :
            push (s, Long, (long)strlen (v_top.str));
            break;
        case (Array) : 
            v_top.l = v_top.arr->size;
            push(s,Long, v_top.l);
            break;
        case (Long) : 
            s_array = criar_stack();
            for (i=0; i < v_top.l; i++)
                push(s_array, Long, i);
            push(s, Array, s_array);
        break;
        case (Double) :
            s_array = criar_stack();
            for (i=0; i < (long)v_top.d; i++)
                push(s_array, Long, i);
            push(s, Array, s_array);
            break; 
        default:break;
    }
} 

/**
 * \brief   Função auxiliar que transforma um char numa String apenas com esse char.
 * @param x Char
 * @param s String
 */
void trsstring(char x, char *s){
    *s = x;
    *(s+1)='\0';
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e:
 *          Caso sejam os 2 arrays, concatena os arrays;
 *          Caso o elemento do topo seja um array, adiciona o 2º elemento da Stack ao início do array e coloca o array resultante na Stack;
 *          Caso o 2º elemento do topo seja um array, adiciona o elemento do topo ao fim do array e coloca o array resultante na Stack;
 * @param s Stack
 */
void concat_arrays(struct Stack *s){
    struct Stack *s_array = criar_stack();
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s); 
    elemtype t_tmp; elemdata v_tmp;
    int size, i;
    if (isBothArray(t_top, t_snd)){
        size = (v_top.arr)->size;
        for (i = 0 ;i < size ; i++){
            t_tmp = (v_top.arr)->p[i].type;
            v_tmp = (v_top.arr)->p[i].valor;
            pushaux (v_snd.arr, t_tmp, v_tmp);
        }
        push (s, Array, v_snd);
    }
    else{
        if (isArray(t_snd)){
                pushaux(v_snd.arr, t_top, v_top);
                push(s, Array, v_snd);
        }
        else{
            size = (v_top.arr)->size ;
            pushaux(s_array, t_snd, v_snd);
            for (i=0; i<size; i++){
                t_tmp = (v_top.arr)->p[i].type;
                v_tmp = (v_top.arr)->p[i].valor;
                pushaux(s_array, t_tmp, v_tmp);    
            }
            push(s, Array, s_array);
        }
    }
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack e:
 *          Caso sejam os 2 strings, concatena as strings;
 *          Caso o elemento do topo seja uma string, adiciona o 2º elemento da Stack ao início da string e coloca a string resultante na Stack;
 *          Caso o 2º elemento do topo seja uma string, adiciona o elemento do topo ao fim da string e coloca a string resultante na Stack.
 * @param s Stack
 */
void concat_strings(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    char *aux = malloc(1000*sizeof(char));
    if (isBothString (t_top, t_snd))
        push(s, String, strcat (v_snd.str, v_top.str));
    else {
        if (isString(t_top)){
            if (t_snd == Char){
                trsstring(v_snd.c, aux);
                push(s, String, strcat(aux, v_top.str));
            }
        }
        else{
            trsstring(v_top.c, aux);
            push(s, String, strcat(v_snd.str, aux));
        }
    }
}

/**
 * \brief   Função que invoca o respetivo concat de strings ou arrays.
 * @param s Stack
 */
void concat(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isAnyArray(t_top, t_snd)) concat_arrays(s);
    if (isAnyString(t_top, t_snd)) concat_strings(s);
}

/**
 * \brief   Função geral do operador '+' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_mais(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isAnyArray(t_top, t_snd) || isAnyString(t_top, t_snd)) concat(s);
    else soma(s);
}

/**
 * \brief   Função que retira o elemento do topo da Stack (array/string) e
 *          retira-lhe o último elemento (se for array, o do topo) e coloca-o na Stack.
 * @param s Stack
 */
void take_last(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    if (isArray(t_top)) {
        elemtype t_arr = peek(v_top.arr);
        elemdata v_arr = pop(v_top.arr);
        push(s, Array, v_top);
        push(s,t_arr,v_arr);
    }
    else{
        int i = 0;
        char *aux = malloc(strlen(v_top.str) * sizeof(char) + 1);
        while (v_top.str[i+1] != '\0') {
            i++;
        }
        aux[0] = v_top.str[i];
        v_top.str[i] = '\0';
        push(s, String, v_top.str);
        push(s, String, aux);
    }
}

/**
 * \brief   Função geral do operador ')' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_pFechado(struct Stack *s){
    elemtype t_top = peek(s);
    if (isArray(t_top) || isString(t_top)) take_last(s);
    else parentesesFechado(s);
}

/**
 * \brief   Função que retira o elemento do topo da Stack (array/string) e
 *          retira-lhe o 1º elemento (se for array, o do fundo) o e coloca-o na Stack.
 * @param s Stack
 */
void take_fst(struct Stack *s){
    elemtype t_top = peek(s);
    elemdata v_top = pop(s);
    if (isArray(t_top)) {
        elemtype t_n = peekind2(v_top.arr, 0);
        elemdata v_n = pop_bottom(v_top.arr);
        push(s, Array, v_top.arr);
        push(s, t_n , v_n);
    }
    else{
        int i = 0;
        char *aux = malloc(strlen(v_top.str) * sizeof(char) + 1);
        aux[0] = v_top.str[0];
        while (v_top.str[i+1] != '\0') {
            v_top.str[i] = v_top.str[i+1];
            i++;
        }
        v_top.str[i] = '\0';
        push(s, String, v_top.str);
        push(s, String, aux);
    }
}

/**
 * \brief   Função geral do operador '(' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_pAberto(struct Stack *s){
    elemtype t_top = peek(s);
    if (isArray(t_top) || isString(t_top)) take_fst(s);
    else parentesesAberto(s);
}

/**
 * \brief   Função que retira da Stack o elemento do topo da Stack(Array) e coloca na Stack todos os seus elementos.
 * @param s Stack
 */
void til(struct Stack *s){
    elemdata s_array = pop(s);
    elemtype t_tmp;
    elemdata v_tmp;
    int size = (s_array.arr)->size, i=0;
    for (;i < size ; i++){
        t_tmp = (s_array.arr)->p[i].type;
        v_tmp = (s_array.arr)->p[i].valor;
        push (s, t_tmp, v_tmp);
    }
}

/**
 * \brief   Função geral do operador '~' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_til(struct Stack *s){
    switch (isArray(peek(s))){
        case 1:
            til(s); break;
        default:
            not(s); break;
    }
}

/**
 * \brief   Função que retira os 2 primeiros elementos da Stack (Strings) e coloca na Stack
 *          o índice na String (2º elemento do topo) onde se inicia a Substring (elemento do topo)
 *          ou -1 caso não exista Substring.
 * @param s Stack
 */
void procura_substr(struct Stack *s){
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    char *sup = strstr(v_snd.str,v_top.str);
    long r=-1;
    if (sup) 
       push(s, Long,sup - v_snd.str);
    else push(s, Long, r);
}

/**
 * \brief   Função geral do operador '#' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_cardinal(struct Stack *s){
    switch (isString(peek(s))){
        case 1:
            procura_substr(s); break;
        default:
            exponenciacao(s); break;
    }
}

/**
 * \brief   Função que lê todo o input de uma string.
 * @param s Stack
 */
void lermtlinhas(struct Stack *s) {
    char *y = (char *) malloc(10000 * sizeof(char)); 
    char *x = (char *) malloc(10000 * sizeof(char)); 
    while (fgets(x, 10000, stdin)){
        strcat(y,x);
    }
    push(s, String, y);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde o do topo é o índice
 *          e o 2º um array/string. Procura o elemento do índice dado na string/array e coloca-o na Stack.
 * @param s Stack
 */
void procura_por_indice(struct Stack *s){
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    if (isArray (t_snd))
        pushaux (s, (v_snd.arr)->p[(int)v_top.l].type, (v_snd.arr)->p[(int)v_top.l].valor);
    else 
        push(s, Char , v_snd.str[(int)v_top.l]);
}

/**
 * \brief   Função geral do operador '=' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_igual(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isBothString(t_top, t_snd)) igual(s);
    else if  (isArray(peekind(s,1)) || isString(peekind(s,1))) procura_por_indice(s);
    else igual(s);
}


/**
 * \brief   Função que retira os 2 elementos do topo da Stack e concatena recursivamente o
 *          array/string do 2º elemento do topo da Stack n vezes, onde n é o elemento do topo da Stack.
 * @param s Stack
 */
void concat_xvezes(struct Stack *s) {
    elemdata v_top = pop(s);
    elemtype t_rep = peek(s);
    elemdata v_rep = pop(s);
    if (isString(t_rep)){
        char *aux = malloc (strlen(v_rep.str) * sizeof(char) + 1);
        aux[0] = '\0';
        for(int i = 0; i < v_top.l; i++) strcat(aux, v_rep.str);
        push(s, String, aux);
    }
    else{
        struct Stack *s_array = criar_stack();
        for (int j=0; j < v_top.l; j++){
            elemtype t_tmp; elemdata v_tmp;
            int size, i;
            size = (v_rep.arr)->size;
            for (i=0; i < size ; i++){
                t_tmp = (v_rep.arr)->p[i].type;
                v_tmp = (v_rep.arr)->p[i].valor;
                pushaux (s_array, t_tmp, v_tmp);
            }
        }
        push(s, Array, s_array);
    }
}

/**
 * \brief   Função geral do operador '*' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_asterisco(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isAnyArray(t_top, t_snd) || isAnyString(t_top, t_snd)) concat_xvezes(s);
    else mult(s);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack (strings) e, sendo o elemento do topo a substring, separa 
 *          o 2º elemento do topo (string) por essa substring-
 * @param s Stack
 */
void sepstr_substr(struct Stack *s){
    char *token;
    elemdata v_top = pop(s);
    elemdata v_snd = pop(s);
    struct Stack *s_array = criar_stack();
    while ((token = strtok_r(v_snd.str, v_top.str, &v_snd.str))){ //separa a string da substring e guarda no token
        push(s_array, String, token);
    }
    push(s, Array, s_array);
}

/**
 * \brief   Função geral do operador '/' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_barra(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isBothString(t_top, t_snd)) sepstr_substr(s);
    else divisao(s);
}

/**
 * \brief   Função que retira o elemento do topo da Stack (string) e separa essa string pela ocorrência de whitespaces.
 * @param s Stack
 */
void sepstr_whitespc(struct Stack *s){
    char *token;
    elemdata v_top = pop(s);
    struct Stack *s_array = criar_stack();
    while ((token = strtok_r(v_top.str, " \t\n", &v_top.str))){ //separa a string e guarda no token
        push(s_array, String, token);
    }
    push(s, Array, s_array);
}

/**
 * \brief   Função que retira o elemento do topo da Stack (string) e separa essa string pela ocorrência de newlines.
 * @param s Stack
 */
void sepstr_newlns(struct Stack *s){
    char *token;
    elemdata v_top = pop(s);
    struct Stack *s_array = criar_stack();
    while ((token = strtok_r(v_top.str, "\n", &v_top.str))){ //separa a string e guarda no token
        push(s_array, String, token);
    }
    push(s, Array, s_array);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde n é o elemento do topo
 *          e o 2º elemento do topo o array/string, e coloca na Stack os n elementos do início do array/string.
 * @param s Stack
 */
void buscaInicio(struct Stack *s){
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    struct Stack *s_array = criar_stack();
    char *aux = malloc(strlen(v_snd.str) * sizeof(char) + 1);
    int i = 0;
    switch (t_snd) {
        case (Array) :
            while (v_top.l){
                push(s_array, peekind2(v_snd.arr, 0), pop_bottom(v_snd.arr));
                (v_top.l)--;
            }
            push(s, Array, s_array); break;
        case (String) :
            while (v_top.l) {
                aux[i] = v_snd.str[i];
                i++;  v_top.l--;
            }
            aux[i] = '\0';
            push(s, String, aux); break;
        default: break;
    }
}

/**
 * \brief   Função geral do operador '<' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_menor(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isBothString(t_top, t_snd)) menor(s);
    else if  (isArray(peekind(s,1)) || isString(peekind(s,1))) buscaInicio(s);
    else menor(s);
}

/**
 * \brief   Função que retira os 2 elementos do topo da Stack, onde n é o elemento do topo
 *          e o 2º elemento do topo o array/string, e coloca na Stack os n elementos do fim do array/string.
 * @param s Stack
 */
void buscaFim(struct Stack *s){
    elemdata v_top = pop(s);
    elemtype t_snd = peek(s);
    elemdata v_snd = pop(s);
    struct Stack *s_array = criar_stack();
    char *aux = malloc(strlen(v_snd.str) * sizeof(char) + 1);
    int i;
    int z = 0;
    switch (t_snd) {
        case (Array) :
            while (v_top.l) {
                push(s_array, v_snd.arr->p[v_snd.arr->size - v_top.l].type, v_snd.arr->p[v_snd.arr->size - v_top.l].valor);
                (v_top.l)--;
            }
            push(s, Array, s_array); break;
        case (String) :
            i = strlen(v_snd.str) - v_top.l;
            while (v_top.l) {
                aux[z] = v_snd.str[i];
                z++; i++; v_top.l--;
            }
            aux[z] = '\0';
            push(s,String, aux); break;
        default: break;
    }
}

/**
 * \brief   Função geral do operador '>' que invoca as operações consoante o tipo dos elementos.
 * @param s Stack
 */
void operador_maior(struct Stack *s){
    elemtype t_top = peek(s);
    elemtype t_snd = peekind(s, 1);
    if (isBothString(t_top, t_snd)) maior(s);
    else if  (isArray(peekind(s,1)) || isString(peekind(s,1))) buscaFim(s);
    else maior(s);
}
