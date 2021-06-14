//Codeboard: https://codeboard.io/projects/238187

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
char *palavra;
int ocorr;
struct celula * prox;
} * Palavras;



//1
void libertaLista(Palavras l){
	while (l != NULL){
		Palavras aux = l;
		l = l->prox;
		free(aux);
	}
}



//2
int quantasP(Palavras l){
	int r=0;
	while (l != NULL){
		l = l->prox;
		r++;
	}
	return r;
}



//3
void listaPal(Palavras l){
	while (l != NULL){
		printf("%s %d\n", l->palavra, l->ocorr);
		l = l->prox;
	}
}



//4
char * ultima(Palavras l){
	if (l==NULL) return NULL;
	while (l->prox != NULL){
		l = l->prox;
	}
	return (l->palavra);
}



//5
Palavras acrescentaInicio(Palavras l, char *p){
	Palavras new = malloc(sizeof(struct celula));
	new->palavra = strdup(p);
	new->ocorr = 1;
	new->prox = l;
	return new;
}



//6
Palavras acrescentaFim(Palavras l, char *p){
	Palavras new = malloc(sizeof(struct celula));
	new->palavra = strdup(p);
	new->ocorr = 1;
	new->prox = NULL;
	if (l == NULL) return new;
	else{
		Palavras inicio = l;
		while (l->prox != NULL){
			l = l->prox;
		}
		l->prox = new;
		return inicio;
	}
}



//7
Palavras acrescenta(Palavras l, char *p){
	Palavras inicio = l;
	while (l != NULL && strcmp(l->palavra, p) < 0)
		l = l->prox;
	if (l != NULL && strcmp(l->palavra, p) == 0) l->ocorr++;
	else if (l != NULL && strcmp(l->palavra, p) > 0) acrescentaInicio(l, p);
	else inicio = acrescentaInicio(inicio, p);
	return inicio;
}



//8
struct celula *maisFreq(Palavras l){
	int max = 0;
	Palavras r = NULL;
	while (l != NULL){
		if (l->ocorr > max){
			max = l->ocorr;
			r = l;
		}
		l = l->prox;
	}
	return r;
}