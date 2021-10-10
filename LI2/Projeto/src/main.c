/**
 @file main.c
 @brief Ficheiro que contém a função principal do programa
 */

#include "parser.h"

/**
 * \brief   Função main do programa
 * @returns 0
 */
int main() {
    struct Stack *s = criar_stack();
    criar_variaveis(s);
    char line[10240];
    assert(fgets(line, 10240, stdin) != NULL);
    parse(s, line);
    print_stack(s);
    printf("\n");
    return 0;
}
