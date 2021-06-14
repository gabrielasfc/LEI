#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



typedef struct lligada{
	int valor;
	struct lligada *prox;
} *LInt;

//1
int length(LInt l){
	int r=0;
	while (l != NULL){
		r++;
		l = l->prox;
	}
	return r;
}



//2
void freeL(LInt l){
	LInt aux;
	while (l != NULL){
		aux = l->prox;
		free(l);
		l = aux;
	}
}



//3
void imprimeL(LInt l){
	while (l !=NULL){
		printf("%d", l->valor);
		l = l->prox;
	}
}



//4
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



//5
void insertOrd(LInt *l, int x){
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



//6
int removeOneOrd(LInt *l, int x){
	LInt ant = NULL;
	while (*l != NULL && (*l)->valor != x){
		ant = *l;
		l = &((*l)->prox);
	}
	if (*l == NULL) return 1; //se não existir na lista
	if (ant == NULL) *l = (*l)->prox; //remover o elemento do início da lista
	else ant->prox = (*l)->prox;
	return 0;
}



//7
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



//8
void splitQS(LInt l, int x, LInt *mx, LInt *Mx){
	if (l != NULL){
		if (l->valor < x){
			*mx = l;
			*Mx = NULL;
			splitQS(l->prox, x, &((*mx)->prox), &(*Mx));
		}
		else{
			*Mx = l;
			*mx = NULL;
			splitQS(l->prox, x, &(*mx), &((*Mx)->prox));
		}
	}
}



//9
LInt parteAmeio(LInt *l){
    int mid = length(*l)/2;
    if(mid == 0) return NULL;
    LInt y = *l;
    LInt ant = NULL;
    int i;
    for(i=0; i<mid; i++) {
        ant = *l;
        *l = (*l)->prox;
    }
    ant->prox = NULL;
    return y;
}



//10
int removeAll (LInt *l, int x){
	int r=0;
	LInt ant = NULL;
	while (*l != NULL){
		if ((*l)->valor != x){
			ant = *l;
			l = &((*l)->prox);
		}
		else{
			if (ant == NULL) *l = (*l)->prox;
			else ant->prox = (*l)->prox;
			r++;
		}
	}
	return r;
}



//11
int removeDups(LInt *l){
    int dups = 0;
    while(*l != NULL){
    	int removidos = removeAll(&((*l)->prox),(*l)->valor);
        dups = dups + removidos;
        l = &((*l)->prox);
    }
    return dups;
}



//12
int removeMaiorL(LInt *l){
	int maxvalue = (*l)->valor;
	LInt aux = *l;
	LInt max = *l, antmax = NULL;
	LInt ant = NULL;
	while (aux != NULL){
		if (aux->valor > maxvalue){
			antmax = ant;
			max = aux;
			maxvalue = aux->valor;
		}
		ant = aux;
		aux = aux->prox;
	}
	if (antmax == NULL) *l = (*l)->prox; //se o máximo estiver no início
	else antmax->prox = max->prox;
	return maxvalue;
}
	


//13
void init(LInt *l){
	while ((*l)->prox != NULL){
		l = &((*l)->prox);
	}
	free(*l);
	*l = NULL;
}



//14
void appendL(LInt *l, int x){
	LInt new = malloc(sizeof(struct lligada));
	new->valor = x;
	new->prox = NULL;
	while (*l != NULL){
		l = &((*l)->prox);
	}
	*l = new;
}



//15
void concatL(LInt *a, LInt b){
	while (*a != NULL){
		a = &((*a)->prox);
	}
	*a = b;
}



//16
LInt cloneL(LInt l){
	if (l==NULL) return NULL;
	LInt new = malloc(sizeof(struct lligada));
	new->valor = l->valor;
	new->prox = cloneL(l->prox);
	return new;
}



//17
LInt cloneRev(LInt l) {
    LInt ant = NULL;
    while (l != NULL) {
        LInt new = malloc(sizeof(struct lligada));
        new->valor = l->valor;
        new->prox = ant;
        ant = new;
        l = l->prox;
    }
    return ant;
} 



//18
int maximo(LInt l){
	int max = 0;
	while (l != NULL){
		if (l->valor > max) max=l->valor;
		l = l->prox;
	}
	return max;
}



//19
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



//20
int drop(int n, LInt *l){
	int i;
	for (i=0; *l != NULL && i<n; i++){
		LInt aux = (*l)->prox;
		free(*l);
		*l = aux;
	}
	return i;
}



//21
LInt Nforward(LInt l, int N){
	int i;
	for (i=0; i<N; i++){
		l = l->prox;
	}
	return l;
}



//22
int listToArray(LInt l, int v[], int N){
	int i;
	for (i=0; i<N && l!=NULL; i++){
		v[i] = l->valor;
		l = l->prox;
	}
	return i;
}



//23
LInt arrayToList(int v[], int N){
	if (N==0) return NULL;
	LInt new = malloc(sizeof(struct lligada));
	new->valor = *v;
	new->prox = arrayToList(v+1, N-1);
	return new;
}



//24
LInt somasAcL(LInt l){
	int soma=0;
	LInt lsomas = NULL, aux = NULL;
	while (l != NULL){
		soma = soma + l->valor;
		LInt new = malloc(sizeof(struct lligada));
		new->valor = soma;
		new->prox = NULL;
		if (lsomas == NULL) lsomas = aux = new;
		else aux = aux->prox = new; //no fim terá um nodo a mais que é a soma de todos(aux->prox)
		l = l->prox;
	}
	return lsomas;
}



//25
void remreps(LInt l){
	LInt next;
	while (l != NULL && l->prox != NULL){
		if (l->valor == (l->prox)->valor){
			LInt aux = l->prox;
			l->prox = l->prox->prox;
			free(aux);
		}
		else l = l->prox;
	}
}



//26
LInt rotateL(LInt l){
	if (l == NULL || l->prox == NULL) return l;
	LInt elem = l, newfst = l->prox;
	while (l->prox != NULL){
		l = l->prox;
	}
	l->prox = elem;
	elem->prox = NULL;
	return newfst;
}



//27
LInt parte(LInt l){
    if (l == NULL || l->prox == NULL) return NULL;
    LInt new = l->prox;
    l->prox = (l->prox)->prox;
    new->prox = parte(l->prox);
    return new;
}



//ÁRVORES

typedef struct nodo{
	int valor;
	struct nodo *esq, *dir;
} *ABin;


//28
int altura(ABin a){
	int r=0;
	if (a != NULL){
		if (altura(a->dir) > altura(a->esq))
			r = 1 + altura(a->dir);
		else r = 1 + altura(a->esq);
	}
	return r;
}



//29
ABin cloneAB(ABin a){
	ABin clone = NULL;
	if (a != NULL){
		clone = malloc(sizeof(struct nodo));
		clone->valor = a->valor;
		clone->esq = cloneAB(a->esq);
		clone->dir = cloneAB(a->dir);
	}
	return clone;
}



//30
void mirror(ABin *a){
	if (*a != NULL){
		ABin aux = (*a)->esq;
		(*a)->esq = (*a)->dir;
		(*a)->dir = aux;
		mirror(&((*a)->esq));
		mirror(&((*a)->dir));
	}
}



//31 ESQ->RAIZ->DIR
void inorder(ABin a, LInt *l){
	if (a == NULL) *l = NULL;
	else{
		inorder(a->esq, l);
        while (*l != NULL) {
            l = &((*l)->prox);
        }
        *l = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        l = &((*l)->prox);
        inorder(a->dir, l);
	}
}



//32 RAIZ->ESQ->DIR
void preorder(ABin a, LInt *l){
	if (a == NULL) *l = NULL;
	else{
		*l = malloc(sizeof(struct lligada));
		(*l)->valor = a->valor;
		l = &((*l)->prox);
		preorder(a->esq, l);
		while (*l != NULL){
			l = &((*l)->prox);
		}
		preorder(a->dir, l);
	}
}



//33 ESQ->DIR->RAIZ
void posorder(ABin a, LInt *l){
	if (a == NULL) *l = NULL;
	else{
		posorder(a->esq, l);
		while (*l != NULL){
			l = &((*l)->prox);
		}
		posorder(a->dir, l);
		while (*l != NULL){
			l = &((*l)->prox);
		}
		*l = malloc(sizeof(struct lligada));
		(*l)->valor = a->valor;
		(*l)->prox = NULL;
	}
}



//34
int depth(ABin a, int x){
	if (a == NULL) return -1;
	if (x == a->valor) return 1;
	if (depth(a->esq, x) == -1 && depth(a->dir, x) == -1) return -1;
	if (depth(a->esq, x) == -1) return (1 + depth(a->dir, x));
	if (depth(a->dir, x) == -1) return (1 + depth(a->esq, x));
	if (depth(a->dir, x) > depth(a->esq, x)) return (1 + depth(a->esq, x));
	else return (1 + depth(a->dir, x));
}



//35
int freeAB(ABin a){
	if (a == NULL) return 0;
	else{
		ABin esq = a->esq;
		ABin dir = a->dir;
		free(a);
		return (1 + freeAB(esq) + freeAB(dir));
	}
}



//36
int pruneAB(ABin *a, int l){
	if (*a == NULL) return 0;
	if (l == 0){
		int r = 1 + pruneAB(&((*a)->esq), 0) + pruneAB(&((*a)->dir), 0);
		free(*a);
		*a = NULL;
		return r;
	}
	else{
		return (pruneAB(&((*a)->esq), l-1) + pruneAB(&((*a)->dir), l-1));
	}
}



//37
int iguaisAB(ABin a, ABin b){
	if (a == NULL && b == NULL) return 1;
	if (a != NULL && b == NULL || a == NULL && b != NULL) return 0;
	if (a->valor != b->valor) return 0;
	else return iguaisAB(a->esq, b->esq) && iguaisAB(a->dir, b->dir);
}



//38
LInt nivelL(ABin a, int n){
    LInt b, r = NULL;
    if (a != NULL){
        if (n==1){
            r = malloc(sizeof(struct lligada));
            r->valor = a->valor;
            r->prox = NULL;
        }
        else{
            r = b = nivelL(a->esq, n-1);
            while (b != NULL && b->prox != NULL) {
            	b = b->prox;
            }
            if (b != NULL) b->prox = nivelL(a->dir,n-1);
            else r = nivelL(a->dir,n-1);
        }
    }
    return r;
}



//39
int nivelV(ABin a, int n, int v[]){
	int i=0;
	if (a != NULL){
		if (n==1){
			v[i] = a->valor;
			i++;
		}
		else{
			i = i + nivelV(a->esq, n-1, v);
			i = i + nivelV(a->dir, n-1, v+i);
		}
	}
	return i;
}



//40
int dumpAbin(ABin a, int v[], int N){
	int i=0;
	if (a != NULL && N>0){
		i = dumpAbin(a->esq, v, N-1);
		*(v+i) = a->valor;
		i = i + 1 + dumpAbin(a->dir, v+i+1, N-i-1);
	}
	return i;
}



//41
int soma(ABin a){
	if (a==NULL) return 0;
	return (a->valor + soma(a->esq) + soma(a->dir));
}

ABin somasAcA(ABin a){
	ABin new = NULL;
	if (a != NULL){
		new = malloc(sizeof(struct nodo));
		new->valor = soma(a);
		new->esq = somasAcA(a->esq);
		new->dir = somasAcA(a->dir);
	}
	return new;
}



//42
int contaFolhas(ABin a){
	if (a==NULL) return 0;
	if (a->esq == NULL && a->dir == NULL) return 1;
	return (contaFolhas(a->esq) + contaFolhas(a->dir));
}



//43
ABin cloneMirror(ABin a){
	ABin new = NULL;
	if (a != NULL){
		new = malloc(sizeof(struct nodo));
		new->valor = a->valor;
		new->esq = cloneMirror(a->dir);
		new->dir = cloneMirror(a->esq);
	}
	return new;
}



//44
int addOrd(ABin *a, int x){
	while (*a != NULL){
		if (x == (*a)->valor) return 1;
		if (x < (*a)->valor) a = &((*a)->esq);
		else a = &((*a)->dir);
	}
	ABin new = malloc(sizeof(struct nodo));
	new->valor = x;
	new->esq = new->dir = NULL;
	*a = new;
	return 0;
}



//45
int lookupAB(ABin a, int x){
	while (a != NULL){
		if (x == a->valor) return 1;
		if (x > a->valor) a = a->dir;
		else a = a->esq;
	}
	return 0;
}



//46
int depthOrd(ABin a, int x){
	int nvl;
	if (a != NULL){
		for (nvl=1; a != NULL; nvl++){
			if (a->valor == x) return nvl;
			if (a->valor > x) a = a->esq;
			else a = a->dir;
		}
	}
	return -1;
}



//47
int maiorAB(ABin a){
	while (a->dir != NULL){
		a = a->dir;
	}
	return a->valor;
}



//48
void removeMaiorA (ABin *a){
	if ((*a)->dir == NULL){
		ABin aux = (*a)->esq;
		free(*a);
		*a = aux;
	}
	else removeMaiorA(&((*a)->dir));
}



//49
int quantosMaiores(ABin a, int x){
	int conta=0;
	if (a==NULL) return conta;
	if (a->valor > x) conta++;
	return conta + quantosMaiores(a->esq, x) + quantosMaiores(a->dir, x);
}



//50
void listToBTree(LInt l, ABin *a){

}



//51
int maximo(ABin a){
	while (a->dir != NULL){
		a = a->dir;
	}
	return a->valor;
}

int minimo(ABin a){
	while (a->esq != NULL){
		a = a->esq;
	}
	return a->valor;
}

int deProcura(ABin a){
	if (a==NULL) return 1;
	if (a->esq != NULL && maximo(a->esq) > a->valor) return 0;
	if (a->dir != NULL && minimo(a->dir) < a->valor) return 0;
	if (!deProcura(a->esq) || !deProcura(a->dir)) return 0;
}