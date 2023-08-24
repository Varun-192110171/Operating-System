#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

typedef struct Record {
    int record_id;
    char data[50];
} Record;

int main() {
    Record file[MAX_RECORDS];
    int num_records = 0;

    // Simulating writing records to the file
    for (int i = 0; i < 5; i++) {
        Record new_record;
        new_record.record_id = num_records + 1;
        sprintf(new_record.data, "This is record %d.", new_record.record_id);
        file[num_records++] = new_record;
    }

    // Simulating reading records from the file
    printf("Reading all records:\n");
    for (int i = 0; i < num_records; i++) {
        printf("Record %d: %s\n", file[i].record_id, file[i].data);
    }

    return 0;
}
