#include <stdio.h>
#include <stdlib.h>

#define FILENAME "employee_records.dat"
#define MAX_NAME_LENGTH 50

struct Employee {
    int empID;
    char name[MAX_NAME_LENGTH];
    float salary;
};

void addRecord(FILE *file, const struct Employee *employee) {
    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    fwrite(employee, sizeof(struct Employee), 1, file);
    printf("Record added successfully.\n");
}

void updateRecord(FILE *file, int empID, const struct Employee *employee) {
    int found = 0;
    struct Employee tempEmployee;

    rewind(file); // Move the file pointer to the beginning of the file

    while (fread(&tempEmployee, sizeof(struct Employee), 1, file)) {
        if (tempEmployee.empID == empID) {
            found = 1;
            fseek(file, -sizeof(struct Employee), SEEK_CUR); // Move the file pointer back by one record
            fwrite(employee, sizeof(struct Employee), 1, file);
            printf("Record updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Record with employee ID %d not found.\n", empID);
    }
}

void retrieveRecord(FILE *file, int empID) {
    struct Employee employee;
    int found = 0;

    rewind(file);

    while (fread(&employee, sizeof(struct Employee), 1, file)) {
        if (employee.empID == empID) {
            found = 1;
            printf("Employee ID: %d\n", employee.empID);
            printf("Name: %s\n", employee.name);
            printf("Salary: %.2f\n", employee.salary);
            break;
        }
    }

    if (!found) {
        printf("Record with employee ID %d not found.\n", empID);
    }
}

void deleteRecord(FILE *file, int empID) {
    int found = 0;
    struct Employee tempEmployee;
    FILE *tempFile = fopen("temp.dat", "wb");

    rewind(file);

    while (fread(&tempEmployee, sizeof(struct Employee), 1, file)) {
        if (tempEmployee.empID != empID) {
            fwrite(&tempEmployee, sizeof(struct Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("Record with employee ID %d deleted successfully.\n", empID);
    } else {
        printf("Record with employee ID %d not found.\n", empID);
    }
}

int main() {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        file = fopen(FILENAME, "wb+");
    }

    int choice;
    struct Employee employee;
    int empID;

    while (1) {
        printf("\n1. Add Record\n");
        printf("2. Update Record\n");
        printf("3. Retrieve Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter employee ID: ");
                scanf("%d", &employee.empID);
                printf("Enter name: ");
                scanf("%s", employee.name);
                printf("Enter salary: ");
                scanf("%f", &employee.salary);
                addRecord(file, &employee);
                break;
            case 2:
                printf("Enter employee ID to update: ");
                scanf("%d", &empID);
                printf("Enter new name: ");
                scanf("%s", employee.name);
                printf("Enter new salary: ");
                scanf("%f", &employee.salary);
                updateRecord(file, empID, &employee);
                break;
            case 3:
                printf("Enter employee ID to retrieve: ");
                scanf("%d", &empID);
                retrieveRecord(file, empID);
                break;
            case 4:
                printf("Enter employee ID to delete: ");
                scanf("%d", &empID);
                deleteRecord(file, empID);
                break;
            case 5:
                printf("Exiting...\n");
                fclose(file);
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
