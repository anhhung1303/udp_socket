#include "socketA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void SocketA::error(const char *msg)
{
    cout << msg<<"\n";
    exit(0);
}

int SocketA::start(string ipAdr, int portno)
{
	char buffer[256];
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
    //if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	//	printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
	//----------------send-----------------------
	Message* msg = ABStudentInfoReq(getData());
	n = sendto(sockfd, msg->buf, msg->getPosition(), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (n < 0)
		error("ERROR send");
	//----------------recv-----------------------
	n = recv(sockfd, buffer, 255, 0);
		if (n < 0)
         error("ERROR reading from socket");
	cout << "%s\n"<<buffer;

    return 0;
}

void SocketA::stop(){
	//close(sockfd);
}

Message* SocketA::ABStudentInfoReq(StrABStudentInfoReq data){
	Message* msg = new Message(300);
	msg->putInt(data.msgId);
	msg->putInt(data.numStudents);
	for (int i = 0; i < data.numStudents; i++){
		msg->putInt(data.studentInfo[i].index);
		msg->putString(data.studentInfo[i].name);
		msg->putString(data.studentInfo[i].date);
		msg->putInt(data.studentInfo[i].id);
		msg->putInt(data.studentInfo[i].age);
	}
msg->putByte(0);
	return msg;
}

StrABStudentInfoReq SocketA::getData(){
	StrABStudentInfoReq data;
	data.msgId = 0;
	data.numStudents = 1;
	data.studentInfo[0].index = 1;
	sprintf(data.studentInfo[0].name, "Hung than thanh");
	sprintf(data.studentInfo[0].date, "3/9/2015");
	data.studentInfo[0].id = 1000;
	data.studentInfo[0].age = 24;
	return data;
}
