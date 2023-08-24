#include <stdio.h>

#define MAX_PROCESSES 10

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
};

void calculateWaitingTime(struct Process processes[], int n, int waitingTime[]) {
    waitingTime[0] = 0;
    
    for (int i = 1; i < n; i++) {
        waitingTime[i] = processes[i - 1].burstTime + waitingTime[i - 1];
    }
}

void calculateTurnaroundTime(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

void calculateAverageTimes(struct Process processes[], int n) {
    int waitingTime[MAX_PROCESSES];
    int turnaroundTime[MAX_PROCESSES];
    
    calculateWaitingTime(processes, n, waitingTime);
    calculateTurnaroundTime(processes, n, waitingTime, turnaroundTime);
    
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;
    
    printf("Process\t  Burst Time\tWaiting Time\tTurnaround Time\n");
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[MAX_PROCESSES];
    
    for (int i = 0; i < n; i++) {
        processes[i].processId = i + 1;
        processes[i].arrivalTime = 0;  
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }
    
    calculateAverageTimes(processes, n);
    
    return 0;
}
