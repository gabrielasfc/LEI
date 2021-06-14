//Ficheiro com funções importantes de listas ligadas

#include <stdio.h>
#include <stdlib.h>


typedef struct lligada{
	int valor;
	struct lligada *prox;
} *LInt;


//comprimento da lista
int length(LInt l){
	int len=0;
	while (l != NULL){
		l = l->prox;
		len++;
	}
	return len;
}



//insere elemento ordenadamente
void insereord(LInt *l, int x){
	LInt new = malloc(sizeof(struct lligada));
	new->valor = x;
	new->prox = NULL;
	LInt ant = NULL;
	while (*l != NULL && x > (*l)->valor){
		ant = *l;
		l = &((*l)->prox);
	} //avança até inserir na posição entre ant e *l
	if (ant != NULL){
		new->prox = *l;
		ant->prox = new;
	}
	else{
		new->prox = *l;
		*l = new;
	}
}



//remove elemento
int remove(LInt *l, int x){
	LInt ant = NULL;
	while (*l != NULL && (*l)->valor != x){
		ant = *l;
		l = &((*l)->prox);
	}
	if (*l == NULL) return -1; //x não está na lista
	if (ant != NULL){
	    LInt aux = *l;
		ant->prox = (*l)->prox;
		free(aux);
	}
	else{
	    LInt aux = *l;
		*l = (*l)->prox;
		free(aux);
	}
}



//liberta todo o espaço da lista
int freeL(LInt l){
	while (l != NULL){
		LInt aux = l->prox;
		free(l);
		l = aux;
	}
}



//inverte a lista
LInt reverseL(LInt l){
	LInt ant = NULL, next = NULL;
	while (l != NULL){
		next = l->prox;
		l->prox = ant;
		ant = l;
		l = next;
	}
	return ant;
}



//concatena 2 listas
void concat(LInt *a, LInt b){
	while (*a != NULL){
		a = &((*a)->prox);
	}
	*a = b;
}



//junta 2 listas ordenadamente
void merge(LInt *r, LInt a, LInt b){
	if (a != NULL || b != NULL){
		if (b == NULL || a != NULL && a->valor < b->valor){
			*r = a;
			merge(&((*r)->prox), a->prox, b);
		}
		else{
			*r = b;
			merge(&((*r)->prox), a, b->prox);
		}
	}
}



//acrescenta 1 elemento no fim da lista
void append(LInt *l, int x){
	LInt new = malloc(sizeof(struct lligada));
	new->valor = x;
	new->prox = NULL;
	while (*l != NULL){
		l = &((*l)->prox);
	}
	*l = new;
}



//elimina o ultimo elemento da lista
void init(LInt *l){
	while ((*l)->prox != NULL){
		l = &((*l)->prox);
	}
	free(*l);
	*l = NULL;
}



//clonar a lista
LInt cloneL(LInt l){
	if (l==NULL) return NULL;
	LInt new = malloc(sizeof(struct lligada));
	new->valor = l->valor;
	new->prox = cloneL(l->prox);
	return new;
}



//remove os elementos da lista a partir da célula n
//devolve o comprimento da lista resultante
int take(int n, LInt *l){
	int i=0;
	for (i; *l != NULL && i<n; i++){
		l = &((*l)->prox);
	}
	if (*l == NULL) return i;
	while (*l != NULL){
		LInt aux = (*l)->prox;
		free(*l);
		*l = aux;
	}
	return n;
}



//remove os n primeiros elementos
//devolve o comprimento da lista resultante
int drop(int n, LInt *l){
	int i;
	for (i=0; *l != NULL && i<n; i++){
		LInt aux = (*l)->prox;
		free(*l);
		*l = aux;
	}
	return i;
}
