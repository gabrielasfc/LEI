//Codeboard: https://codeboard.io/projects/243300

#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
	int valor;
	struct nodo *esq, *dir;
} * ABin;


ABin newABin (int r, ABin e, ABin d) {
	ABin a = malloc (sizeof(struct nodo));
	if (a!=NULL) {
	a->valor = r; a->esq = e; a->dir = d;
	}
	return a;
}


//1
//a
int altura(ABin a){
	if (a == NULL) return 0;
	if (altura(a->esq) > altura(a->dir)) return 1 + altura(a->esq);
	else return 1 + altura(a->dir);
}



//b
int nFolhas(ABin a){
	if (a == NULL) return 0;
	if (a->esq == NULL && a->dir == NULL) return 1;
	else return nFolhas(a->esq) + nFolhas(a->dir);
}



//c
ABin maisEsquerda(ABin a){
	if (a != NULL){
		while (a->esq != NULL){
			a = a->esq;
		}
	}
	return a;
}



//d
void imprimeNivel(ABin a, int l){
	if (a != NULL){
		if (l==0) printf("%d\n", a->valor);
		else{
			imprimeNivel(a->esq, l-1);
			imprimeNivel(a->dir, l-1);
		}
	}
}



//e
int procuraE(ABin a, int x){
	if (a != NULL){
		if (a->valor == x) return 1;
		else return (procuraE(a->esq, x) || procuraE(a->dir, x));
	}
	return 0;
}



//2 --> ÁRVORES BINÁRIAS DE PROCURA
//f
struct nodo *procura(ABin a, int x){
	while (a != NULL && a->valor != x){
		if (a->valor > x) a = a->esq;
		else a = a->dir;
	}
	return a;
}



//g
int nivel(ABin a, int x){
	if (a == NULL) return -1;
	if (x == a->valor) return 1;
	if (nivel(a->esq, x) == -1 && nivel(a->dir, x) == -1) return -1;
	if (nivel(a->esq, x) == -1) return (1 + nivel(a->dir, x));
	if (nivel(a->dir, x) == -1) return (1 + nivel(a->esq, x));
	if (nivel(a->dir, x) > nivel(a->esq, x)) return (1 + nivel(a->esq, x));
	else return (1 + nivel(a->dir, x));
}



//h
void imprimeAte(ABin a, int x){
	if (a != NULL){
		imprimeAte(a->esq, x);
		if (a->valor < x){
			printf("%d ", a->valor);
		}
		imprimeAte(a->dir, x);
	}
}