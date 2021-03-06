#include "../include/socketB.h"
#include "../include/ListStudent.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

SocketB::SocketB(){
    listStudent = new ListStudent();
}

void SocketB::error(const char *msg){
    cout << msg <<"\n";
    exit(1);
}

int SocketB::start(int portno){
    int n;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd <0)
        error("ERROR INVALID_SOCKET");
     //bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
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
                cout << "A_B_STUDENT_INFO_REQ_SIG" << endl;
                msg1 = handleABStudentInfoReq(msg);
                break;
            }
            case A_B_SHOW_ALL_REQ_SIG: {
                cout << "A_B_SHOW_ALL_REQ_SIG" << endl;
                msg1 = handleABShowAllReq();
                break;
            }
            case A_B_BORN_1990_REQ_SIG: {
                cout << "A_B_BORN_1990_REQ_SIG" << endl;
                msg1 = handleABBorn1990Req();
                break;
            }
            case A_B_SORT_ID_REQ_SIG: {
                cout << "A_B_SORT_ID_REQ_SIG" << endl;
                msg1 = handleABSortIDReq();
                break;
            }
            case A_B_INSERT_NEW_REQ_SIG: {
                cout << "A_B_INSERT_NEW_REQ_SIG" << endl;
                msg1 = handleABInsertNewReq(msg);
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
    unsigned int index;
    string name;
    string date;
    unsigned int id;
    unsigned int age;
    for (int i = 0; i < n; i++){
        index = msg -> getInt();
        name = msg -> getString().c_str();
        date = msg -> getString().c_str();
        id = msg -> getInt();
        age = msg -> getInt();
        StrStudentInfo* student = new StrStudentInfo();
        student->index = index;
        copy(name.begin(), name.end(), student->name);
        student -> name[name.size()] = '\0';
        copy(date.begin(), date.end(), student->date);
        student->date[date.size()] = '\0';
        student->id = id;
        student->age = age;
        listStudent -> addStudent(student);
    }
    return NULL;
}

Message* SocketB::handleABStudentInfoReq(Message* msg){
    ABStudentInfoReq(msg);
    Message* msg1 = new Message(4);
    msg1->putInt(B_A_STUDENT_INFO_RES_SIG);
    return msg1;
}

Message* SocketB::handleABShowAllReq(){
    Message* msg = new Message(PACKAGE_MAX_LEN);
    msg->putInt(B_A_SHOW_ALL_RES_SIG);
    msg->putInt(listStudent->getNumStudents());
    putDataToMessage(msg, listStudent, listStudent->getNumStudents());
    return msg;
}

Message* SocketB::handleABBorn1990Req(){
    Message* msg = new Message(PACKAGE_MAX_LEN);
    ListStudent* filterered1990List = listStudent->filterStudent();
    msg->putInt(B_A_BORN_1990_RES_SIG);
    msg->putInt(filterered1990List->getNumStudents());
    putDataToMessage(msg, filterered1990List, filterered1990List->getNumStudents());
    return msg;
}

Message* SocketB::handleABSortIDReq(){
    Message* msg = new Message(PACKAGE_MAX_LEN);
    listStudent->sortStudent();
    StrStudentInfo* curr = listStudent->getFirst();
    msg->putInt(B_A_SORT_ID_RES_SIG);
    msg->putInt(listStudent->getNumStudents());
    putDataToMessage(msg, listStudent, listStudent->getNumStudents());
    return msg;
}

Message* SocketB::handleABInsertNewReq(Message* msg){
    unsigned int index = msg->getInt();
    string name = msg->getString();
    string date = msg->getString();
    unsigned int id = msg->getInt();
    unsigned int age = msg->getInt();

    StrStudentInfo* student = new StrStudentInfo();
    student->index = index;
    copy(name.begin(), name.end(), student->name);
    student->name[name.size()] = '\0';
    copy(date.begin(), date.end(), student->date);
    student->date[date.size()] = '\0';
    student->id = id;
    student->age = age;
    student->next = NULL;
    listStudent->addStudent(student);

    Message* msg1 = new Message(PACKAGE_MAX_LEN);
    msg1->putInt(B_A_INSERT_NEW_RES_SIG);
    msg1->putInt(listStudent->getNumStudents());
    putDataToMessage(msg1, listStudent, listStudent->getNumStudents());
    return msg1;
}

void SocketB::putDataToMessage(Message* msg, ListStudent* list, int n){
    StrStudentInfo* curr = list->getFirst();
    for(int i = 0; i < n; i++){
        msg->putInt(curr->index);
        msg->putString(curr->name);
        msg->putString(curr->date);
        msg->putInt(curr->id);
        msg->putInt(curr->age);
        curr = curr->next;
    }
}

int main(int argc, char const *argv[]){
    (new SocketB())->start(8080);
    return 0;
}
