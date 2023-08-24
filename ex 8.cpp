#include <stdio.h>
#define MAX_PROCESSES 10
struct Process {
    int processId;
    int burstTime;
};

void executeRoundRobin(struct Process processes[], int n, int quantum) {
    int remainingTime[MAX_PROCESSES];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }
    int currentTime = 0;
    int completed = 0;
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                if (remainingTime[i] <= quantum) {
                    currentTime += remainingTime[i];
                    remainingTime[i] = 0;
                    completed++;
                    printf("Time %d: Process %d completed\n", currentTime, i + 1);
                } else {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                    printf("Time %d: Process %d executed for %d units\n", currentTime, i + 1, quantum);
                }
            }
        }
    }
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    executeRoundRobin(processes, n, quantum);

    return 0;
}
