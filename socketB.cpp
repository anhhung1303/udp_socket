#include "socketB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void SocketB::error(const char *msg)
{
    cout << msg;
    //exit(1);
}

int SocketB::start(int portno)
{
	//socklen_t clilen;

     int n;
	 sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	 if (sockfd <0)
		 error("ERROR INVALID_SOCKET");
     //bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	cout << "bind:\n";
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
	cout << "bind....\n";
	cout <<"wait:\n";
	 n = recv(sockfd, buffer, 255, 0);
	 if (n < 0) error("ERROR reading from socket");
	 Message* msg = new Message(buffer, n);
	 if (msg->getInt() == 0){
		 ABStudentInfoReq(msg);
		 //delete msg;
		 //cout <<"Here is the message: %s\n"<< buffer;
		error("rep");
		 Message* msg = new Message();
		 msg->putInt(0);
		 //msg->putInt(0);
		 n = send(newsockfd, msg->buf, msg->getPosition(), 0);
		error("rep....");
	 }
     //close(newsockfd);
     //close(sockfd);
     return 0;
}


StrABStudentInfoReq* SocketB::ABStudentInfoReq(Message* msg){
	int n = msg->getInt();
	cout <<""<< n <<"\n";
	for (int i = 0; i < n; i++){
		error("Fuck error....");
		cout <<msg->getInt();
		cout <<"    " << msg->getString().c_str();
		cout <<"    " << msg->getString().c_str();
		cout <<"    " << msg->getInt();
		cout <<"    " << msg->getInt();
		cout <<"\n";
		error("Fuck error....");
	}
	return NULL;
}
