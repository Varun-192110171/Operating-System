#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Sorts the requests in ascending order
void sortRequests(int requests[], int num_requests) {
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

int main() {
    int requests[MAX_REQUESTS];
    int num_requests;

    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &num_requests);

    if (num_requests > MAX_REQUESTS) {
        printf("Exceeded maximum number of requests.\n");
        return 1;
    }

    printf("Enter the disk I/O requests (cylinder numbers):\n");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the current head position: ");
    int current_head;
    scanf("%d", &current_head);

    printf("Enter the maximum cylinder number: ");
    int max_cylinder;
    scanf("%d", &max_cylinder);

    sortRequests(requests, num_requests);

    int total_distance = 0;
    printf("Sequence of serviced requests:\n");

    // Moving the head in one direction
    int current_pos = current_head;
    for (int i = 0; i < num_requests; i++) {
        int distance = abs(requests[i] - current_pos);
        total_distance += distance;
        printf("Request: %d, Distance: %d\n", requests[i], distance);
        current_pos = requests[i];
    }

    // Moving the head to the beginning (circular movement)
    total_distance += current_pos;
    printf("Moving the head to the beginning (circular).\n");
    current_pos = 0;

    // Servicing remaining requests on the circular path
    for (int i = 0; i < num_requests; i++) {
        int distance = abs(requests[i] - current_pos);
        total_distance += distance;
        printf("Request: %d, Distance: %d\n", requests[i], distance);
        current_pos = requests[i];
    }

    printf("Total head movement: %d\n", total_distance);

    return 0;
}
