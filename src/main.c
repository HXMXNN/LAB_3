#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"
#include "sorts.h"
#include "file_io.h"
#include <windows.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void printArray(int *arr, int n) {
    if (n == 0) {
        printf("Массив пуст\n");
        return;
    }

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
        printf("Элементы массива: ");
        
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int* getNumbersFromInput(int *count) {
    char buffer[100000];
    int *numbers = NULL;
    *count = 0;
    int capacity = 10;

    printf("Введите числа через пробел (для завершения - Enter): ");
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

    numbers = (int*)malloc(capacity * sizeof(int));
    if (!numbers) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }

    char *ptr = buffer;
    while (*ptr) {
        while (*ptr && isspace((unsigned char)*ptr)) ptr++;

        if (*ptr == '\0') break;

        if (isdigit((unsigned char)*ptr) || (*ptr == '-' && isdigit((unsigned char)*(ptr+1)))) {
            int num = atoi(ptr);

            if (*count >= capacity) {
                capacity *= 2;
                int *temp = (int*)realloc(numbers, capacity * sizeof(int));
                if (!temp) {
                    printf("Ошибка перераспределения памяти!\n");
                    free(numbers);
                    return NULL;
                }
                numbers = temp;
            }

            numbers[*count] = num;
            (*count)++;

            while (*ptr && !isspace((unsigned char)*ptr)) ptr++;
        } else {
            ptr++;
        }
    }

    if (*count == 0) {
        free(numbers);
        return NULL;
    }

    if (*count < capacity) {
        int *temp = (int*)realloc(numbers, *count * sizeof(int));
        if (temp) {
            numbers = temp;
        }
    }

    return numbers;
}

void processUserInput() {
    int *numbers = NULL;
    int n = 0;
    Queue *q = NULL;
    int *arr = NULL;

    numbers = getNumbersFromInput(&n);
    if (!numbers || n == 0) {
        printf("Не введено ни одного числа!\n");
        if (numbers) free(numbers);
        return;
    }

    printf("Введено чисел: %d\n", n);
    printf("Исходный массив:\n");
    printArray(numbers, n);

    q = createQueue(n);
    if (!q) {
        printf("Ошибка создания очереди!\n");
        free(numbers);
        return;
    }

    for (int i = 0; i < n; i++) {
        enqueue(q, numbers[i]);
    }

    writeArrayToFile(INPUT_FILE, numbers, n);
    printf("Исходный массив записан в '%s'\n", INPUT_FILE);

    arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("Ошибка выделения памяти для сортировки!\n");
        free(numbers);
        freeQueue(q);
        return;
    }

    queueToArray(q, arr);

    selectionSort(arr, n);
    writeArrayToFile(OUTPUT_FILE, arr, n);
    printf("Отсортированный массив записан в '%s'\n", OUTPUT_FILE);
    printf("Отсортированный массив:\n");
    printArray(arr, n);

    compareSorts(numbers, n);

    free(arr);
    free(numbers);
    freeQueue(q);
}

void processFileMode() {
    char filename[256];

    printf("Введите имя файла: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Ошибка чтения имени файла!\n");
        return;
    }

    filename[strcspn(filename, "\n")] = 0;

    if (strlen(filename) == 0) {
        printf("Имя файла не может быть пустым!\n");
        return;
    }

    int *arr = NULL;
    int n = 0;

    printf("Чтение файла '%s'...\n", filename);
    arr = readArrayFromFileDynamic(filename, &n);

    if (!arr || n == 0) {
        printf("Не удалось прочитать файл '%s' или файл пуст\n", filename);
        if (arr) free(arr);
        return;
    }

    printf("=== Режим чтения из файла ===\n");
    printf("Файл: %s\n", filename);
    printf("Количество элементов: %d\n", n);
    printf("Исходный массив:\n");
    printArray(arr, n);

    int *sorted = (int*)malloc(n * sizeof(int));
    if (!sorted) {
        printf("Ошибка выделения памяти!\n");
        free(arr);
        return;
    }

    for (int i = 0; i < n; i++) sorted[i] = arr[i];

    quickSort(sorted, 0, n - 1);
    printf("\nОтсортированный массив (быстрая сортировка):\n");
    printArray(sorted, n);

    writeArrayToFile("sorted_from_file.txt", sorted, n);
    printf("Результат записан в 'sorted_from_file.txt'\n");

    compareSorts(arr, n);

    free(sorted);
    free(arr);
}

void printMenu() {
    printf("\n=== МЕНЮ ===\n");
    printf("1 - Ввод чисел с клавиатуры\n");
    printf("2 - Чтение из файла\n");
    printf("3 - Выход\n");
    printf("Выберите действие: ");
}

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        int *arr = NULL;
        int n = 0;

        printf("=== Запуск через аргументы командной строки ===\n");
        printf("Чтение файла: %s\n", argv[2]);

        arr = readArrayFromFileDynamic(argv[2], &n);

        if (!arr || n == 0) {
            printf("Не удалось прочитать файл '%s' или файл пуст\n", argv[2]);
            if (arr) free(arr);
            return 1;
        }

        printf("Количество элементов: %d\n", n);
        printf("Исходный массив:\n");
        printArray(arr, n);

        int *sorted = (int*)malloc(n * sizeof(int));
        if (!sorted) {
            printf("Ошибка выделения памяти!\n");
            free(arr);
            return 1;
        }

        for (int i = 0; i < n; i++) sorted[i] = arr[i];

        quickSort(sorted, 0, n - 1);
        printf("\nОтсортированный массив (быстрая сортировка):\n");
        printArray(sorted, n);

        writeArrayToFile("output_command_line.txt", sorted, n);
        printf("Результат записан в 'output_command_line.txt'\n");

        compareSorts(arr, n);

        free(sorted);
        free(arr);
        return 0;
    }

    printf("=== Лабораторная работа №3: Сравнение сортировок ===\n");
    printf("Для быстрого запуска с файлом используйте: %s --file <имя_файла>\n", argv[0]);

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
                printf("\n=== Режим ввода с клавиатуры ===\n");
                processUserInput();
                break;
            case 2:
                printf("\n=== Режим чтения из файла ===\n");
                processFileMode();
                break;
            case 3:
                printf("Выход из программы...\n");
                break;
            default:
                printf("Неверный выбор! Пожалуйста, выберите 1, 2 или 3.\n");
                break;
        }

        if (choice != 3) {
            printf("\nНажмите Enter для продолжения...");
            while (getchar() != '\n');
        }

    } while (choice != 3);

    printf("Программа завершена.\n");
    return 0;
}