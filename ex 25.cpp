#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // Open a file using the open() system call
    int file_descriptor = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    
    if (file_descriptor == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    
    printf("File opened successfully.\n");
    
    // Use the fcntl() system call to set the file status flags
    int flags = fcntl(file_descriptor, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
        exit(EXIT_FAILURE);
    }
    
    flags |= O_APPEND;  // Set the append flag
    
    if (fcntl(file_descriptor, F_SETFL, flags) == -1) {
        perror("Error setting file flags");
        exit(EXIT_FAILURE);
    }
    
    printf("File flags set to append mode.\n");
    
    // Use the lseek() system call to seek to the end of the file
    off_t offset = lseek(file_descriptor, 0, SEEK_END);
    
    if (offset == -1) {
        perror("Error seeking file");
        exit(EXIT_FAILURE);
    }
    
    printf("Seeked to the end of the file.\n");
    
    // Use the stat() system call to get information about the file
    struct stat file_info;
    if (stat("example.txt", &file_info) == -1) {
        perror("Error getting file information");
        exit(EXIT_FAILURE);
    }
    
    printf("File size: %lld bytes\n", (long long)file_info.st_size);
    
    // Use opendir() and readdir() system calls to list files in a directory
    DIR *directory = opendir(".");
    
    if (directory == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    
    printf("Files in the current directory:\n");
    
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    
    // Close the directory
    closedir(directory);
    
    // Close the file
    if (close(file_descriptor) == -1) {
        perror("Error closing the file");
        exit(EXIT_FAILURE);
    }
    
    printf("File closed.\n");
    
    return 0;
}
