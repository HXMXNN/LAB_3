#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"
#include "list.h"

void compareSortingAlgorithms(ListQueue* list) {
    if (!list || list->size == 0) {
        printf("Список пуст, нечего сортировать\n");
        return;
    }

    printf("\n=== СРАВНЕНИЕ СКОРОСТИ СОРТИРОВОК ===\n");
    printf("Количество элементов: %d\n", list->size);

    ListQueue* copy1 = copyListQueue(list);
    ListQueue* copy2 = copyListQueue(list);

    if (!copy1 || !copy2) {
        printf("Ошибка создания копий списка\n");
        if (copy1) freeListQueue(copy1);
        if (copy2) freeListQueue(copy2);
        return;
    }

    clock_t start, end;
    double time_selection, time_quick;

    start = clock();
    selectionSortList(copy1);
    end = clock();
    time_selection = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    quickSortList(copy2);
    end = clock();
    time_quick = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Время сортировки прямым выбором: %.10f сек\n", time_selection);
    printf("Время быстрой сортировки Хоара:  %.10f сек\n", time_quick);

    if (time_quick > 0) {
        double ratio = time_selection / time_quick;
        printf("Быстрая сортировка быстрее в %.2f раз\n", ratio);
    }

    freeListQueue(copy1);
    freeListQueue(copy2);
}