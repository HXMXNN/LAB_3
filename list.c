#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

ListQueue* createListQueue() {
    ListQueue* list = (ListQueue*)malloc(sizeof(ListQueue));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void freeListQueue(ListQueue* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void enqueueList(ListQueue* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = value;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

int dequeueList(ListQueue* list) {
    if (isListQueueEmpty(list)) {
        return -1;
    }

    Node* temp = list->head;
    int value = temp->data;

    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(temp);
    list->size--;
    return value;
}

int peekList(ListQueue* list) {
    if (isListQueueEmpty(list)) {
        return -1;
    }
    return list->head->data;
}

int isListQueueEmpty(ListQueue* list) {
    return list->head == NULL;
}

void insertAtPosition(ListQueue* list, int position, int value) {
    if (position < 0 || position > list->size) {
        printf("Неверная позиция!\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = value;

    if (position == 0) {
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL) {
            list->tail = newNode;
        }
    } else if (position == list->size) {
        enqueueList(list, value);
        return;
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

void deleteAtPosition(ListQueue* list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Неверная позиция!\n");
        return;
    }

    Node* temp;
    if (position == 0) {
        temp = list->head;
        list->head = list->head->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
    } else {
        Node* current = list->head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;

        if (temp == list->tail) {
            list->tail = current;
        }
    }

    free(temp);
    list->size--;
}

void updateValueAt(ListQueue* list, int position, int newValue) {
    if (position < 0 || position >= list->size) {
        printf("Неверная позиция!\n");
        return;
    }

    Node* current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    current->data = newValue;
}

int getValueAt(ListQueue* list, int position) {
    if (position < 0 || position >= list->size) {
        return -1;
    }

    Node* current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    return current->data;
}

void printListQueue(ListQueue* list) {
    if (isListQueueEmpty(list)) {
        printf("Список пуст\n");
        return;
    }

    printf("Список (%d элементов): ", list->size);

    if (list->size > 20) {
        Node* current = list->head;
        printf("Первые 10: ");
        for (int i = 0; i < 10 && current != NULL; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("... ");

        current = list->head;
        for (int i = 0; i < list->size - 10; i++) {
            current = current->next;
        }

        printf("Последние 10: ");
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
    } else {
        Node* current = list->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    printf("\n");
}

int getListQueueSize(ListQueue* list) {
    return list->size;
}

int* listQueueToArray(ListQueue* list, int* size) {
    *size = list->size;
    if (*size == 0) return NULL;

    int* arr = (int*)malloc((*size) * sizeof(int));
    if (!arr) return NULL;

    Node* current = list->head;
    for (int i = 0; i < *size && current != NULL; i++) {
        arr[i] = current->data;
        current = current->next;
    }

    return arr;
}

ListQueue* arrayToListQueue(int* arr, int n) {
    ListQueue* list = createListQueue();
    if (!list) return NULL;

    for (int i = 0; i < n; i++) {
        enqueueList(list, arr[i]);
    }

    return list;
}

ListQueue* copyListQueue(ListQueue* list) {
    if (!list) return NULL;

    ListQueue* copy = createListQueue();
    if (!copy) return NULL;

    Node* current = list->head;
    while (current != NULL) {
        enqueueList(copy, current->data);
        current = current->next;
    }

    return copy;
}

Node** findMinNodeRef(Node** headRef) {
    Node** minRef = headRef;
    int minValue = (*minRef)->data;

    Node** currentRef = &((*headRef)->next);
    while (*currentRef != NULL) {
        if ((*currentRef)->data < minValue) {
            minRef = currentRef;
            minValue = (*currentRef)->data;
        }
        currentRef = &((*currentRef)->next);
    }

    return minRef;
}

void selectionSortList(ListQueue* list) {
    if (list->size < 2) return;

    Node** headRef = &(list->head);
    Node* sorted = NULL;

    while (*headRef != NULL) {
        Node** minRef = findMinNodeRef(headRef);
        Node* minNode = *minRef;

        *minRef = minNode->next;

        minNode->next = sorted;
        sorted = minNode;
    }

    list->head = sorted;

    Node* current = sorted;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    list->tail = current;
}

Node* getTail(Node* head) {
    while (head != NULL && head->next != NULL) {
        head = head->next;
    }
    return head;
}

Node* partitionList(Node* head, Node* end, Node** newHead, Node** newEnd) {
    Node* pivot = end;
    Node* prev = NULL;
    Node* cur = head;
    Node* tail = pivot;

    Node* smallerHead = NULL;
    Node* smallerTail = NULL;
    Node* greaterHead = NULL;
    Node* greaterTail = NULL;

    while (cur != pivot) {
        if (cur->data <= pivot->data) {
            if (smallerHead == NULL) {
                smallerHead = cur;
            } else {
                smallerTail->next = cur;
            }
            smallerTail = cur;
        } else {
            if (greaterHead == NULL) {
                greaterHead = cur;
            } else {
                greaterTail->next = cur;
            }
            greaterTail = cur;
        }
        cur = cur->next;
    }

    if (smallerTail) {
        smallerTail->next = pivot;
    }
    pivot->next = greaterHead;

    if (greaterTail) {
        greaterTail->next = NULL;
    }

    *newHead = (smallerHead != NULL) ? smallerHead : pivot;
    *newEnd = (greaterTail != NULL) ? greaterTail : pivot;

    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) {
        return head;
    }

    Node* newHead = NULL;
    Node* newEnd = NULL;

    Node* pivot = partitionList(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* tmp = newHead;
        while (tmp->next != pivot) {
            tmp = tmp->next;
        }
        tmp->next = NULL;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSortList(ListQueue* list) {
    if (list->size < 2) return;

    list->head = quickSortRecur(list->head, list->tail);

    Node* current = list->head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    list->tail = current;
}