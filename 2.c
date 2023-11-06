#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 3

int random_numbers[ARRAY_SIZE];
int divisible_counts[NUM_THREADS] = {0}; // Liczniki podzielnych przez 3, 5, i 7

// Wątek obliczający ile liczb jest podzielnych przez dany dzielnik
void* countDivisibles(void* arg) {
    int thread_id = *((int*)arg);
    int divisor;
    if (thread_id == 0) {
        divisor = 3;
    } else if (thread_id == 1) {
        divisor = 5;
    } else {
        divisor = 7;
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (random_numbers[i] % divisor == 0) {
            divisible_counts[thread_id]++;
        }
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
        pthread_create(&threads[i], NULL, countDivisibles, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        int divisor;
        if (i == 0) {
            divisor = 3;
        } else if (i == 1) {
            divisor = 5;
        } else {
            divisor = 7;
        }
        printf("Liczba liczb podzielnych przez %d: %d\n", divisor, divisible_counts[i]);
    }

    return 0;
}
