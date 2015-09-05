

#include <stddef.h>
#include <iostream>
#include <cstdlib>
#include <string>

#include <fstream>
#include "DataStruct.h"

using namespace std;

ListStudent::ListStudent() {
	first = last = NULL;
}

void ListStudent::append(unsigned int index, char name[64], char date[16], unsigned int id, unsigned int age) {
	if (first == NULL) {
		first = last = new _StrStudentInfo(index, name, date, id, age);
	}else {
		last = last->next = new _StrStudentInfo(index, name, date, id, age);
	}
}

void ListStudent::print() {
	StrStudentInfo* curr = first;
	while(curr != NULL) {
		cout << curr->index << "\t" << curr->name << "\t" << curr->date << "\t" << curr->age << endl;
		curr = curr->next;
	}
}

void ListStudent::filter() {
	
}

void ListStudent::sort() {
	
}

ListStudent::~ListStudent(){
	first = NULL;
}
