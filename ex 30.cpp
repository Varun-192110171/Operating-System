#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *printMessage(void *message) {
    printf("Thread says: %s\n", (char *)message);
    pthread_exit(NULL);  // Thread exit
}

void *printNumbers(void *arg) {
    int n = *(int *)arg;
    for (int i = 1; i <= n; i++) {
        printf("%d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    int maxNumber = 10;
    const char *message = "Hello, from the new thread!";
    
    pthread_create(&thread1, NULL, printMessage, (void *)message);
    pthread_create(&thread2, NULL, printNumbers, &maxNumber);
    pthread_create(&thread3, NULL, NULL, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    printf("Main thread: All threads have finished.\n");
    
    pthread_t mainThread = pthread_self();
    if (pthread_equal(mainThread, thread3)) {
        printf("Main thread and thread3 are equal.\n");
    } else {
        printf("Main thread and thread3 are not equal.\n");
    }
    
    return 0;
}
