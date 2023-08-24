#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct DataBlock {
    char data[128];
    int next_block;  // Pointer to the next block
} DataBlock;

typedef struct File {
    int first_block; // Pointer to the first block
    int last_block;  // Pointer to the last block
} File;

int main() {
    DataBlock data_blocks[MAX_BLOCKS];
    File file;
    int num_blocks = 0;

    // Simulating writing data blocks
    for (int i = 0; i < 5; i++) {
        DataBlock new_data;
        sprintf(new_data.data, "This is data block %d.", num_blocks + 1);
        new_data.next_block = -1; // Initialize next_block pointer to -1
        data_blocks[num_blocks++] = new_data;
    }

    // Simulating creating the file linked list
    file.first_block = 0;   // Pointer to the first block
    file.last_block = num_blocks - 1; // Pointer to the last block

    // Simulating reading data blocks through the file linked list
    int current_block = file.first_block;
    printf("Reading data blocks through linked allocation:\n");
    while (current_block != -1) {
        printf("Data block %d: %s\n", current_block + 1, data_blocks[current_block].data);
        current_block = data_blocks[current_block].next_block;
    }

    return 0;
}

