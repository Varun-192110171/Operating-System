#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

// Find the index of the least recently used page
int findLRUIndex(int page_queue[], int last_used[], int num_frames) {
    int min_index = 0;
    int min_time = INT_MAX;

    for (int i = 0; i < num_frames; i++) {
        if (last_used[i] < min_time) {
            min_time = last_used[i];
            min_index = i;
        }
    }

    return min_index;
}

int main() {
    int page_queue[MAX_FRAMES] = {0}; // Initialize page queue with zeros
    int page_table[MAX_PAGES] = {0};   // Initialize page table with zeros
    int page_faults = 0;
    int last_used[MAX_FRAMES] = {0}; // Array to track the last usage time of frames

    int pages[MAX_PAGES] = {0, 1, 2, 3, 4, 5, 2, 1, 0, 3, 6, 4, 3, 2, 1, 0, 7, 6, 4, 3};

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_queue[j] == page) {
                page_found = 1;
                last_used[j] = i; // Update last usage time of the frame
                break;
            }
        }

        // If page is not in memory, replace the least recently used page
        if (!page_found) {
            int lru_index = findLRUIndex(page_queue, last_used, MAX_FRAMES);
            page_table[page_queue[lru_index]] = 0; // Update page table
            page_table[page] = 1;
            page_queue[lru_index] = page; // Replace the least recently used page in the queue
            last_used[lru_index] = i; // Update last usage time of the frame
            page_faults++;
        }

        // Print current page queue
        printf("Page Queue: ");
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_queue[j] == 0) {
                printf("- ");
            } else {
                printf("%d ", page_queue[j]);
            }
        }
        printf(" - Page Faults: %d\n", page_faults);
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
