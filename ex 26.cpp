#include <stdio.h>
#include <stdlib.h>

int main() {
    // Create a new file and write data to it
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error creating the file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "Hello, world!\n");
    fclose(file);
    
    printf("File created and data written.\n");
    
    // Append more data to the file
    file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error opening the file for appending");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "This is an appended line.\n");
    fclose(file);
    
    printf("Data appended to the file.\n");
    
    // Read data from the file
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening the file for reading");
        exit(EXIT_FAILURE);
    }
    
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    
    // Rename the file
    if (rename("example.txt", "renamed_example.txt") != 0) {
        perror("Error renaming the file");
        exit(EXIT_FAILURE);
    }
    
    printf("File renamed.\n");
    
    // Delete the file
    if (remove("renamed_example.txt") != 0) {
        perror("Error deleting the file");
        exit(EXIT_FAILURE);
    }
    
    printf("File deleted.\n");
    
    return 0;
}
