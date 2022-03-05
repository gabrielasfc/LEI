//Codeboard: https://codeboard.io/projects/240896

#include <stdio.h>
#include <stdlib.h>

typedef struct slist{
    int valor;
    struct slist *prox;
} *LInt;

typedef LInt Stack;

typedef struct{
    LInt inicio, fim;
} Queue;


//1
//STACKS
void initStack(Stack *s){
    *s = NULL;
}

int SisEmpty(Stack s){
    return (s == NULL);
}

int push(Stack *s, int x){
    Stack new = malloc(sizeof(struct slist));
    if (new != NULL){
        new->valor = x;
        new->prox = *s;
        *s = new;
    }
    else return -1;
    return 0;
}

int pop(Stack *s, int *x){
    Stack aux;
    if (SisEmpty(*s) == 0){
        *x = (*s)->valor;
        aux = *s;
        *s = (*s)->prox;
        free(aux);
    }
    else return -1;
    return 0;
}

int top(Stack s, int *x){
    if (SisEmpty(s) == 0) *x = s->valor;
    else return -1;
    return 0;
}


//2
//QUEUES
void initQueue(Queue *q){
	q->inicio = NULL;
	q->fim = NULL;
}

int QisEmpty(Queue q){
	return (q.inicio == NULL);
}

int enqueue(Queue *q, int x){
	LInt new = malloc(sizeof(struct slist));
	if (new == NULL) return -1;
	else{
		new->valor = x;
	    new->prox = NULL;
		if (q->inicio == NULL){
			q->inicio = new;
			q->fim = new;
		}
		else{
			q->fim->prox = new;
			q->fim = new;
		}
	}
	return 0;
}

int dequeue(Queue *q, int *x){
	LInt aux;
	if (q->inicio == NULL) return -1;
	else{
		*x = q->inicio->valor;
	    aux = q->inicio;
		if (q->inicio == q->fim) //se a queue só tiver 1 elemento
			q->inicio = q->fim = NULL;
		else q->inicio = q->inicio->prox;
		free(aux);
	}
	return 0;
}

int front(Queue q, int *x){
    if (QisEmpty(q)) return -1;
    else *x = q.inicio->valor;
    return 0;
}


//3
//QUEUES CIRCULARES
typedef LInt QueueC;

int enqueueC(QueueC *q, int x){
	LInt new  = malloc(sizeof(struct slist));
    if (new == NULL) return -1;
	new->valor = x; 
	if (*q == NULL){
		new->prox = new;
		*q = new;
	}
	else{
		new->prox = (*q)->prox;
		(*q)->prox = new;
		*q = new;
	}
	return 0;
}


int dequeueC(QueueC *q, int *x){
	LInt aux;
	if (*q == NULL) return -1;
	else{
		*x = (*q)->prox->valor;
		aux = (*q)->prox;
		if ((*q)->prox == *q) *q = NULL;
		else (*q)->prox = (*q)->prox->prox;
		free(aux);
	}
	return 0;
}


//4
//DOUBLE ENDED QUEUES
typedef struct dlist{
	int valor;
	struct dlist *ant, *prox;
} *DList;

typedef struct{
	DList back, front;
} Deque;


int initDeque(Deque *q){
	q->back = q->front = NULL;
}

int DisEmpty(Deque q){
	return (q->front == NULL);
}

int pushBack(Deque *q, int x){
	DList new = malloc(sizeof(struct dlist));
	if (new == NULL) return -1;
	else{
		new->valor = x;
		new->ant = NULL;
		new->prox = q->back;
		if (q->back == NULL){ //se for vazia
			q->front = new;
		}
		else{
			q->back->ant = new;
		}
		q->back = new;
	}
	return 0;
}