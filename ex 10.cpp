#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct Message {
    long mtype;         // Message type (must be greater than 0)
    char mtext[100];    // Message data
};

int main() {
    key_t key;
    int msgid;
    struct Message message;

    // Generate a unique key for the message queue
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Create a message queue
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    // Send a message to the queue
    message.mtype = 1;
    strcpy(message.mtext, "Hello, message queue!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent to the queue.\n");

    // Receive a message from the queue
    if (msgrcv(msgid, &message, sizeof(message.mtext), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received message from queue: %s\n", message.mtext);

    // Destroy the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    return 0;
}
