/**
 @file  parser.c
 @brief Ficheiro com as funções relativas ao parse
 */

#include "parser.h"

/**
 * \brief       Função que invoca, consoante o token, as operações matemáticas simples ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token Operador
 */
void operadores_mat(struct Stack *s, char token){
    switch (token) {
        case '+': 
            operador_mais(s); break;   
        case '-': 
            subtracao(s); break;
        case '*': 
            operador_asterisco(s); break;
        case '/':
            operador_barra(s); break;
        case '(':
            operador_pAberto(s); break;
        case ')':
            operador_pFechado(s); break;
        case '%': 
            modulo(s); break;
        case '#':
            operador_cardinal(s); break;
        default: break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as operações bitwise ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token Operador
 */
void operadores_bitwise(struct Stack *s, char token){
    switch (token) {
        case '&': 
           conjuncao(s); break;
        case '|':
            disjuncao(s); break; 
        case '^': 
            xor(s); break;
        case '~':
            operador_til(s); break;
        default: break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as operações de conversão.
 * @param s     Stack
 * @param token Operador
 */
void operadores_conversoes(struct Stack *s, char token){
    switch (token) {
        case 'c': 
            trschar(s); break;
        case 'i': 
            trsint(s); break;
        case 'f':
            trsdouble(s); break;
        case 'l':
            leitura(s); break;
        default: break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as operações relativas à manipulação da Stack.
 * @param s     Stack
 * @param token Operador
 */
void operadores_stack(struct Stack *s, char token){
    switch (token) {
        case '@': 
            arroba(s); break;
        case ';': 
            pop(s); break;
        case '_':
            underscore(s); break;
        case '$':
            tpindex(s); break;
        case '\\':
            switchtop(s); break;
        default: 
            operadores_conversoes(s, token); break;
    }
}

/**
 * \brief       Função que invoca, consoante o char a seguir ao "e", as operações lógicas.
 * @param s     Stack
 * @param token Operador
 */
void operadores_e(struct Stack *s, char token) {
    switch(token) {
        case '&':
            econjuncao(s); break;
        case '|':
            edisjuncao(s); break;
        case '>':
            emaior(s); break;
        case '<':
            emenor(s); break;
        default: break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as operações lógicas ou
 *              as operações de strings/arrays correspondentes.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_logica(struct Stack *s, char *token) {
    switch(*token){
        case '!' :
            invertevl(s); break;
        case '?' :
            ifthenelse(s); break;
        case '=' :
            operador_igual(s); break;
        case '>' :
            operador_maior(s); break;
        case '<' :
            operador_menor(s); break;
        case 'e' :
            operadores_e(s, *(token+1)); break;
        default: 
            operadores_bitwise(s, *token); break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as respetivas operações das variáveis.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_variaveis(struct Stack *s, char *token){
    char *sovars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    switch (strchr(sovars, *token) != NULL) {
        case 1:
            pushvar(s, *token); break;
        default: //se o 1º char for ':'
            switch (strchr(sovars, *(token+1)) != NULL) {
                case 1:
                    copiatopo(s, *(token+1)); break;
                default: break;
            } break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, as novas operações relativas a arrays/strings do guião 4.
 * @param s     Stack
 * @param token String com o operador
 */
void operadores_arrstr(struct Stack *s, char *token){
    switch (*token){
        case ',' :
            virgula (s); break;
        case 't' : 
            lermtlinhas (s); break;
        case 'S':
            switch (*(token+1) == '/'){
                case 1:
                    sepstr_whitespc(s); break;
                default:
                    break;
            } break;
        case 'N' :
            switch (*(token+1) == '/'){
                case 1:
                    sepstr_newlns(s); break;
                default:
                    break;
            } break;
        default: break;
    }
}

/**
 * \brief       Função que invoca, consoante o token, a função geral do respetivo tipo de operação.
 * @param s     Stack
 * @param token String com o operador
 */
void operacoes(struct Stack *s, char *token){
	char *tknmat = "+-*/()%#";
	char *tknstack = "@;_$\\cifl";
	char *tknlogica = "^~!?=e&e|e>e<";
    char *tknvariaveis = ":A:B:C:D:E:F:G:H:I:J:K:L:M:N:O:P:Q:R:S:T:U:V:W:X:Y:Z";
    char *tknarrstr = ",tS/N/";
	switch (strstr(tknmat, token) != NULL) {
		case 1:
			operadores_mat(s, *token); break;
		default:
			switch (strstr(tknstack, token) != NULL) {
				case 1:
					operadores_stack(s, *token); break;
				default:
					switch (strstr(tknlogica, token) != NULL) {
						case 1:
							operadores_logica(s, token); break;
						default: 
                            switch (strstr(tknvariaveis, token) != NULL) {
                                case 1:
                                    operadores_variaveis(s, token); break;
                                default:  
                                    switch (strstr(tknarrstr, token) != NULL) {
                                        case 1:
                                            operadores_arrstr(s, token); break;
                                        default: break;
                                    } break;
					        } break;
			        } break;
            }break;
    }
}

/**
 * \brief       Função auxiliar que devolve o token até ao delimitador dado.
 * @param line  Linha
 * @param delim Delimitador
 * @returns     Token
 */
char *get_token(char **line, char *delim){
    int i;
    char *token = (char *) malloc(strlen(*line) * sizeof(char));
    for(i=0; **line != '\0' && strchr(delim, **line) == NULL; i++){
        token[i] = **line;
        (*line)++;
    }
    (*line)++;
    token[i] = '\0';
    return token;
}

/**
 * \brief      Função auxiliar que tem o mesmo efeito que a get_token, mas dedicada a arrays,
 *             analisando quantos arrays podem existir dentro desse array.
 * @param line Linha
 * returns     Token
 */
char *get_token_arr(char **line){
    int i, contador=1;
    char *token = (char *) malloc(strlen(*line) * sizeof(char));
    for(i=0; **line != '\0' && contador ; i++){
        switch (**line){
            case '[':
            contador++;
            token[i] = **line;
            break;
            case ']':
            contador--; 
            token[i] = **line;
            break; 
            default:
                token[i] = **line;
                break;
        }
    (*line)++;
    }
    token[i] = '\0';
    return token;
}

/**
 * \brief       Função que coloca na Stack os números recebidos no token ou 
 *              invoca as operações, recorrendo à função auxiliar "operacoes".
 * @param s     Stack
 * @param Token Token
 */
void numberoroperation(struct Stack *s, char *token){
    char *sobra;
    int val_l = strtol(token, &sobra, 10);
    int temp = 1;
    if(strlen(sobra) == 0 && temp) {
        push(s, Long, (long)val_l);
        temp = 0;
    }
    double val_d = strtod(token, &sobra);
    if(strlen(sobra) == 0 && temp) push(s, Double, (double)val_d);
    else operacoes(s, token);
}

/**
 * \brief   Função que copia as variéveis da Stack para o Array.
 * @param s Stack
 * @returns Devolve o Array com as variáveis já introduzidas.
 */
struct Stack *copiavars(struct Stack *s) {
    struct Stack *arr = criar_stack();
    criar_variaveis(arr);
    int i;
    for(i = 0; i < 26; i++) {
        arr->vars[i] = s->vars[i];
    }
    return arr;
}

/**
 * \brief     Função que copia as variéveis do Array para a Stack.
 * @param s   Stack
 * @param arr Array 
 */
void copiavars2(struct Stack *s, struct Stack *arr) {
    int i;
    for(i = 0; i < 26; i++) {
        s->vars[i] = arr->vars[i];
    }
}

/**
 * \brief      Função principal que analisa a linha recebida no input e faz o seu parse.
 * @param s    Stack
 * @param line Linha
 */
void parse(struct Stack *s, char *line){
    struct Stack *s_array;
    int verificaempty=1; //condição -> se a linha não é vazia
    while (verificaempty){
        switch (line[0]){
            case '\0':
                verificaempty=0; break;
            case '[':
                line++;
                s_array = copiavars(s);
                parse(s_array, get_token_arr(&line));
                copiavars2(s, s_array);
                push(s, Array, s_array);
                break;
            case '\"':
                line++;
                push(s, String, get_token(&line, "\""));
                break;
            case ' ':
                line++; break;
            case '\t':
                line++; break;
            case '\n':
                line++; break;
            case '\'':
                line++;
                push(s, Char, get_token(&line, "\'"));
                break;
            default:
                numberoroperation(s, get_token(&line, " \t\n"));
                break;
        }
    }
}
