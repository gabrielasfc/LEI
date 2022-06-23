#ifndef QUEUE_
#define QUEUE_

#include "request.h"

typedef struct pQueue{
    Request* requests;
    int capacity;
    int size;
}*PriorityQueue;


PriorityQueue initQueue();

int isEmpty(PriorityQueue queue);

int enqueue(PriorityQueue queue, Request r);

Request dequeue(PriorityQueue queue);

void printQueue(PriorityQueue queue);

#endif