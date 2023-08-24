#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
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

void executeNonPreemptiveSJF(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int shortestJobIndex = -1;
        int shortestJobBurstTime = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                if (shortestJobIndex == -1 || processes[i].burstTime < shortestJobBurstTime) {
                    shortestJobIndex = i;
                    shortestJobBurstTime = processes[i].burstTime;
                }
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
        } else {
            struct Process *shortestJobProcess = &processes[shortestJobIndex];
            printf("Time %d: Process %d started\n", currentTime, shortestJobProcess->processId);
            currentTime += shortestJobProcess->burstTime;
            shortestJobProcess->burstTime = 0;
            completed++;
            printf("Time %d: Process %d completed\n", currentTime, shortestJobProcess->processId);
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
    }

    sortProcessesByArrivalTime(processes, n);
    executeNonPreemptiveSJF(processes, n);

    return 0;
}
