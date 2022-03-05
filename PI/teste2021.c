#include <stdio.h>
#include <stdlib.h>

//1
int tamanho(int n){
	int r=0, i=0;
	while (n!=1){
		r += n;
		if (n%2 == 0) n = n/2; else n = 1+(3*n);
		i++;
	}
	return i;
}

void swap(int *x, int *y){
	int aux = *x;
	*x = *y;
	*y = aux;
}

void bubblesort(int v[], int N){
	int i, j;
	for (i=0; i<N-1; i++){
		for (j=0; j<N-i-1; j++){
			if (v[j] > v[j+1]) swap(&v[j], &v[j+1]);
		}
	}
}

int sumhtpo(int n){
	int r = 0, i=0, t=0;
	t = tamanho(n);
	int v[t];
	for(; i<t; i++) v[i] = 0;
	while (n != 1){
		r += n;
		v[i] = n;
		if (n%2 == 0) n = n/2; else n = 1+(3*n);
		i++;
	}
	bubblesort(v, i);
	if (i<99) return -1;
	else return v[99];
}


//VERSAO LUIS
void insereOrd(int v[],int x){
	for (int i=0; i<100 && x!=0; i++){
    	if (x<v[i] || v[i]==0){
        	swap(&v[i], &x);
        }
    }
}

int sumhtpo2(int n){
    int r = 0, i=0, v[100]={0};
    while (n != 1){
        r += n;
        insereOrd(v,n);
        if (n%2 == 0) n = n/2; else n = 1+(3*n);
        i++;
    }
    if (i<99) return -1;
    else return v[99];
}



//2
int contavezes(int v[], int N, int x){
	int conta=0, i=0;
	while (i<N){
		if (v[i]==x) conta++;
		i++;
	}
	return conta;
}

int moda(int v[], int N, int *m){
	int max=0, i;
	for (i=0; i<N; i++){
		if (contavezes(v, N, v[i]) > max){
			max = contavezes(v, N, v[i]);
			*m = v[i];
		}
		else if(contavezes(v, N, v[i]) == max) return 0;
	}
	return max;
}



//3
typedef struct lligada{
	int valor;
	struct lligada *prox;
} *LInt;

int procura(LInt *l, int x){
	LInt ant = NULL;
	LInt inicio = *l;
	while (*l != NULL && (*l)->valor != x){
		ant = *l;
		l = &((*l)->prox);
	}
	if (*l == NULL) return 0;
	else{
		if (ant != NULL){
			ant->prox = (*l)->prox;
			(*l)->prox = inicio;
		}
		else *l = inicio;
	}
	return 1;
}



//4
typedef struct nodo{
	int valor;
	struct nodo *pai, *esq, *dir;
} *ABin;

int freeAB(ABin a){
	ABin esq, dir = NULL;
	if (a==NULL) return 0;
	else{
		esq = a->esq;
		dir = a->dir;
		free(a);
	}
	return 1+freeAB(esq)+freeAB(dir);
}



//5
void caminho(ABin a){
	if (a != NULL && a->pai != NULL){
		caminho(a->pai);
		if (a->pai->esq == a) printf("esq");
		else if (a->pai->dir == a) printf("dir");
  	}
}