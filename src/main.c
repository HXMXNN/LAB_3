#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "sorts.h"
#include "file_io.h"
#include <windows.h>

#define MAX_INPUT_SIZE 100000
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void printArray(int arr[], int n) {
    if (n > 20) {
        printf("Первые 10 элементов: ");
        for (int i = 0; i < 10 && i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("... ");
        printf("Последние 10 элементов: ");
        for (int i = n - 10 > 0 ? n - 10 : 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

void processUserInput() {
    int numbers[MAX_INPUT_SIZE];
    int n = 0;

    printf("Введите числа через пробел (для завершения - Enter): ");
    char buffer[100000];

    fgets(buffer, sizeof(buffer), stdin);

    char *token = strtok(buffer, " \t\n");
    while (token != NULL && n < MAX_INPUT_SIZE) {
        numbers[n++] = atoi(token);
        token = strtok(NULL, " \t\n");
    }

    if (n == 0) {
        printf("Не введено ни одного числа!\n");
        return;
    }

    printf("Введено чисел: %d\n", n);


    Queue *q = createQueue(n);
    for (int i = 0; i < n; i++) {
        enqueue(q, numbers[i]);
    }

    writeArrayToFile(INPUT_FILE, numbers, n);
    printf("Исходный массив записан в '%s'\n", INPUT_FILE);
    


    int *arr = (int*)malloc(n * sizeof(int));
    queueToArray(q, arr);

    selectionSort(arr, n);
    writeArrayToFile(OUTPUT_FILE, arr, n);
    printf("Отсортированный массив записан в '%s'\n", OUTPUT_FILE);


    compareSorts(numbers, n);

    free(arr);
    freeQueue(q);
}

int main(int argc, char *argv[]) {

    SetConsoleOutputCP(CP_UTF8);
    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        int arr[MAX_INPUT_SIZE];
        int n = readArrayFromFile(argv[2], arr, MAX_INPUT_SIZE);

        if (n == 0) {
            printf("Не удалось прочитать файл '%s'\n", argv[2]);
            return 1;
        }

        printf("=== Режим чтения из файла ===\n");
        printf("Файл: %s\n", argv[2]);
        printf("Количество элементов: %d\n", n);
        printf("Исходный массив:\n");
        printArray(arr, n);


        int *sorted = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) sorted[i] = arr[i];

        quickSort(sorted, 0, n - 1);
        printf("\nОтсортированный массив (быстрая сортировка):\n");
        printArray(sorted, n);

        free(sorted);
        return 0;
    }


    printf("=== Лабораторная работа №3: Сравнение сортировок ===\n");
    printf("Для работы с файлом используйте: %s --file <имя_файла>\n", argv[0]);
    printf("Для интерактивного режима просто запустите программу\n\n");

    int repeat = 1;
    while (repeat) {
        processUserInput();

        printf("\nПовторить? (1 - да, 0 - нет): ");
        scanf("%d", &repeat);
        getchar(); // Очистка буфера ввода
    }

    printf("Программа завершена. Результаты в файлах '%s' и '%s'\n",
           INPUT_FILE, OUTPUT_FILE);
    return 0;
}
