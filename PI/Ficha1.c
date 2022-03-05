#include <stdio.h>

/*
1.1
int x, y;
x = 3; 
y = x+1;
x = x*y; 
y = x + y;
printf("%d %d\n", x, y);

Definimos as variáveis x e y
Atribuímos o valor 3 a x
Damos o valor 3+1=4 a y
Atualizamos o valor de x para 3*4=12
Atualizamos o valor de y para 12+4=16.
O resultado é os 2 valores finais em x e y : "12 16"


1.2
int x, y;
x = 0;
printf ("%d %d\n", x, y);

Definimos x e y
x=0
Não atribuímos valor a y e não dá erro ao compilar, mas é um erro de código.


1.3
char a, b, c;
a = 'A'; b = ' '; c = '0';
printf ("%c %d\n", a, a);
a = a+1; c = c+2;
printf ("%c %d %c %d\n", a, a, c, c);
c = a + b;
printf ("%c %d\n", c, c);

Definimos a, b e c
Atribuímos chars às variáveis
Imprimimos o char em c e o seu ASCII : "0 48"
Atualizamos a para o char a seguir na tabela ASCII ('B')
Atualizamos c para o char 2 posições a seguir na tabela ('2')
Imprimimos o char em a, o seu ASCII, o char em C, o seu ASCII : "B 66 2 50"
Atualizamos b para o char com a posição (a(66)+b(32)=98), ou seja, 'b'
Imprimimos o char em c e o seu ASCII : "b 98"


1.4
int x, y;
x = 200; y = 100;
x = x+y; y = x-y; x = x-y;
printf ("%d %d\n", x, y);

Definimos x e y
Atribuímos o valor 200 a x e 100 a y
Atualizamos x=200+100=300
Atualizamos y=300-100=200
Atualizamos x=300-200=100
Imprimimos x e y : "100 200"
*/



//3
void replicate(int n, char c){
    int i;
    for (i=0; i<n; i++) putchar(c);
}


//3.1
void quadrado(int n){
	int i, j;
	for (i=0; i<n; i++){
		replicate(n, '#');
		putchar('\n');
	}
}


//3.2
void xadrez(int n){
    int i, j;
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
             if (i%2 == j%2) putchar('#');
             else putchar('_');
		}
    	putchar('\n');
    }
}


//3.3
//a
void trianguloV(int n){
	int i, j;
	for (i=0; i<n; i++){
		replicate(i, '#');
		putchar('\n');
	}
	for (i=n; i>0; i--){
		replicate(i, '#');
		putchar('\n');
	}
}


//b
void trianguloH(int n){
	int i, j, c=1, e=n-1;
	for (i=0; i<n; i++){
		replicate(e, ' ');
		replicate(c, '#');
		c += 2; e--;
	    putchar('\n');
	}
}