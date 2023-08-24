#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

typedef struct IndexBlock {
    int block_pointers[MAX_BLOCKS];
} IndexBlock;

typedef struct DataBlock {
    char data[128];
} DataBlock;

int main() {
    IndexBlock index_block;
    DataBlock data_blocks[MAX_BLOCKS];
    int num_blocks = 0;

    // Simulating writing data blocks
    for (int i = 0; i < 5; i++) {
        DataBlock new_data;
        sprintf(new_data.data, "This is data block %d.", num_blocks + 1);
        data_blocks[num_blocks++] = new_data;
    }

    // Simulating creating the index block
    for (int i = 0; i < num_blocks; i++) {
        index_block.block_pointers[i] = i;
    }

    // Simulating reading data blocks through the index block
    printf("Reading data blocks through index block:\n");
    for (int i = 0; i < num_blocks; i++) {
        int block_pointer = index_block.block_pointers[i];
        printf("Data block %d: %s\n", block_pointer + 1, data_blocks[block_pointer].data);
    }

    return 0;
}
