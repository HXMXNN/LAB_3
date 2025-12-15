#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    int *data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void queueToArray(Queue *q, int *arr);
int queueSize(Queue *q);
void freeQueue(Queue *q);


#endif
