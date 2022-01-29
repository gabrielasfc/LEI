#include <stdio.h>
#include <string.h>


////////////////////////////  MIN-HEAPS  ////////////////////////////
//um array crescente é sempre uma min-heap
//uma min-heap NÃO é sempre um array crescente

//1 -- devolve os indices no array
//a
#define ESQ(i) 2*i+1

//b
#define DIR(i) 2*i+2

//c
#define PAI(i) (i-1)/2

//d
#define FOLHA(N) N/2


//2
void swap(int h[], int i, int j){
    int temp = h[i];
    h[i] = h[j];
    h[j] = temp;
}

void bubbleUp(int i, int h[]){
    while(i>0 && h[i] < h[PAI(i)]){
      swap(h, i, PAI(i));
      i = PAI(i);  
    }
}
//Melhor caso : constante
//Pior caso : log N


//3
void bubbleDown(int i, int h[], int N){
    int ind_min = ESQ(i); //guarda o indice do menor entre a esquerda e a direita -- neste caso inicializamos com a esquerda
    while(ind_min <= N-1){
        if (DIR(i) <= N-1 && h[DIR(i)] < h[ind_min]) ind_min = DIR(i); //atualiza o ind_min caso o da direita seja menor
        if (h[i] < h[ind_min]) break; //caso o menor for maior que o pai
        swap(h, i, ind_min);
        i = ind_min;
    }
}
//Melhor caso : constante
//Pior caso: log N


//4
#define MAX 100
typedef struct pQueue{
    int valores[MAX];
    int tamanho;
}PriorityQueue;


void empty(PriorityQueue *q){
    q->tamanho = 0;
}


int isEmpty(PriorityQueue *q){
    return (q->tamanho == 0);
}


int add(int x, PriorityQueue *q){
    if (q->tamanho == MAX) return -1;
    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho, q->valores);
    q->tamanho++;
    return 0; 
}


int remove(PriorityQueue *q, int *rem){
    if (q->tamanho == 0) return -1;
    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho-1];
    q->tamanho--;
    bubbleDown(0, q->valores, q->tamanho);
    return 0;
}


//5
//top-down
void heapify1(int v[], int N){
    for(int i=0; i<N; i++){
        bubbleUp(i, v);
    }
}
/* Complexidade com array ordenado por ordem decrescente:
bubbleUp: log N - 1
heapify : (N-1)*(log N - 1) ---> N . log N
*/

//bottom-up
void heapify2(int v[], int N){
    for(int i=N-1; i>0; i++){
        if(ESQ(i) <= N-1 || DIR(i) <= N-1) //para verificar se o nodo tem sucessores
            bubbleDown(i, v, N);
    }
}
/* Complexidade com array ordenado por ordem decrescente:
bubbleDown: log N - f    (f = nº de folhas)
heapify : (N-1)*(log N - f) ---> N . log N
*/


//6
ordenaHeap(int h[], int N){
    for (int i=N-1; i>0; i--){
        swap(h, 0, i);
        bubbleDown(0, h, i-1);
    }
}



////////////////////////////  HASH TABLES  ////////////////////////////


//http://www.cse.yorku.ca/~oz/hash.html
unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}


////////////  CHAINING (CLOSE ADDRESSING)  ////////////
//Listas ligadas em cada entrada para resolver colisões
//Uma lista para cada índice com keys diferentes em cada nodo
//Inserimos sempre no inicio da lista para facilitar o processo caso a key não esteja na lista

#define SIZE 100
typedef struct nodo{
    char *chave; 
    int ocorr;
    struct nodo *prox;
}Nodo, *THash_CA [SIZE];


//1
void initEmpty_CA(THash_CA t){
    for(int i=0; i<SIZE; i++){
        t[i] = NULL;
    }
}


//2
void add_CA(char *s, THash_CA t){
    int ind = hash(s);
    Nodo *l = t[ind];
    for(; l != NULL && strcmp(s, l->chave) != 0; l = l->prox); //percorre a lista toda para ver se já existe a key
    if(l==NULL){ //caso não tenha encontrado a key
        Nodo *new = malloc(sizeof(struct nodo));
        new->chave = strdup(s);
        new->ocorr = 1;
        new->prox = t[ind];
        t[ind] = new;
    }
    else l->ocorr++;
}


//3
int lookup_CA(char *s, THash_CA t){
    int ind = hash(s);
    Nodo *l = t[ind];
    for(; l != NULL && strcmp(s, l->chave) != 0; l = l->prox);
    if (l==NULL) return 0;
    else return l->ocorr;
}


//4
int remove_CA(char *s, THash_CA t){
    int ind = hash(s);
    Nodo *l = t[ind];
    Nodo *ant = NULL;
    while(l != NULL && strcmp(s, l->chave) != 0){
        ant = l;
        l = l->prox;
    }
    if(l==NULL) return -1;
    else{
        if(l->ocorr==1){
            if(ant==NULL) t[ind] = l->prox; //se estivermos no 1º nodo da lista
            else ant->prox = l->prox;
            free(l->chave); free(l);
        }
        else l->ocorr--;
    }
    return 0;
}


////////////  OPEN ADDRESSING  ////////////
//Resolver colisões:
//Linear probing ->  aumenta o índice até encontrar um índice vazio
//Quadratic probing -> faz a soma dos índices com os quadrados perfeitos até encontrar um índice vazio

//#define SIZE 100
#define FREE 0
#define USED 1
#define DEL 2

typedef struct bucket{
    int status; // Free | Used | Del
    char *chave; 
    int ocorr;
}THash_OA [SIZE];


//1
int where(char *s, THash_OA t){
    int ind = hash(s);
    int check_full=0; //para verificar se a hash está cheia (não podemos usar ind -> inicia com valor possivelmente != 0)
    while(check_full < SIZE && t[ind].status != FREE && t[ind].status != DEL && strcmp(s, t[ind].chave) != 0){
        if(ind == SIZE-1) ind=0;
        else ind++;
        check_full++;
    }
    if(check_full == SIZE) return -1;
    return ind;
}


//2
//a
void initEmpty_OA(THash_OA t){
    for(int i=0; i<SIZE; i++){
        t[i].status = FREE;
        t[i].chave = NULL;
        t[i].ocorr = 0;
    }
}


//b
void add_OA(char *s, THash_OA t){
    int ind = where(s, t);
    if(t[ind].status == USED) t[ind].ocorr++;
    else{
        t[ind].status = USED;
        t[ind].chave = strdup(s);
        t[ind].ocorr = 1;
    }

}


//c
int lookup_OA(char *s, THash_OA t){
    int ind = where(s,t);
    if(t[ind].status == USED) return (t[ind].ocorr);
    else return 0;
}


//d
int remove_OA(char *s, THash_OA t){
    int ind = where(s,t);
    if (t[ind].status != USED) return -1;
    else{
        if(t[ind].ocorr==1){
            t[ind].status = DEL;
            t[ind].ocorr = 0;
            free(t[ind].chave);
        }
        else t[ind].ocorr--;
    }
    return 0;
}


//3
int garb_collection(THash_OA t){
    int i=0;
    int count = 0;
    for(; i<SIZE; i++){
        if(t[i].status == DEL){
            t[i].status = FREE;
            t[i].ocorr = 0;
            free(t[i].chave);
            count++;
        }
    }
    return count;
}