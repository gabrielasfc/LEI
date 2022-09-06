# Projeto

No âmbito da UC de Laboratórios de Informática II, foi-nos proposta a implementação de um interpretador de uma linguagem de programação orientada à stack, chamado $0M.


## Comandos:

#### Expressões Matemáticas
```
+ - * /  ->  Somar, subtrair, multiplicar e dividir
( )  ->  Decrementar e incrementar um valor
%  ->  Módulo
#  ->  Exponenciação
& | ^ ~  ->  E, ou, xor e not (bitwise) para inteiros
```

#### Stack
```
_  ->  Duplicar
;  ->  Pop
\  ->  Trocar os dois elementos do topo da stack
@  ->  Rodar os 3 elementos no topo da stack
n $  ->  Copia n-ésimo elemento para o topo da stack; 0 é o topo da stack
```

#### Lógica
```
0 ou vazio  ->  False
contrário de 0  ->  Verdadeiro
=  ->  Igual
<  ->  Menor
>  ->  Maior
!  ->  Não
e&  ->  E (com shortcut)
e|  ->  Ou (com shortcut)
e<  ->  Coloca o menor dos 2 valores na stack
e>  ->  Coloca o maior dos 2 valores na stack
?  ->  If-Then-Else
```

#### Variáveis
```
A até Z  ->  Coloca no topo da stack o conteúdo da variável
:<Letra>  ->  Copia topo da stack à variável
A  ->  Valor por omissão: 10
B  ->  Valor por omissão: 11
C  ->  Valor por omissão: 12
D  ->  Valor por omissão: 13
E  ->  Valor por omissão: 14
F  ->  Valor por omissão: 15
N  ->  Valor por omissão: '\n'
S  ->  Valor por omissão: ' '
X  ->  Valor por omissão: 0
Y  ->  Valor por omissão: 1
Z  ->  Valor por omissão: 2
```

#### Input/Output
```
l  ->  Ler linha
t  ->  Ler todas as linhas
p  ->  Imprimir topo da stack
```

#### Conversões
```
i  ->  Converter o topo da stack num inteiro
f  ->  Converter o topo da stack num double
c  ->  Converter o topo da stack para caratere
s  ->  Converter o topo da stack para string
```

#### Arrays e Strings
```
""  ->  Criar uma string
[]  ->  Criar um array
~  ->  Colocar na stack todos os elementos do array
+  ->  Concatenar strings ou arrays (ou array/string com elemento)
*  ->  Concatenar várias vezes strings ou arrays
,  ->  Tamanho ou range
=  ->  Ir buscar um valor por índice
< >  ->  Ir buscar X elems/carat do início ou fim
( )  ->  Remover 1º ou últ. elt. e colocar na stackapós o array/string
#  ->  Procurar substring na string e devolver o índice ou -1 se não encontrar
t  ->  Ler todo o input => String
/  ->  Separar string por substring => Array
S/  ->  Separar uma string por whitespace => Array
N/  ->  Separar uma string por newlines => Array
```


## Contributors:
- Beatriz Monteiro [@5ditto](https://github.com/5ditto)
- Gabriela Cunha [@gabrielasfc](https://github.com/gabrielasfc)
- Lara Ferreira [@178LaPata](https://github.com/178LaPata)
- Ricardo Lucena [@Lucena02](https://github.com/Lucena02)
