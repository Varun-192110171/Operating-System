#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES] = {10, 5, 7};
int maximum[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[NUM_PROCESSES][NUM_RESOURCES];

bool check_safe_state(int process) {
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (need[process][i] > available[i]) {
            return false;
        }
    }
    return true;
}

bool banker_algorithm() {
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES] = {0};

    // Initialize need matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Initialize work vector
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        work[i] = available[i];
    }

    // Find a safe sequence
    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (finish[i] == 0 && check_safe_state(i)) {
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    work[j] += allocation[i][j];
                }
                finish[i] = 1;
                found = true;
                count++;
                break;
            }
        }
        if (!found) {
            break; // No safe sequence found
        }
    }

    return count == NUM_PROCESSES;
}

int main() {
    if (banker_algorithm()) {
        printf("Safe state. Resources can be allocated.\n");
    } else {
        printf("Unsafe state. Resources cannot be allocated safely.\n");
    }

    return 0;
}









