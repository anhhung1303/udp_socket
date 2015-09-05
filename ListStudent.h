#ifndef LISTSTUDENT_H
#define LISTSTUDENT_H

#include <string>
#include "DataStruct.h"

class ListStudent {
	public:
		ListStudent();
		void append(unsigned int index, char name[64], char date[16], unsigned int id, unsigned int age);
		void print();
		void filter();
		void sort();
		virtual ~ListStudent();
	private:
		_StrStudentInfo* first;
		_StrStudentInfo* last;
};

#endif
