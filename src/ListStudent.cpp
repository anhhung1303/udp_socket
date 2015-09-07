#include "../include/ListStudent.h"
#include "../include/DataStruct.h"
#include <string>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ListStudent::ListStudent(){
    first = last = NULL;
    numStudents = 0;
}

ListStudent::~ListStudent(){
    delete first, last, numStudents;
}

void ListStudent::addStudent(StrStudentInfo* student){
    numStudents++;
    if (first == NULL){
        first = last = student;
    } else{
        last = last -> next = student;
    }
}

void ListStudent::sortStudent(){
    // StrStudentInfo* pre = first;
    // StrStudentInfo* curr = pre->next;
    // StrStudentInfo* pos = curr -> next;
}

ListStudent* ListStudent::filterStudent(){
    ListStudent* filteredListStudent = new ListStudent();
    filteredListStudent->printStudent();
    StrStudentInfo* curr = first;
    int count = 0;
    char year[4];
    for(curr = first; curr != NULL; curr = curr->next){
        for(int i = 6; i <= 9; i++){
            year[i-6] = curr->date[i];
        }
        if (atoi(year) == 1990){
            filteredListStudent -> addStudent(curr);
        }
    }
    cout << filteredListStudent->getNumStudents() << endl;
    return filteredListStudent;
}

void ListStudent::printStudent(){
    StrStudentInfo* curr = first;
    // while(curr != NULL){
    //     cout << curr->index << "\t" << curr->name << "\t" << curr->date << "\t" << curr->id << "\t" << curr->age << endl;
    //     curr = curr -> next;
    // }
    for(int i = 0; i < numStudents; i++) {
        cout << curr->index << "\t" << curr->name << "\t" << curr->date << "\t" << curr->id << "\t" << curr->age << endl;
        curr = curr->next;
    }
}

void ListStudent::writeStudent(){
    
}

int ListStudent::getNumStudents() {
    return numStudents;
}

// int main(int argc, char const *argv[]){
//     ListStudent* listStudent = new ListStudent();
//     unsigned int index;
//     string name;
//     string date;
//     unsigned int id;
//     unsigned int age;
//     std::string line;
//     ifstream input("input_data.txt");
//     while (getline(input, line)) {
//         if (line[0] == '#' || line[0] == '\n' || line[1] == '\t') {
//             continue;
//         }
//         istringstream tmp(line);
//         tmp >> index >> name >> date >> id >> age;
//         StrStudentInfo* student = new StrStudentInfo();
//         student->index = index;
//         copy(name.begin(), name.end(), student->name);
//         student -> name[name.size()] = '\0';
//         copy(date.begin(), date.end(), student->date);
//         student->date[date.size()] = '\0';
//         student->id = id;
//         student->age = age;
//         listStudent -> addStudent(student);
//     }
//     // listStudent->printStudent();
//     //cout << listStudent -> getNumStudents() << endl;
//     ListStudent* filteredListStudent = listStudent -> filterStudent();
//     filteredListStudent->printStudent();
//     return 0;
// }
