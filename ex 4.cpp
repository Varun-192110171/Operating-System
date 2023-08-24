#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int remainingTime;
};

void sortProcessesByArrivalTime(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int findNextProcess(struct Process processes[], int n, int currentTime) {
    int smallestIndex = -1;
    int smallestBurstTime = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
            if (smallestIndex == -1 || processes[i].remainingTime < smallestBurstTime) {
                smallestIndex = i;
                smallestBurstTime = processes[i].remainingTime;
            }
        }
    }

    return smallestIndex;
}

void executeSJN(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int nextProcessIndex = findNextProcess(processes, n, currentTime);

        if (nextProcessIndex == -1) {
            currentTime++;
        } else {
            struct Process *nextProcess = &processes[nextProcessIndex];
            nextProcess->remainingTime--;
            currentTime++;

            if (nextProcess->remainingTime == 0) {
                completed++;
                printf("Time %d: Process %d completed\n", currentTime, nextProcess->processId);
            }
        }
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    sortProcessesByArrivalTime(processes, n);
    executeSJN(processes, n);

    return 0;
}
