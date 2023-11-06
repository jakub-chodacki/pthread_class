#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 1000

int numbers[MAX_NUMBERS];
double sums[MAX_NUMBERS];

// Struktura do przechowywania danych przekazywanych do wątków
typedef struct {
    int number;
    double sum;
} ThreadData;

// Wątek obliczający sumy liczb naturalnych dla danej liczby
void* calculateSum(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    int number = data->number;
    double sum = 0;

    for (int i = 1; i <= number; i++) {
        sum += i;
    }

    data->sum = sum;
    return NULL;
}

int main() {
    FILE* file = fopen("numbers.txt", "r");
    if (file == NULL) {
        perror("Nie można otworzyć pliku");
        return 1;
    }

    int num_numbers = 0;

    while (fscanf(file, "%d", &numbers[num_numbers]) != EOF) {
        num_numbers++;
    }

    fclose(file);

    pthread_t threads[MAX_NUMBERS];
    ThreadData thread_data[MAX_NUMBERS];

    if (num_numbers > MAX_NUMBERS) {
        fprintf(stderr, "Zbyt wiele liczb w pliku. Maksymalna liczba to %d\n", MAX_NUMBERS);
        return 1;
    }

    for (int i = 0; i < num_numbers; i++) {
        thread_data[i].number = numbers[i];
        pthread_create(&threads[i], NULL, calculateSum, &thread_data[i]);
    }

    for (int i = 0; i < num_numbers; i++) {
        pthread_join(threads[i], NULL);
        sums[i] = thread_data[i].sum;
    }

    printf("Obliczone sumy:\n");
    for (int i = 0; i < num_numbers; i++) {
        printf("%d: %.2lf\n", numbers[i], sums[i]);
    }

    return 0;
}
