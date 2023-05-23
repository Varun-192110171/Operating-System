#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_REFERENCES 100

int findLFUPage(int pages[], int pageFaults[], int currentReference, int frameCount, int referencesCount) {
    int lfuPage = 0;
    int minFutureTime = referencesCount + 1;
    int i, j;

    for (i = 0; i < frameCount; i++) {
        int page = pages[i];
        int futureTime = referencesCount;

        for (j = currentReference + 1; j < referencesCount; j++) {
            if (page == pageFaults[j]) {
                futureTime = j;
                break;
            }
        }

        if (futureTime > minFutureTime) {
            minFutureTime = futureTime;
            lfuPage = i;
        }
    }

    return lfuPage;
}

int main() {
    int pageFaults[MAX_REFERENCES];
    int pages[MAX_FRAMES];
    int frameCount, referencesCount, pageFaultCount;
    int i, j;

    printf("Number of page frames: ");
    scanf("%d", &frameCount);

    printf("Page reference sequence (separated by spaces): ");
    for (i = 0; i < MAX_REFERENCES; i++) {
        scanf("%d", &pageFaults[i]);
        if (pageFaults[i] == -1) {
            referencesCount = i;
            break;
        }
    }

    // Initialize page frames with -1 (empty)
    for (i = 0; i < frameCount; i++) {
        pages[i] = -1;
    }

    pageFaultCount = 0;

    // Perform page replacement
    for (i = 0; i < referencesCount; i++) {
        int page = pageFaults[i];
        int pageFound = 0;

        // Check if the page is already in a frame
        for (j = 0; j < frameCount; j++) {
            if (pages[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If page is not found in any frame, perform page fault
        if (!pageFound) {
            pageFaultCount++;

            // Find the page to replace using LFU algorithm
            int lfuPage = findLFUPage(pages, pageFaults, i, frameCount, referencesCount);

            // Replace the page
            pages[lfuPage] = page;
        }
    }

    printf("Number of page faults: %d\n", pageFaultCount);

    return 0;
}
