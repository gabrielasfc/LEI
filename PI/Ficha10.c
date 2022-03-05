//Codeboard : https://codeboard.io/projects/244195

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq, *dir;
} *ABin;


//1
//a
ABin removeMenor(ABin *a){
    ABin min = NULL;
	while (*a != NULL && (*a)->esq != NULL){
		a = &((*a)->esq);
	}
	min = *a;
	*a = (*a)->dir;
	return min;
}


//b
void removeRaiz(ABin *a){
	ABin tmp = *a, min;
	if ((*a)->esq == NULL) *a = (*a)->dir;
	else if ((*a)->dir == NULL) *a = (*a)->esq;
	else{
		min = removeMenor(&((*a)->dir));
		min->esq = (*a)->esq;
		min->dir = (*a)->dir;
		*a = min;
		free(tmp);
	}
}


//c
int removeElem(ABin *a, int x){
	while (*a != NULL && (*a)->valor != x){
		if (x < (*a)->valor) a = &((*a)->esq);
		else a = &((*a)->dir);
	}
	if (*a == NULL) return -1;
	else removeRaiz(a);
	return 0;
}


//2
void rodaEsquerda(ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}

void rodaDireita(ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}

//a
void promoveMenor(ABin *a){
    if (*a != NULL && (*a)->esq != NULL){
		promoveMenor(&((*a)->esq));
		rodaDireita(a);
	}
}


//b
void promoveMaior(ABin *a){
    if (*a != NULL && (*a)->dir != NULL){
		promoveMaior(&((*a)->dir));
		rodaEsquerda(a);
	}    
}


//c
ABin removeMenor2(ABin *a){
    promoveMenor(a);
    ABin r = *a;
    *a = (*a)->dir;
    return r;
}