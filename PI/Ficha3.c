//Codeboard: https://codeboard.io/projects/224189

#include <stdio.h>

//1
/*a
int main () {
int x [15] = {1, 2, 3, 4, 5, 6, 7, 8, 9,10, 11,12,13,14,15};
int *y, *z, i;

y = x; //y passa a ser o elemento do array x[15] na posição 0 (y=1)
z = x+3; //z passa a ser o elemento do array x[15] na posição 3 (z=4)

for (i=0; i<5; i++) {
printf ("%d %d %d\n", x[i], *y, *z); //até à posição 4 do array serão printados os elementos do array
y = y+1; z = z+2;  //y=x[i]
                   //z serão os elementos das primeiras 5 posições ímpares do array a começar na 3 (4,6,8,10,12)
}

OUTPUT
1 1 4
2 2 6
3 3 8
4 4 10
5 5 12
*/



/*b
int main () {
int i, j, *a, *b;

i=3; j=5;
a = b = 42; 			//não tem efeito visto que a e b são endereços de int
a = &i; b = &j; 		//a é o endereço de i e b o endereço de j
i++; 					//i=4

j = i + *b; 			//j=4+5=9
b = a; 					//b=&i
j = j + *b;				//j=9+4=13
printf ("%d\n", j);
return 0;
}

OUTPUT
13
*/



//2
void swapM(int *x, int *y){
	int aux = *x;
	*x = *y;
	*y = aux;
}



//3
void swap(int v[], int i, int j){
	int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}



//4
int soma(int v[], int N){
	int i, soma=0;
	for (i=0; i<N; i++){
		soma = soma + v[i];
	}
	return soma;
}



//5
void inverteArray(int v[], int N){
	int i;
	int mid = N/2;
	for (i=0; i<mid; i++){
		v[i] = v[N-i-1];
	}
}



//6
int maximum(int v[], int N, int *m){
	int max=0, i;
	for (i=0; i<N; i++){
		if (v[i] > max){
			max = v[i];
		}
	}
	*m = max;
	return 0;
}



//7
void quadrados(int q[], int N){
	int i;
	q[0]=0;
	for (i=0; i<N-1; i++){
		q[i+1] = q[i] + (2*i+1);
	}
}



//8
void pascal(int v[], int N){
	int q[N-1], i;
	if (N>1){
		v[0] = v[N-1] = 1;
		pascal(q, N-1);
		for (i=1; i<N-1; i++){
			v[i] = q[i-1] + q[i];
		}
	}
}


void pascal2(int v[], int N){
	int i, j, k;
	for (i=1; i<=N; i++){
		k=1;
		for (j=1; j<=i; j++){
			printf("%d ", k);
			k = k*(i-j) / j;
		}
		printf("\n");
	}
}