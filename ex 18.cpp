#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;   // Semaphore to track empty slots in the buffer
sem_t full;    // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex; // Mutex to protect access to the buffer

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        int item = rand() % 100; // Generate a random item
        
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        buffer[in] = item;
        printf("Produced item: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that a slot is filled
        
        sleep(rand() % 2); // Simulate varying production time
    }
    
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; ++i) {
        sem_wait(&full); // Wait for a filled slot
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        int item = buffer[out];
        printf("Consumed item: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that a slot is emptied
        
        sleep(rand() % 2); // Simulate varying consumption time
    }
    
    return NULL;
}

int main() {
    srand(time(NULL));

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
