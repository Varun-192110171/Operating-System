#include <stdio.h>
#include <limits.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

int main() {
    int page_queue[MAX_FRAMES] = {0}; // Initialize page queue with zeros
    int page_table[MAX_PAGES] = {0};   // Initialize page table with zeros
    int page_faults = 0;

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

        // If page is not in memory, replace a page that will be used last
        if (!page_found) {
            int replaced_page = -1;
            int max_future_distance = -1;

            for (int j = 0; j < MAX_FRAMES; j++) {
                int future_distance = INT_MAX;
                for (int k = i + 1; k < MAX_PAGES; k++) {
                    if (page_queue[j] == pages[k]) {
                        future_distance = k - i;
                        break;
                    }
                }

                if (future_distance > max_future_distance) {
                    max_future_distance = future_distance;
                    replaced_page = j;
                }
            }

            page_table[page_queue[replaced_page]] = 0; // Update page table
            page_table[page] = 1;
            page_queue[replaced_page] = page; // Replace the selected page in the queue
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
