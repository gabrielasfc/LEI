//Codeboard: https://codeboard.io/projects/155512

#include <stdio.h>
#include <stdlib.h>

#define Max 10

//1
//STATIC STACKS
typedef struct staticStack{
    int sp;
    int values[Max];
} STACK, *SStack;

//a
void SinitStack(SStack s){
	s->sp = 0;
}

//b
int SisEmpty(SStack s){
	return (s->sp == 0);
}

//c
int Spush(SStack s, int x){
	if (s->sp == Max) return 1;
	else{
		s->values[s->sp] = x;
		s->sp++;
	}
	return 0;
}

//d
int Spop(SStack s, int *x){
	if (s->sp == 0) return 1;
	else{
		s->sp--;
		*x = s->values[s->sp];
	}
	return 0;
}

//e
int Stop(SStack s, int *x){
    if (SisEmpty(s) == 0){
        *x = s->values[s->sp-1];
        return 0;
    }
	return 1;
}


//2
//STATIC QUEUES
typedef struct staticQueue{
    int front;
    int length;
    int values [Max];
} QUEUE, *SQueue;

//a
void SinitQueue(SQueue q){
    q->length = 0;
    q->front = 0;
}

//b
int SisEmptyQ(SQueue q){
    return (q->length == 0);
}

//c
int Senqueue(SQueue q, int x){
    if (q->length == Max) return 1;
    else{
        q->values[(q->front + q->length) % Max] = x;
        q->length++;
    }
    return 0;
}

//d
int Sdequeue(SQueue q, int *x){
    if (SisEmptyQ(q) == 0){
        *x = q->values[q->front];
        q->front++;
        q->length--;
        q->front = q->front % Max;
    }
    else return 1;
	return 0;
}

//e
int Sfront(SQueue q, int *x){
    if (SisEmptyQ(q) == 0){
        *x = q->values[q->front];
        q->front++;
    }
    else return 1;
	return 0;
}


//3
typedef struct dinStack{
    int size; // guarda o tamanho do array values
    int sp;
    int *values;
} *DStack;

typedef struct dinQueue{
    int size; // guarda o tamanho do array values
    int front;
    int length;
    int *values;
} *DQueue;


//DYNAMIC STACKS
//a
void DinitStack(DStack s){
    s->size = Max;
	s->sp = 0;
	s->values = malloc(s->size * sizeof(int));
}

//b
int DisEmpty(DStack s){
    return (s->sp == 0);
}

//c
int Dpush(DStack s, int x){
	if (s->sp == s->size){
		s->values = realloc(s->values, 2*s->size);
		s->size *= 2;
    }
    s->values[s->sp] = x;
    s->sp++;
    return 0;
}

//d
int Dpop(DStack s, int *x){
	if (DisEmpty(s)) return 1;
	else{
		*x = s->values[s->sp-1];
        s->sp--;
	}
	return 0;
}

//e
int Dtop(DStack s, int *x){
	if (DisEmpty(s)) return 1;
	else *x = s->values[s->sp-1];
	return 0;
}



//DYNAMIC QUEUES
//a
void DinitQueue(DQueue q){
    q->size = Max;
	q->front = 0;
    q->length = 0;
    q->values = malloc(sizeof(int) * q->size);
}

//b
int DisEmptyQ(DQueue s){
	return (s->length == 0);
}

//c
int Denqueue(DQueue q, int x){
    if (q->length == q->size){
		q->values = realloc(q->values, 2*q->size);
		q->size *= 2;
    }
    q->values[(q->front + q->length) % Max] = x;
    q->size++;
    return 0;
}

//d
int Ddequeue(DQueue q, int *x){
    if (DisEmptyQ(q) == 0){
        *x = q->values[q->front];
        q->front++;
        q->length--;
        q->front = q->front % Max;
    }
    else return 1;
	return 0;
}

//e
int Dfront(DQueue q, int *x){
    if (DisEmpty(q)) return 1;
    else *x = q->values[q->front];
    return 0;
}