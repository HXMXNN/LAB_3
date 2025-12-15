#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* createQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(capacity * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->capacity = capacity;
    return q;
}

void enqueue(Queue *q, int value) {
    if (q->rear == q->capacity - 1) {
        printf("Queue overflow\n");
        return;
    }
    q->data[++(q->rear)] = value;
}

int dequeue(Queue *q) {
    if (q->front > q->rear) {
        printf("Queue underflow\n");
        return -1;
    }
    return q->data[(q->front)++];
}

void queueToArray(Queue *q, int *arr) {
    for (int i = q->front; i <= q->rear; i++) {
        arr[i - q->front] = q->data[i];
    }
}

int queueSize(Queue *q) {
    return q->rear - q->front + 1;
}

void freeQueue(Queue *q) {
    free(q->data);
    free(q);
}