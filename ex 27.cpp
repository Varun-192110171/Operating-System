#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *dir_path = "."; // Default directory is the current directory

    // Check if a directory path is provided as a command-line argument
    if (argc > 1) {
        dir_path = argv[1];
    }

    // Open the specified directory
    DIR *directory = opendir(dir_path);
    if (directory == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read directory entries and print their names
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(directory);

    return 0;
}
