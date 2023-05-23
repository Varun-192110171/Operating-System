#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

void calculateNeedMatrix(int allocation[][MAX_RESOURCES], int max[][MAX_RESOURCES], int need[][MAX_RESOURCES], int available[]) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void printMatrix(int matrix[][MAX_RESOURCES], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {1, 1, 2},
        {2, 1, 2},
        {3, 0, 1},
        {0, 2, 0},
        {1, 1, 2}
    };

    int max[MAX_PROCESSES][MAX_RESOURCES] = {
        {5, 4, 4},
        {4, 3, 3},
        {9, 1, 3},
        {8, 6, 4},
        {2, 2, 3}
    };

    int available[MAX_RESOURCES] = {3, 2, 1}; 

    int need[MAX_PROCESSES][MAX_RESOURCES];

    calculateNeedMatrix(allocation, max, need, available);

    printf("Need Matrix:\n");
    printMatrix(need, MAX_PROCESSES, MAX_RESOURCES);

    return 0;
}
