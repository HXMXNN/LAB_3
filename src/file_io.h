#ifndef FILE_IO_H
#define FILE_IO_H

void writeArrayToFile(const char *filename, int arr[], int n);
int readArrayFromFile(const char *filename, int arr[], int max_size);
int* readArrayFromFileDynamic(const char *filename, int *size);

#endif