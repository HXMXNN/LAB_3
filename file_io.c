#include <stdio.h>
#include <stdlib.h>
#include "file_io.h"

void writeArrayToFile(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

int readArrayFromFile(const char *filename, int arr[], int max_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return 0;
    }

    int n = 0;
    while (n < max_size && fscanf(file, "%d", &arr[n]) == 1) {
        n++;
    }

    fclose(file);
    return n;
}

int* readArrayFromFileDynamic(const char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        *size = 0;
        return NULL;
    }

    int capacity = 100;
    int *temp = (int*)malloc(capacity * sizeof(int));
    if (!temp) {
        fclose(file);
        *size = 0;
        return NULL;
    }

    int count = 0;

    while (fscanf(file, "%d", &temp[count]) == 1) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            int *new_temp = (int*)realloc(temp, capacity * sizeof(int));
            if (!new_temp) {
                free(temp);
                fclose(file);
                *size = 0;
                return NULL;
            }
            temp = new_temp;
        }
    }

    fclose(file);

    if (count == 0) {
        free(temp);
        *size = 0;
        return NULL;
    }

    int *result = (int*)malloc(count * sizeof(int));
    if (!result) {
        free(temp);
        *size = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        result[i] = temp[i];
    }

    free(temp);
    *size = count;
    return result;
}