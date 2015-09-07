#ifndef LISTSTUDENT_H
#define LISTSTUDENT_H
#include "DataStruct.h"

class ListStudent{
private:
    StrStudentInfo* first;
    StrStudentInfo* last;
    int numStudents;
public:
    ListStudent();
    virtual ~ListStudent();
    void addStudent(StrStudentInfo* student);
    void sortStudent();
    ListStudent* filterStudent();
    void printStudent();
    void writeStudent();
    int getNumStudents();
};

#endif