#include <stdio.h>

#define MAX_BLOCKS 100

// Structure to represent a memory block
struct MemoryBlock {
    int block_id;
    int size;
    int allocated;
};

// Function to allocate memory using best fit
void allocateMemory(struct MemoryBlock blocks[], int num_blocks, int process_id, int process_size) {
    int best_fit_block_index = -1;
    int min_free_space = __INT_MAX__;

    for (int i = 0; i < num_blocks; i++) {
        if (!blocks[i].allocated && blocks[i].size >= process_size) {
            if (blocks[i].size - process_size < min_free_space) {
                best_fit_block_index = i;
                min_free_space = blocks[i].size - process_size;
            }
        }
    }

    if (best_fit_block_index != -1) {
        blocks[best_fit_block_index].allocated = 1;
        printf("Process %d allocated to Block %d\n", process_id, blocks[best_fit_block_index].block_id);
    } else {
        printf("Process %d cannot be allocated due to insufficient memory.\n", process_id);
    }
}

// Function to deallocate memory
void deallocateMemory(struct MemoryBlock blocks[], int num_blocks, int process_id) {
    for (int i = 0; i < num_blocks; i++) {
        if (blocks[i].allocated && blocks[i].block_id == process_id) {
            blocks[i].allocated = 0;
            printf("Memory block %d deallocated.\n", process_id);
            return;
        }
    }
    printf("Memory block %d not found.\n", process_id);
}

int main() {
    int num_blocks;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &num_blocks);

    struct MemoryBlock blocks[MAX_BLOCKS];

    for (int i = 0; i < num_blocks; i++) {
        blocks[i].block_id = i;
        printf("Enter size of block %d: ", i);
        scanf("%d", &blocks[i].size);
        blocks[i].allocated = 0;
    }

    int choice, process_id, process_size;

    do {
        printf("\n1. Allocate Memory\n2. Deallocate Memory\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID: ");
                scanf("%d", &process_id);
                printf("Enter process size: ");
                scanf("%d", &process_size);
                allocateMemory(blocks, num_blocks, process_id, process_size);
                break;
            case 2:
                printf("Enter process ID to deallocate: ");
                scanf("%d", &process_id);
                deallocateMemory(blocks, num_blocks, process_id);
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
