#include "../include/ListStudent.h"
#include "../include/DataStruct.h"
#include <string>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

ListStudent::ListStudent(){
    first = last = NULL;
    numStudents = 0;
}

ListStudent::~ListStudent(){
    StrStudentInfo* temp = first;
    while (first != NULL){
        temp = first->next;
        delete first;
        first = temp;
    }
}

void ListStudent::addStudent(StrStudentInfo* student){
    numStudents++;
    if (first == NULL){
        first = last = student;
    } else{
        last = last -> next = student;
    }
}

void ListStudent::swapStudent(StrStudentInfo* first, StrStudentInfo* second){
    swap(first->index, second->index);
    swap(first->name, second->name);
    swap(first->date, second->date);
    swap(first->id, second->id);
    swap(first->age, second->age);
}

void ListStudent::sortStudent(){
    StrStudentInfo* curr = first;
    StrStudentInfo* lcurr = NULL;
    bool swapped = false;
    if(curr == NULL){
        return;
    }
    do {
        swapped = false;
        curr = first;
        while(curr->next != lcurr){
            if (curr->id > curr->next->id){
                swapStudent(curr, curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
        lcurr = curr;
    }while(swapped);
}

ListStudent* ListStudent::filterStudent(){
    ListStudent* filteredListStudent = new ListStudent();
    StrStudentInfo* curr = first;
    int count = 0;
    char year[4];
    for(int i = 0; i < numStudents; i++){
        for(int j = 6; j <= 9; j++){
            year[j-6] = curr->date[j];
        }
        if (atoi(year) == 1990){
            StrStudentInfo* temp = new StrStudentInfo();
            temp->index = curr->index;
            strcpy(temp->name, curr->name);
            strcpy(temp->date, curr->date);
            temp->id = curr->id;
            temp->age = curr->age;
            temp->next = NULL;
            filteredListStudent -> addStudent(temp);
        }
        curr = curr->next;
    }
    return filteredListStudent;
}

void ListStudent::printStudent(){
    StrStudentInfo* curr = first;
    while(curr != NULL) {
        cout << curr->index << "\t" << curr->name << "\t" << curr->date << "\t" << curr->id << "\t" << curr->age << endl;
        curr = curr->next;
    }
}

StrStudentInfo* ListStudent::getFirst(){
    return first;
}

int ListStudent::getNumStudents() {
    return numStudents;
}
