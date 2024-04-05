#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"
#include "io.h"

typedef struct {
    double avg_mark;
    int group;
} StudentStatistics;

double avg_mark(Student *s)
{
    return (s->dm + s->ma + s->la + s->cs + s->hi) / 5.0;
}

void sort(int arr[], int length)
{
    int tmp;
    for (int i = 1; i < length; ++i) {
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; --j) {
            tmp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = tmp;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage:\n\t./execute DB_FILE\n");
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    double max_avg = -1.0;

    // Each Student maps to { her average mark, her group }
    StudentStatistics students[200] = { { 0.0, -1 } };
    int students_qty = 0;

    // Gathering statistics for each student and finding globally maximal average mark
    Student student;
    while (student_read_bin(&student, in)) {
        if (student.gender == 'F') {  // Only consider female students
            double avg = avg_mark(&student);
            if (avg > max_avg) {
                max_avg = avg;
            }
            students[students_qty++] = (StudentStatistics) {
                avg, student.group
            };
        }
    }

    fclose(in);

    // Finding groups with maximum average mark
    int max_avg_groups[200] = { -1 };
    int max_avg_groups_qty = 0;
    for (int i = 0; i < students_qty; ++i) {
        if (students[i].avg_mark == max_avg) {
            max_avg_groups[max_avg_groups_qty++] = students[i].group;
        }
    }

    // Sorting makes counting easy (equal group numbers will be neighbours in sorted array)
    sort(max_avg_groups, max_avg_groups_qty);

    // Printing the first group with maximum average marks
    if (max_avg_groups_qty > 0) {
        printf("%d\n", max_avg_groups[0]);
    }

    return 0;
}
