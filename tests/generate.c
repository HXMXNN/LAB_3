#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    // Различные размеры данных для тестирования
    int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        char filename[50];
        snprintf(filename, sizeof(filename), "test_data_%d.txt", sizes[s]);

        FILE *file = fopen(filename, "w");
        if (!file) {
            perror("Failed to create file");
            continue;
        }

        for (int i = 0; i < sizes[s]; i++) {
            fprintf(file, "%d ", rand() % 1000000);
        }
        fprintf(file, "\n");

        fclose(file);
        printf("Создан файл: %s с %d числами\n", filename, sizes[s]);
    }

    return 0;
}
