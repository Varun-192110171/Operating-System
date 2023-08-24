#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    int shmid;
    char *shmaddr;

    // Create a shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Attach the shared memory segment to the process
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    // Write data into shared memory
    sprintf(shmaddr, "Hello, shared memory!");

    // Detach the shared memory segment from the process
    shmdt(shmaddr);

    // Re-attach the shared memory segment to read data
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    // Read data from shared memory
    printf("Message from shared memory: %s\n", shmaddr);

    // Detach the shared memory segment
    shmdt(shmaddr);

    // Destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
