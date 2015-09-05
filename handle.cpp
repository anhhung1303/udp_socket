#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "handle.h"

using namespace std;

void handleFirstCase(){
	string line;
	bool tit_flag = true;
	ifstream data_file("input_data.txt");
	while(getline(data_file, line)) {
		if (line[0] != "#" && tit_flag != true) {
			istringstream iss(line);
			_StrStudentInfo* student = new _StrStudentInfo();
			tit_flag = false;
		}
	}
	data_file.close();
	return 0;
}