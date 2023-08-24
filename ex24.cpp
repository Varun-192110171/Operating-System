#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Create a new file using the open() system call
    int file_descriptor = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (file_descriptor == -1) {
        perror("Error creating the file");
        exit(EXIT_FAILURE);
    }
    
    // Write data to the file using the write() system call
    const char *data = "Hello, world!";
    ssize_t bytes_written = write(file_descriptor, data, strlen(data));
    
    if (bytes_written == -1) {
        perror("Error writing to the file");
        exit(EXIT_FAILURE);
    }
    
    printf("Data written to the file: %s\n", data);
    
    // Close the file using the close() system call
    if (close(file_descriptor) == -1) {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }
    
    // Reopen the file for reading using the open() system call
    file_descriptor = open("example.txt", O_RDONLY);
    
    if (file_descriptor == -1) {
        perror("Error opening the file for reading");
        exit(EXIT_FAILURE);
    }
    
    // Read data from the file using the read() system call
    char buffer[100];
    ssize_t bytes_read = read(file_descriptor, buffer, sizeof(buffer) - 1);
    
    if (bytes_read == -1) {
        perror("Error reading from the file");
        exit(EXIT_FAILURE);
    }
    
    buffer[bytes_read] = '\0';  // Null-terminate the buffer
    
    printf("Data read from the file: %s\n", buffer);
    
    // Close the file again
    if (close(file_descriptor) == -1) {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
