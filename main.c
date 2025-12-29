#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "list.h"
#include "file_io.h"
#include "sorts.h"

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

ListQueue* getNumbersFromInput() {
    char buffer[100000];

    printf("Введите числа через пробел: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    int only_spaces = 1;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (!isspace((unsigned char)buffer[i])) {
            only_spaces = 0;
            break;
        }
    }

    if (only_spaces) {
        return NULL;
    }

    ListQueue* queue = createListQueue();
    if (!queue) {
        printf("Ошибка создания очереди!\n");
        return NULL;
    }

    char *ptr = buffer;
    int count = 0;
    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) ptr++;

        if (*ptr == '\0') break;

        if (isdigit((unsigned char)*ptr) || (*ptr == '-' && isdigit((unsigned char)*(ptr+1)))) {
            int num = atoi(ptr);
            enqueueList(queue, num);
            count++;

            while (*ptr && !isspace((unsigned char)*ptr)) ptr++;
        } else {
            ptr++;
        }
    }

    if (count == 0) {
        freeListQueue(queue);
        return NULL;
    }

    return queue;
}

void printFirstN(ListQueue* queue, int n) {
    if (!queue || queue->size == 0) {
        printf("пусто\n");
        return;
    }

    Node* current = queue->head;
    int count = 0;
    while (current != NULL && count < n) {
        printf("%d ", current->data);
        current = current->next;
        count++;
    }
    if (queue->size > n) printf("...");
    printf("\n");
}

void processUserInput() {
    ListQueue* queue = getNumbersFromInput();

    if (!queue || queue->size == 0) {
        printf("Не введено ни одного числа!\n");
        if (queue) freeListQueue(queue);
        return;
    }

    printf("\n=== СОЗДАНА ОЧЕРЕДЬ ===\n");
    printf("Количество элементов: %d\n", queue->size);
    printf("Первые 15 элементов: ");
    printFirstN(queue, 15);

    int* arr = listQueueToArray(queue, &(queue->size));
    if (arr) {
        writeArrayToFile(INPUT_FILE, arr, queue->size);
        printf("\n✓ Исходный ряд записан в '%s'\n", INPUT_FILE);
    }

    printf("\n=== СОРТИРОВКА ПРЯМЫМ ВЫБОРОМ ===\n");
    ListQueue* sortedQueue = copyListQueue(queue);
    if (sortedQueue) {
        printf("Сортировка... ");
        fflush(stdout);

        clock_t start = clock();
        selectionSortList(sortedQueue);
        clock_t end = clock();
        double sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("завершена за %.6f сек\n", sort_time);

        int* sortedArr = listQueueToArray(sortedQueue, &(sortedQueue->size));
        if (sortedArr) {
            writeArrayToFile(OUTPUT_FILE, sortedArr, sortedQueue->size);
            printf("✓ Отсортированный ряд записан в '%s'\n", OUTPUT_FILE);

            printf("Отсортированная очередь (первые 15): ");
            printFirstN(sortedQueue, 15);

            free(sortedArr);
        }

        freeListQueue(sortedQueue);
    }

    compareSortingAlgorithms(queue);

    printf("\n=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ СО СПИСКОМ ===\n");

    ListQueue* demoQueue = copyListQueue(queue);
    if (demoQueue) {
        printf("1. Вставка числа 100 на позицию 1\n");
        printf("   До: ");
        printFirstN(demoQueue, 5);
        insertAtPosition(demoQueue, 1, 100);
        printf("   После: ");
        printFirstN(demoQueue, 5);

        printf("2. Удаление элемента на позиции 2\n");
        printf("   До: ");
        printFirstN(demoQueue, 5);
        deleteAtPosition(demoQueue, 2);
        printf("   После: ");
        printFirstN(demoQueue, 5);

        printf("3. Изменение значения на позиции 0 на 999\n");
        printf("   До: ");
        printFirstN(demoQueue, 5);
        updateValueAt(demoQueue, 0, 999);
        printf("   После: ");
        printFirstN(demoQueue, 5);

        freeListQueue(demoQueue);
    }

    if (arr) free(arr);
    freeListQueue(queue);
}

void processFileMode(const char* filename) {
    printf("Чтение файла '%s'...\n", filename);

    int *arr = NULL;
    int n = 0;

    arr = readArrayFromFileDynamic(filename, &n);

    if (!arr || n == 0) {
        printf("Не удалось прочитать файл или файл пуст\n");
        if (arr) free(arr);
        return;
    }

    ListQueue* queue = arrayToListQueue(arr, n);
    free(arr);

    if (!queue) {
        printf("Ошибка создания очереди\n");
        return;
    }

    printf("\n=== ПРОЧИТАНА ОЧЕРЕДЬ ИЗ ФАЙЛА ===\n");
    printf("Количество элементов: %d\n", queue->size);
    printf("Первые 15 элементов: ");
    printFirstN(queue, 15);

    printf("\n=== ПРЕДЫДУЩИЙ ВВЕДЕННЫЙ РЯД ===\n");
    printListQueue(queue);

    ListQueue* sorted = copyListQueue(queue);
    if (sorted) {
        quickSortList(sorted);
        printf("\n=== ОТСОРТИРОВАННЫЙ РЯД ===\n");
        printf("Первые 15 элементов: ");
        printFirstN(sorted, 15);
        freeListQueue(sorted);
    }

    compareSortingAlgorithms(queue);

    freeListQueue(queue);
}

void printMenu() {
    printf("\n=== ЛАБОРАТОРНАЯ РАБОТА №3 ===\n");
    printf("1 - Ввод чисел с клавиатуры\n");
    printf("2 - Выход\n");
    printf("Выберите действие: ");
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        printf("=== РЕЖИМ КОМАНДНОЙ СТРОКИ ===\n");
        processFileMode(argv[2]);
        return 0;
    }

    printf("=== ЛАБОРАТОРНАЯ РАБОТА №3: СОРТИРОВКА СПИСКА ===\n");
    printf("Для работы с файлом: %s --file <имя_файла>\n\n", argv[0]);

    int choice;
    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                processUserInput();
                break;
            case 2:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Выберите 1 или 2.\n");
                break;
        }

        if (choice != 2) {
            printf("\nНажмите Enter для продолжения...");
            while (getchar() != '\n');
        }

    } while (choice != 2);

    printf("Программа завершена.\n");
    return 0;
}