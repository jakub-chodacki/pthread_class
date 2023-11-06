#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int array1[ARRAY_SIZE] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
int array2[ARRAY_SIZE] = {2, 4, 5, 8, 10, 11, 14, 16, 17, 20};
int array3[ARRAY_SIZE] = {5, 11, 17, 21, 25, 30, 35, 40, 45, 50};

int result1 = -1;  // Indeks w tablicy array1
int result2 = -1;  // Indeks w tablicy array2
int result3 = -1;  // Indeks w tablicy array3

void* findIndex(void* arg) {
    int* array = (int*)arg;
    int* result = malloc(sizeof(int)); // Alokuje pamięć na wynik wątku
    *result = -1;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (array[i] == 5) {  // Wyszukujemy wartość 5 w tablicy
            *result = i;
            break;
        }
    }

    pthread_exit(result);
}

int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, findIndex, (void*)array1);
    pthread_create(&thread2, NULL, findIndex, (void*)array2);
    pthread_create(&thread3, NULL, findIndex, (void*)array3);

    int* result;
    pthread_join(thread1, (void**)&result);
    if (*result != -1) {
        result1 = *result;
    }
    free(result);

    pthread_join(thread2, (void**)&result);
    if (*result != -1) {
        result2 = *result;
    }
    free(result);

    pthread_join(thread3, (void**)&result);
    if (*result != -1) {
        result3 = *result;
    }
    free(result);

    if (result1 != -1 && result2 != -1 && result3 != -1) {
        printf("Wspólna liczba 5 znajduje się na indeksach:\n");
        printf("Tablica 1: %d\n", result1);
        printf("Tablica 2: %d\n", result2);
        printf("Tablica 3: %d\n", result3);
    } else {
        printf("Wspólna liczba nie została znaleziona w co najmniej jednej z tablic.\n");
    }

    return 0;
}
