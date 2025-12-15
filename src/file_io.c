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
