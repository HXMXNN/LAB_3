#include <stdio.h>
#include <stdlib.h>

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
}