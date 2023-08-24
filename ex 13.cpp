#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000

// Linked list node structure for free memory blocks
struct Node {
    int size;
    int start;
    struct Node* next;
};

// Global variable representing the memory pool
char memory[MEMORY_SIZE];

// Head of the linked list representing free memory blocks
struct Node* freeList = NULL;

// Function to initialize the free memory list
void initializeFreeList() {
    freeList = (struct Node*)malloc(sizeof(struct Node));
    freeList->size = MEMORY_SIZE;
    freeList->start = 0;
    freeList->next = NULL;
}

// Function to allocate memory using First Fit strategy
void firstFit(int size) {
    struct Node* current = freeList;
    struct Node* previous = NULL;

    while (current != NULL) {
        if (current->size >= size) {
            // Allocate memory
            struct Node* newBlock = (struct Node*)malloc(sizeof(struct Node));
            newBlock->size = size;
            newBlock->start = current->start;
            newBlock->next = NULL;

            // Update free memory list
            current->size -= size;
            current->start += size;

            if (current->size == 0) {
                if (previous == NULL)
                    freeList = current->next;
                else
                    previous->next = current->next;
                free(current);
            }

            printf("Memory allocated using First Fit: Block starting at %d, Size: %d\n", newBlock->start, newBlock->size);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Memory allocation failed using First Fit.\n");
}

// Function to allocate memory using Best Fit strategy
void bestFit(int size) {
    // TODO: Implement the Best Fit strategy here
    printf("Best Fit strategy is not implemented in this example.\n");
}

// Function to allocate memory using Worst Fit strategy
void worstFit(int size) {
    // TODO: Implement the Worst Fit strategy here
    printf("Worst Fit strategy is not implemented in this example.\n");
}

int main() {
    initializeFreeList();

    // Example usage
    firstFit(100);
    firstFit(200);
    firstFit(50);

    // TODO: Add example usage for Best Fit and Worst Fit strategies

    return 0;
}
