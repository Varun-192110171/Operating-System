#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50

struct File {
    char name[MAX_FILENAME_LENGTH];
};

struct Directory {
    struct File files[MAX_FILES];
    int fileCount;
};

void initializeDirectory(struct Directory *dir) {
    dir->fileCount = 0;
}

void addFile(struct Directory *dir, const char *filename) {
    if (dir->fileCount < MAX_FILES) {
        strcpy(dir->files[dir->fileCount].name, filename);
        dir->fileCount++;
        printf("File '%s' added to the directory.\n", filename);
    } else {
        printf("Directory is full. Cannot add more files.\n");
    }
}

void deleteFile(struct Directory *dir, const char *filename) {
    int found = 0;
    for (int i = 0; i < dir->fileCount; i++) {
        if (strcmp(dir->files[i].name, filename) == 0) {
            found = 1;
            // Remove the file by shifting subsequent files to the left
            for (int j = i; j < dir->fileCount - 1; j++) {
                strcpy(dir->files[j].name, dir->files[j + 1].name);
            }
            dir->fileCount--;
            printf("File '%s' deleted from the directory.\n", filename);
            break;
        }
    }
    if (!found) {
        printf("File '%s' not found in the directory.\n", filename);
    }
}

void listFiles(const struct Directory *dir) {
    printf("Files in the directory:\n");
    for (int i = 0; i < dir->fileCount; i++) {
        printf("%d. %s\n", i + 1, dir->files[i].name);
    }
}

int main() {
    struct Directory mainDirectory;
    initializeDirectory(&mainDirectory);

    int choice;
    char filename[MAX_FILENAME_LENGTH];

    while (1) {
        printf("\n1. Add File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%s", filename);
                addFile(&mainDirectory, filename);
                break;
            case 2:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(&mainDirectory, filename);
                break;
            case 3:
                listFiles(&mainDirectory);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
