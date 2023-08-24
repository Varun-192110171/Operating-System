#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int itemCount = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Generate a random item
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is full
        while (itemCount == BUFFER_SIZE) {
            pthread_cond_wait(&can_produce, &mutex);
        }

        buffer[itemCount] = item;
        itemCount++;
        printf("Produced item: %d\n", item);

        // Signal consumer threads that an item is available
        pthread_cond_signal(&can_consume);
        pthread_mutex_unlock(&mutex);
        usleep(rand() % 1000000); // Sleep for a short duration
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while (1) {
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is empty
        while (itemCount == 0) {
            pthread_cond_wait(&can_consume, &mutex);
        }

        item = buffer[itemCount - 1];
        itemCount--;
        printf("Consumed item: %d\n", item);

        // Signal producer threads that a slot is available
        pthread_cond_signal(&can_produce);
        pthread_mutex_unlock(&mutex);
        usleep(rand() % 1000000); // Sleep for a short duration
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // Let the simulation run for a while
    usleep(10000000);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_cancel(producers[i]);
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_cancel(consumers[i]);
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
