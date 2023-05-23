#include <stdio.h>

#define MAX_PARTITIONS 6
#define MAX_PROCESSES 4

void bestFit(int partitions[], int processSizes[]) {
    int allocation[MAX_PROCESSES];
    int i, j;

    for (i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1;

        int bestFitIndex = -1;

        for (j = 0; j < MAX_PARTITIONS; j++) {
            if (partitions[j] >= processSizes[i]) {
                if (bestFitIndex == -1 || partitions[j] < partitions[bestFitIndex]) {
                    bestFitIndex = j;
                }
            }
        }

        if (bestFitIndex != -1) {
            allocation[i] = bestFitIndex;
            partitions[bestFitIndex] -= processSizes[i];
        }
    }

    printf("Process No.\tProcess Size\tPartition No.\n");
    for (i = 0; i < MAX_PROCESSES; i++) {
        printf("%d\t\t%d KB\t\t", i, processSizes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int partitions[MAX_PARTITIONS] = {300, 600, 350, 200, 750, 125};
    int processSizes[MAX_PROCESSES] = {275, 400, 200, 500};

    bestFit(partitions, processSizes);

    return 0;
}
