//Ficheiro com funções importantes de árvores binárias

#include <stdio.h>
#include <stdlib.h>


typedef struct nodo {
	int valor;
	struct nodo *esq, *dir;
} *ABin;


//testa se é de procura
int maximo(ABin a){
	while (a != NULL && a->dir != NULL){
		a = a->dir;
	}
	return a->valor;
}

int minimo(ABin a){
	while (a != NULL && a->esq != NULL){
		a = a->esq;
	}
	return a->valor;
}

int testaProcura(ABin a){
	if (a == NULL) return 1;
	if (a->esq != NULL && maximo(a->esq) > a->valor) return 0;
	if (a->dir != NULL && minimo(a->dir) < a->valor) return 0;
	if (!testaProcura(a->esq) || !testaProcura(a->dir)) return 0;
}



//altura da árvore
int altura(ABin a){
	if (a==NULL) return 0;
	int e = altura(a->esq);
	int d = altura(a->dir);
	if (e > d) return 1+e;
	else return 1+d;
}



//liberta a árvore e retorna o nº de elems removidos
int freeAB(ABin a){
	if (a == NULL) return 0;
	ABin esq = a->esq, dir = a->dir;
	free(a);
	return 1 + freeAB(esq) + freeAB(dir);
}



//conta os nodos
int contaNodos(ABin a){
	if (a == NULL) return 0;
	else return 1 + contaNodos(a->esq) + contaNodos(a->dir);
}



//conta as folhas
int contaFolhas(ABin a){
	if (a == NULL) return 0;
	if (a->esq == NULL && a->dir == NULL) return 1;
	return contaFolhas(a->esq) + contaFolhas(a->dir);
}



//verifica se o elemento do input está na árvore
int procurabool(ABin a, int x){
	if (a != NULL){
		if (a->valor == x) return 1;
		else return (procurabool(a->esq, x) || procurabool(a->dir, x));
	}
	return 0;
}



//verifica se o elemento do input está numa BST
int procuraboolbst(ABin a, int x){
	while (a != NULL){
		if (a->valor == x) return 1;
		if (a->valor > x) a = a->esq;
		else a = a->dir;
	}
	return 0;
}



//procura elemento numa árvore
struct nodo *procura(ABin a, int x){
	if (a == NULL) return NULL;
	if (a->valor == x) return a;
    struct nodo *esq = procura(a->esq, x);
    if (esq == NULL) procura(a->dir, x);
    else return esq;
}



//procura elemento numa árvore
struct nodo *procurabst(ABin a, int x){
	while (a != NULL){
		if (a->valor == x) return a;
		if (a->valor > x) a = a->esq;
		else a = a->dir;
	}
	return NULL;
}



//retorna a profundidade (raiz=1, aumenta para baixo) a que se encontra o elem x ou -1 caso não esteja na árvore
int depth(ABin a, int x){
	if (a == NULL) return -1;
	if (x == a->valor) return 1;
	if (depth(a->esq, x) == -1 && depth(a->dir, x) == -1) return -1;
	if (depth(a->esq, x) == -1) return (1 + depth(a->dir, x));
	if (depth(a->dir, x) == -1) return (1 + depth(a->esq, x));
	if (depth(a->dir, x) > depth(a->esq, x)) return (1 + depth(a->esq, x));
	else return (1 + depth(a->dir, x));
}



//retorna a profundidade (raiz=1, aumenta para baixo) a que se encontra o elem x ou -1 caso não esteja na BST
int depthbst(ABin a, int x){
	int nvl=1;
	while (a != NULL){
		if (a->valor == x) return nvl;
		if (a->valor > x) a = a->esq;
		else a = a->dir;
		nvl++;
	}
	return -1;
}



//travessia inorder ESQ->RAIZ->DIR
void inorder(ABin a){
	if (a != NULL){
		inorder(a->esq);
		printf("%d ", a->valor);
		inorder(a->dir);
	}
}



//travessia postorder ESQ->DIR->RAIZ
void postorder(ABin a){
	if (a != NULL){
		postorder(a->esq);
		postorder(a->dir);
		printf("%d ", a->valor);
	}
}



//travessia preorder RAIZ->ESQ->DIR
void preorder(ABin a){
	if (a != NULL){
		printf("%d ", a->valor);
		preorder(a->esq);
		preorder(a->dir);
	}
}



//remove o menor da bst
ABin removemenorbst(ABin *a){
	while (*a != NULL && (*a)->esq != NULL){
		a = &((*a)->esq);
	}
	ABin r = *a;
	*a = (*a)->dir;
	return r;
}



//remove a raiz da bst
void removeraizbst(ABin *a){
	ABin raiz = *a, newraiz;
	if ((*a)->esq == NULL) *a = (*a)->dir;
	else if ((*a)->dir == NULL) *a = (*a)->esq;
	else{
		newraiz = removemenorbst(&((*a)->dir)); 
		newraiz->esq = (*a)->esq;
		newraiz->dir = (*a)->dir;
		*a = newraiz;
		free(raiz);
	}
}



//remove um elemento da bst
int remove(ABin *a, int x){
	while (*a != NULL && (*a)->valor != x){
		if (x < (*a)->valor) a = &((*a)->esq);
		else a = &((*a)->dir);
	} //procurar o elemento na bst
	if (*a == NULL) return -1;
	else removeraizbst(a);
	return 0;
}



//roda bst à esquerda
void rodaEsquerda(ABin *a){
	ABin b = (*a)->dir;
	(*a)->dir = b->esq;
	b->esq = *a;
	*a = b;
}



//roda bst à direita
void rodaDireita(ABin *a){
	ABin b = (*a)->esq;
	(*a)->esq = b->dir;
	b->dir = *a;
	*a = b;
}



//checka se a árvore é balanceada ou não
int isbalanced(ABin a){
	if (a == NULL) return 1;
	else{
		int esq = altura(a->esq);
		int dir = altura(a->dir);
		return (abs(esq - dir) <= 1 && isbalanced(a->esq) && isbalanced(a->dir));
	}
}



//balancear árvore
void balance(ABin *a){
	while (*a != NULL){
		if (isbalanced(*a)) break;
		if (altura((*a)->esq) > altura((*a)->dir)) rodaDireita(a);
		else rodaEsquerda(a);
	}
}