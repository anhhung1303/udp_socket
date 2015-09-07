#include "../include/socketA.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// SocketA::SocketA(){
// 	listStudent = new ListStudent();
// }

void SocketA::error(const char *msg){
    cout << msg<<"\n";
    exit(0);
}

void SocketA::initRecv(int portno){
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
}

int SocketA::start(string ipAdr, int portno){
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	error("ERROR opening socket");
	server = gethostbyname(ipAdr.c_str());
	if (server == NULL) {
	cout << stderr,"ERROR, no such host\n";
	exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ipAdr.c_str());
	serv_addr.sin_port = htons(portno);
	initRecv(portno+1);
	//----------------send-----------------------
	int inputReq = 1;
	while(true){
		cout << "Student Management\n";
		cout << "1. Load input file\n";
		cout << "2. Show all list\n";
		cout << "3. Filter students that was born in 1990\n";
		cout << "4. Sort by increament ID\n";
		cout << "5. Insert new student\n";
		cout << "Enter your choice:\n";
		cin >> inputReq;
		//inputReq = 1;
		switch(inputReq){
			case 1:	{
				Message* msg = ABStudentInfoReq(getData());
				n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
				if (n < 0) error("ERROR send");
				break;
			}
			case 2: {
				Message* msg = ABShowAllReq();
				n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
				if (n < 0) error("Error send");
				break;
			}
			case 3: {
				Message* msg = ABBorn1990Req();
				n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
				if (n < 0) error("Error send");
				break;
			}
			case 4: {
				Message* msg = ABSortIDReq();
				n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
				if (n < 0) error("Error send");
				break;
			}
			// case 5: {
			// 	Message* msg = ABInsertNewReq();
			// 	n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
			// 	if (n < 0) error("Error send");
			// 	break;
			// }
		};
		handleRespond();
	}
	return 0;
}

void SocketA::stop(){
	close(sockfd);
}

Message* SocketA::ABStudentInfoReq(StrABStudentInfoReq data){
	Message* msg = new Message(PACKAGE_MAX_LEN);
	msg->putInt(data.msgId);
	msg->putInt(data.numStudents);
	for (int i = 0; i < data.numStudents; i++){
		msg->putInt(data.studentInfo[i].index);
		msg->putString(data.studentInfo[i].name);
		msg->putString(data.studentInfo[i].date);
		msg->putInt(data.studentInfo[i].id);
		msg->putInt(data.studentInfo[i].age);
	}
	return msg;
}

Message* SocketA::ABShowAllReq(){
	Message* msg = new Message(PACKAGE_MAX_LEN);
	msg->putInt(A_B_SHOW_ALL_REQ_SIG);
	return msg;
}

Message* SocketA::ABBorn1990Req(){
	Message* msg = new Message(PACKAGE_MAX_LEN);
	msg->putInt(A_B_BORN_1990_REQ_SIG);
	return msg;
}

Message* SocketA::ABSortIDReq(){
	Message* msg = new Message(PACKAGE_MAX_LEN);
	msg->putInt(A_B_SORT_ID_REQ_SIG);
	return msg;
}

StrABStudentInfoReq SocketA::getData(){
	StrABStudentInfoReq data;
	data.msgId = A_B_STUDENT_INFO_REQ_SIG;

	data.numStudents = 0;
	
	int count = 0;
	unsigned int index;
	string name;
	string date;
	unsigned int id;
	unsigned int age;
	std::string line;
	ifstream input("input_data.txt");
	while (getline(input, line)) {
		if (line[0] == '#' || line[0] == '\n' || line[1] == '\t') {
			continue;
		}
		istringstream tmp(line);
		tmp >> index >> name >> date >> id >> age;
		data.studentInfo[count].index = index;
		// data.studentInfo[count].name = name.c_str();
		// data.studentInfo[count].date = date.c_str();
		copy(name.begin(), name.end(), data.studentInfo[count].name);
		data.studentInfo[count].name[name.size()] = '\0';
		copy(date.begin(), date.end(), data.studentInfo[count].date);
		data.studentInfo[count].date[date.size()] = '\0';
		data.studentInfo[count].id = id;
		data.studentInfo[count].age = age;
		count++;		
	}
	data.numStudents = count;
	input.close();
	// data.studentInfo[0].index = 1;
	// sprintf(data.studentInfo[0].name, "Hung sida");
	// sprintf(data.studentInfo[0].date, "3/9/2015");
	// data.studentInfo[0].id = 1000;
	// data.studentInfo[0].age = 24;
	return data;
}

void SocketA::handleRespond(){
	char buffer[PACKAGE_MAX_LEN];
	n = recv(sockfd, buffer, PACKAGE_MAX_LEN-1, 0);
	if (n < 0) {
		error("ERROR reading from socket");
		exit(1);
	}
	Message* msg = new Message(buffer, n);
	int msgID = msg->getInt();
	cout << "msgID: " << msgID << endl ;
	switch(msgID){
		case B_A_STUDENT_INFO_RES_SIG: {
			cout << "========================================================" << endl;
			cout << "| Hey A, I have recieved your message and processed it |" << endl;
			cout << "========================================================" << endl;;
			break;
		}
		case B_A_SHOW_ALL_RES_SIG: {
			cout << "TITLE:\t" << "INDEX\t" << "NAME\t\t\t" << "DATE\t\t" << "ID\t" << "AGE" << endl;
			int n = msg->getInt();
			unsigned int index;
		    string name;
		    string date;
		    unsigned int id;
		    unsigned int age;
		    for(int i = 0; i < n; i++){
		    	index = msg->getInt();
		    	name = msg->getString().c_str();
		    	date = msg->getString().c_str();
		    	id = msg->getInt();
		    	age = msg->getInt();
		    	cout << "\t" << index << "\t" << name << "\t\t" << date << "\t" << id << "\t" << age << endl;
		    }
		    break;
		}
		case B_A_BORN_1990_RES_SIG: {
			cout << "TITLE:\t" << "INDEX\t" << "NAME\t\t\t" << "DATE\t\t" << "ID\t" << "AGE" << endl;
			int n = msg->getInt();
			unsigned int index;
		    string name;
		    string date;
		    unsigned int id;
		    unsigned int age;
		    for(int i = 0; i < n; i++){
		    	index = msg->getInt();
		    	name = msg->getString().c_str();
		    	date = msg->getString().c_str();
		    	id = msg->getInt();
		    	age = msg->getInt();
		    	cout << "\t" << index << "\t" << name << "\t\t" << date << "\t" << id << "\t" << age << endl;
		    }
		    break;
		}
		case B_A_SORT_ID_RES_SIG: {
			cout << "TITLE:\t" << "INDEX\t" << "NAME\t\t\t" << "DATE\t\t" << "ID\t" << "AGE" << endl;
			int n = msg->getInt();
			unsigned int index;
		    string name;
		    string date;
		    unsigned int id;
		    unsigned int age;
		    for(int i = 0; i < n; i++){
		    	index = msg->getInt();
		    	name = msg->getString().c_str();
		    	date = msg->getString().c_str();
		    	id = msg->getInt();
		    	age = msg->getInt();
		    	cout << "\t" << index << "\t" << name << "\t\t" << date << "\t" << id << "\t" << age << endl;
		    }
		    break;
		}
	};
}

int main(int argc, char const *argv[]){
	(new SocketA())->start("127.0.0.1", 8080);
	return 0;
}
