#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(&arr[i], &arr[minIdx]);
    }
}

void quickSort(int arr[], int first, int last) {
    if (first >= last) return;

    int pivot = arr[(first + last) / 2];
    int i = first, r = last;

    while (i <= r) {
        while (arr[i] < pivot) i++;
        while (arr[r] > pivot) r--;
        if (i <= r) {
            swap(&arr[i], &arr[r]);
            i++;
            r--;
        }
    }

    if (first < r) quickSort(arr, first, r);
    if (i < last) quickSort(arr, i, last);
}

void compareSorts(int arr[], int n) {
    int *copy1 = (int*)malloc(n * sizeof(int));
    int *copy2 = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        copy1[i] = arr[i];
        copy2[i] = arr[i];
    }

    clock_t start, end;



    start = clock();
    selectionSort(copy1, n);
    end = clock();
    double time_selection = ((double)(end - start)) / CLOCKS_PER_SEC;



    start = clock();
    quickSort(copy2, 0, n - 1);
    end = clock();
    double time_quick = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n=== Сравнение алгоритмов сортировки ===\n");
    printf("Количество элементов: %d\n", n);
    printf("Время сортировки прямым выбором: %.6f сек\n", time_selection);
    printf("Время быстрой сортировки: %.6f сек\n", time_quick);

    if (time_selection > 0) {
        printf("Быстрая сортировка быстрее в %.2f раз\n",
               time_selection / time_quick);
    }

    free(copy1);
    free(copy2);
}