#include <stdio.h>
#include <unistd.h>

void printNumbers(int start, int end, int step) {
    for (int i = start; i <= end; i += step) {
        printf("%d ", i);
    }
    printf("\n");
}

int main() {
    int childProcessCount = 4;
    pid_t pid;

    for (int i = 1; i <= childProcessCount; i++) {
        pid = fork();

        if (pid < 0) {
            printf("Error occurred while forking.\n");
            return 1;
        } else if (pid == 0) {
            printf("Child process with ID %d:\n", getpid());

            switch (i) {
                case 1:
                    printf("Odd numbers: ");
                    printNumbers(1, 10, 2);
                    break;
                case 2:
                    printf("Even numbers: ");
                    printNumbers(2, 10, 2);
                    break;
                case 3:
                    printf("Multiples of 3: ");
                    printNumbers(3, 9, 3);
                    break;
                case 4:
                    printf("Multiples of 5: ");
                    printNumbers(5, 10, 5);
                    break;
            }

            return 0;
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < childProcessCount; i++) {
        wait(NULL);
    }

    return 0;
}
