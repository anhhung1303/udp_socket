#include "../include/socketB.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

void SocketB::error(const char *msg){
    cout << msg <<"\n";
    //exit(1);
}

int SocketB::start(int portno){
	//socklen_t clilen;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd <0)
		error("ERROR INVALID_SOCKET");
     //bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	while(true){
		struct sockaddr_storage recv_sa;
		socklen_t recv_sa_len;
		n = recvfrom(sockfd, buffer, PACKAGE_MAX_LEN-1, 0, (struct sockaddr *)&recv_sa, &recv_sa_len);
		if (n < 0) error("ERROR reading from socket");

		char host[NI_MAXHOST];
		getnameinfo((struct sockaddr *)&recv_sa, recv_sa_len, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
		sock_rep = socket(AF_INET, SOCK_DGRAM, 0);
		if (sock_rep <0)
			error("ERROR INVALID_SOCKET");
		struct sockaddr_in sender;
		sender.sin_family = AF_INET;
		string sIP = host;
		sender.sin_addr.s_addr = inet_addr(sIP.c_str());
		sender.sin_port = htons(portno+1);

		Message* msg = new Message(buffer, n);
		int msgID = msg->getInt();
		Message* msg1 = NULL;
		switch(msgID){
			case A_B_STUDENT_INFO_REQ_SIG: {
				msg1 = handleABStudentInfoReq(msg);
				
				break;
			}
		};

		if(msg1){
			n = sendto(sock_rep, msg1->buf, msg1->getPosition(), 0, (struct sockaddr *) &sender, sizeof(sender));
			delete msg1;
		}
		delete msg;
		close(sock_rep);
	}
     //close(sockfd);
     return 0;
}

StrABStudentInfoReq* SocketB::ABStudentInfoReq(Message* msg){
	int n = msg->getInt();
	cout <<""<< n <<"\n";
	for (int i = 0; i < n; i++){
		cout <<msg->getInt();
		cout << "\t\t" << msg->getString().c_str();
		cout << "\t\t" << msg->getString().c_str();
		cout << "\t\t" << msg->getInt()<< " " << msg->getPosition();
		cout << "\t\t" << msg->getInt()<< " " << msg->getPosition();
		cout << "\n";
	}
	return NULL;
}

Message* SocketB::handleABStudentInfoReq(Message* msg){
	ABStudentInfoReq(msg);
	Message* msg1 = new Message(4);
	msg1->putInt(0);
	return msg1;
}

int main(int argc, char const *argv[]){
	(new SocketB())->start(8080);
	return 0;
}