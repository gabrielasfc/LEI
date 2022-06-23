#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"

#define LEFT(i) 2*i+1
#define RIGHT(i) 2*i+2
#define PARENT(i) (i-1)/2
#define LEAF(N) N/2

PriorityQueue initQueue(){
    PriorityQueue queue = malloc(sizeof(struct pQueue));   
    
    queue->size = 0;
    queue->capacity = 1000 * sizeof(struct request);
    queue->requests = malloc(queue->capacity*sizeof(struct request));

    for(int i = 0; i<queue->capacity; i++) queue->requests[i] = NULL;

    return queue;
}

void swap(Request* requests, int i, int j){
    Request temp = requests[i];

    requests[i] = requests[j];
    requests[j] = temp;
}

void bubbleUp(Request* requests, int i){
    while(i>0 && (requests[i]->priority) > requests[PARENT(i)]->priority){
        swap(requests, i, PARENT(i));
        i = PARENT(i);
    }
}


void bubbleDown (Request* requests, int N) {
    int i=0, maior;
    while (LEFT(i) < N){
        maior = LEFT(i);
        if (RIGHT(i) < N && requests[RIGHT(i)]->priority > requests[maior]->priority){
            maior = RIGHT(i);
        }
        if (requests[maior]->priority < requests[i]->priority){ 
           break; 
        }
        swap(requests, i, maior);
        i = maior;
    }
}




int enqueue(PriorityQueue queue, Request r){
    if(queue->size >= queue->capacity){ 
        queue->capacity *= 2;
        queue->requests = realloc(queue->requests, queue->capacity*sizeof(struct request));

        return -1;
    }
    
    queue->requests[queue->size] = r;
    bubbleUp(queue->requests, queue->size);
    queue->size++;

    return 0;
}


Request dequeue(PriorityQueue queue){
    if(queue->size == 0) return NULL;

    Request ret = queue->requests[0];
    
    queue->size--;

    swap(queue->requests, 0, queue->size);
    
    bubbleDown(queue->requests, queue->size);

    return ret;
}


int isEmpty(PriorityQueue queue){
    return queue->size == 0;
}

void printQueue(PriorityQueue queue){
    for(int i=0; i<queue->size; i++){
        printf("%d\n\n", i);
        print_request(queue->requests[i]);
    }
}