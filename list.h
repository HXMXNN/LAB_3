#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} ListQueue;

ListQueue* createListQueue();
void freeListQueue(ListQueue* list);

void enqueueList(ListQueue* list, int value);
int dequeueList(ListQueue* list);
int peekList(ListQueue* list);
int isListQueueEmpty(ListQueue* list);

void insertAtPosition(ListQueue* list, int position, int value);
void deleteAtPosition(ListQueue* list, int position);
void updateValueAt(ListQueue* list, int position, int newValue);
int getValueAt(ListQueue* list, int position);

void selectionSortList(ListQueue* list);
void quickSortList(ListQueue* list);

void printListQueue(ListQueue* list);
int getListQueueSize(ListQueue* list);
int* listQueueToArray(ListQueue* list, int* size);
ListQueue* arrayToListQueue(int* arr, int n);
ListQueue* copyListQueue(ListQueue* list);

#endif