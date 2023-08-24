#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int main() {
    int page_queue[MAX_FRAMES] = {0}; // Initialize page queue with zeros
    int page_table[MAX_PAGES] = {0};   // Initialize page table with zeros
    int page_faults = 0;
    int oldest_page_index = 0; // Index of the oldest page in the queue

    int pages[MAX_PAGES] = {0, 1, 2, 3, 4, 5, 2, 1, 0, 3, 6, 4, 3, 2, 1, 0, 7, 6, 4, 3};

    for (int i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (page_queue[j] == page) {
                page_found = 1;
                break;
            }
        }

        // If page is not in memory, replace the oldest page
        if (!page_found) {
            page_table[page] = 1; // Update page table
            page_queue[oldest_page_index] = page; // Replace the oldest page in the queue
            oldest_page_index = (oldest_page_index + 1) % MAX_FRAMES; // Move index to the next oldest page
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

