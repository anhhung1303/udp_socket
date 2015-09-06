#ifndef _SocketB_h_
#define _SocketB_h_

#include <string>
#include "DataStruct.h"
#include "Message.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 

class SocketB{
public:
	int sockfd, sock_rep;
	char buffer[PACKAGE_MAX_LEN];
	struct sockaddr_in serv_addr, cli_addr;
	int sizeAddr;

	SocketB(){};
	~SocketB(){};
    int start(int portno);
	void error(const char *msg);
	StrABStudentInfoReq* ABStudentInfoReq(Message* data);
	Message* handleABStudentInfoReq(Message* msg);
};
#endif // _socketB_h_
