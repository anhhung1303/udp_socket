#ifndef _SocketA_h_
#define _SocketA_h_

#include <string>
#include "DataStruct.h"
#include "Message.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> 

using namespace std;
class SocketA{
private:
    int sockfd, sock_recv, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

public:
    SocketA(){};
    ~SocketA(){};
    int start(string ipAdr, int portno);
    void stop();
    void error(const char *msg);
    Message* ABStudentInfoReq(StrABStudentInfoReq data);
    StrABStudentInfoReq getData();
    Message* ABShowAllReq();
    Message* ABBorn1990Req();
    Message* ABSortIDReq();
    Message* ABInsertNewReq(StrABInsertNewReq data);
    StrABInsertNewReq getInsertStudentData();
    void initRecv(int portno);
    void handleRespond();
    void printToScreen(Message* msg);
};
#endif // _socketA_h_
