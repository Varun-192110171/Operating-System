#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_NAME_LENGTH 50

struct File {
    char name[MAX_NAME_LENGTH];
};

struct Directory {
    char name[MAX_NAME_LENGTH];
    struct File files[MAX_FILES];
    int fileCount;
};

int main() {
    struct Directory directory;
    strcpy(directory.name, "CSE");
    directory.fileCount = 0;

    // Adding files to the directory
    strcpy(directory.files[directory.fileCount++].name, "A");
    strcpy(directory.files[directory.fileCount++].name, "B");
    strcpy(directory.files[directory.fileCount++].name, "C");

    // Displaying the files in the directory
    printf("Directory: %s\n", directory.name);
    printf("Files:\n");
    for (int i = 0; i < directory.fileCount; i++) {
        printf("%s\n", directory.files[i].name);
    }

    return 0;
}
