#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4

int random_numbers[ARRAY_SIZE];
int partial_sums[NUM_THREADS] = {0}; // Częściowe sumy obliczone przez wątki

// Wątek obliczający sumę częściową dla swojego fragmentu tablicy
void* calculatePartialSum(void* arg) {
    int thread_id = *((int*)arg);
    int elements_per_thread = ARRAY_SIZE / NUM_THREADS;
    int start_index = thread_id * elements_per_thread;
    int end_index = (thread_id == NUM_THREADS - 1) ? ARRAY_SIZE : start_index + elements_per_thread;

    for (int i = start_index; i < end_index; i++) {
        partial_sums[thread_id] += random_numbers[i];
    }

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
        pthread_create(&threads[i], NULL, calculatePartialSum, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Oblicz sumę całkowitą na podstawie częściowych sum
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        total_sum += partial_sums[i];
    }

    printf("Suma wszystkich liczb w tablicy: %d\n", total_sum);

    return 0;
}
