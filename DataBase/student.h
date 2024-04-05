#ifndef _STUDENT_H_
#define _STUDENT_H_

#define STR_SIZE 24

typedef struct {
    char surname[STR_SIZE];
    char initials[STR_SIZE];
    char gender;
    int  group;
    int  dm, ma, la, cs, hi;
} Student;

#endif

