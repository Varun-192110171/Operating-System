#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
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

int findHighestPriorityProcess(struct Process processes[], int n, int currentTime) {
    int highestPriorityIndex = -1;
    int highestPriority = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
            if (highestPriorityIndex == -1 || processes[i].priority < highestPriority) {
                highestPriorityIndex = i;
                highestPriority = processes[i].priority;
            }
        }
    }

    return highestPriorityIndex;
}

void executePriorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int highestPriorityProcessIndex = findHighestPriorityProcess(processes, n, currentTime);

        if (highestPriorityProcessIndex == -1) {
            currentTime++;
        } else {
            struct Process *highestPriorityProcess = &processes[highestPriorityProcessIndex];
            highestPriorityProcess->burstTime--;
            currentTime++;

            if (highestPriorityProcess->burstTime == 0) {
                completed++;
                printf("Time %d: Process %d completed\n", currentTime, highestPriorityProcess->processId);
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
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    sortProcessesByArrivalTime(processes, n);
    executePriorityScheduling(processes, n);

    return 0;
}
