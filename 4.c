#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4

int random_numbers[ARRAY_SIZE];
int min_values[NUM_THREADS]; // Najmniejsze wartości obliczone przez wątki

// Wątek obliczający najmniejszą wartość dla swojego fragmentu tablicy
void* calculateMinValue(void* arg) {
    int thread_id = *((int*)arg);
    int elements_per_thread = ARRAY_SIZE / NUM_THREADS;
    int start_index = thread_id * elements_per_thread;
    int end_index = (thread_id == NUM_THREADS - 1) ? ARRAY_SIZE : start_index + elements_per_thread;

    int min = random_numbers[start_index];
    for (int i = start_index + 1; i < end_index; i++) {
        if (random_numbers[i] < min) {
            min = random_numbers[i];
        }
    }

    min_values[thread_id] = min;

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Wypełnij tablicę losowymi liczbami od 1 do 1000
    for (int i = 0; i < ARRAY_SIZE; i++) {
        random_numbers[i] = rand() % 1000 + 1;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, calculateMinValue, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Znajdź najmniejszą wartość spośród wszystkich częściowych wyników
    int min_value = min_values[0];
    for (int i = 1; i < NUM_THREADS; i++) {
        if (min_values[i] < min_value) {
            min_value = min_values[i];
        }
    }

    printf("Najmniejsza wartość w tablicy: %d\n", min_value);

    return 0;
}
