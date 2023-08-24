#include <stdio.h>
#include <sys/stat.h>

int main() {
    // Specify the filename
    const char *filename = "example.txt";

    // Set permissions: Owner can read and write, Group and Others can only read
    int permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    // Apply permissions using chmod
    if (chmod(filename, permissions) == 0) {
        printf("File access permissions set successfully.\n");
    } else {
        perror("chmod error");
        return 1;
    }

    return 0;
}
