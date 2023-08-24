#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRECTORIES 100
#define MAX_FILES_PER_DIR 100
#define MAX_NAME_LENGTH 50

struct File {
    char name[MAX_NAME_LENGTH];
};

struct Directory {
    char name[MAX_NAME_LENGTH];
    struct File files[MAX_FILES_PER_DIR];
    int fileCount;
};

struct FileSystem {
    struct Directory directories[MAX_DIRECTORIES];
    int dirCount;
};

void initializeFileSystem(struct FileSystem *fs) {
    fs->dirCount = 0;
}

void createDirectory(struct FileSystem *fs, const char *dirname) {
    if (fs->dirCount < MAX_DIRECTORIES) {
        strcpy(fs->directories[fs->dirCount].name, dirname);
        fs->directories[fs->dirCount].fileCount = 0;
        fs->dirCount++;
        printf("Directory '%s' created.\n", dirname);
    } else {
        printf("File system directory limit reached. Cannot create more directories.\n");
    }
}

void addFileToDirectory(struct FileSystem *fs, const char *dirname, const char *filename) {
    for (int i = 0; i < fs->dirCount; i++) {
        if (strcmp(fs->directories[i].name, dirname) == 0) {
            struct Directory *dir = &fs->directories[i];
            if (dir->fileCount < MAX_FILES_PER_DIR) {
                strcpy(dir->files[dir->fileCount].name, filename);
                dir->fileCount++;
                printf("File '%s' added to directory '%s'.\n", filename, dirname);
            } else {
                printf("Directory '%s' is full. Cannot add more files.\n", dirname);
            }
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

void listFilesInDirectory(struct FileSystem *fs, const char *dirname) {
    for (int i = 0; i < fs->dirCount; i++) {
        if (strcmp(fs->directories[i].name, dirname) == 0) {
            struct Directory *dir = &fs->directories[i];
            printf("Files in directory '%s':\n", dirname);
            for (int j = 0; j < dir->fileCount; j++) {
                printf("%d. %s\n", j + 1, dir->files[j].name);
            }
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

int main() {
    struct FileSystem fileSystem;
    initializeFileSystem(&fileSystem);

    int choice;
    char dirname[MAX_NAME_LENGTH];
    char filename[MAX_NAME_LENGTH];

    while (1) {
        printf("\n1. Create Directory\n");
        printf("2. Add File to Directory\n");
        printf("3. List Files in Directory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                createDirectory(&fileSystem, dirname);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                printf("Enter filename: ");
                scanf("%s", filename);
                addFileToDirectory(&fileSystem, dirname, filename);
                break;
            case 3:
                printf("Enter directory name: ");
                scanf("%s", dirname);
                listFilesInDirectory(&fileSystem, dirname);
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
