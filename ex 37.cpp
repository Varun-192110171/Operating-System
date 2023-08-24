#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

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

    int total_distance = 0;
    printf("Sequence of serviced requests:\n");

    for (int i = 0; i < num_requests; i++) {
        int distance = abs(requests[i] - current_head);
        total_distance += distance;
        printf("Request: %d, Distance: %d\n", requests[i], distance);
        current_head = requests[i];
    }

    printf("Total head movement: %d\n", total_distance);

    return 0;
}
