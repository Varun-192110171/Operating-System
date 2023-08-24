#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int data = 0;
int readers_count = 0;

sem_t mutex;        // For controlling access to shared variables
sem_t data_mutex;   // For protecting data modifications
sem_t read_try;     // For coordinating read access

void *reader(void *arg) {
    int id = *(int *)arg;
    
    sem_wait(&mutex);
    readers_count++;
    if (readers_count == 1) {
        sem_wait(&data_mutex); // First reader locks data access
    }
    sem_post(&mutex);

    sem_wait(&read_try); // Request access to read
    printf("Reader %d read data: %d\n", id, data);
    sem_post(&read_try); // Release read access
    
    sem_wait(&mutex);
    readers_count--;
    if (readers_count == 0) {
        sem_post(&data_mutex); // Last reader unlocks data access
    }
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;
    
    sem_wait(&data_mutex); // Request access to write
    data++;
    printf("Writer %d wrote data: %d\n", id, data);
    sem_post(&data_mutex); // Release write access

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&data_mutex, 0, 1);
    sem_init(&read_try, 0, 1);

    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&data_mutex);
    sem_destroy(&read_try);

    return 0;
}
