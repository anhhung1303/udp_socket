#ifndef _DataStruct_h_
#define _DataStruct_h_

#include <string.h>


typedef struct _StrStudentInfo {
	unsigned int index;
	char name[64];
	char date[16];
	unsigned int id;
	unsigned int age;
	_StrStudentInfo* next;
} StrStudentInfo;

//A_B_STUDENT_INFO_REQ_SIG: msgId = 0
typedef struct _StrABStudentInfoReq{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrABStudentInfoReq;

//B_A_STUDENT_INFO_RES_SIG: msgId = 1
typedef struct _StrBAStudentInfoRes{
	int msgId;
} StrBAStudentInfoRes;

//A_B_BORN_1990_REQ_SIG: msgId = 2
typedef struct _StrABBorn1990Req{
	int msgId;
} StrABBorn1990Req;

//B_A_BORN_1990_RES_SIG: msgId=3
typedef struct _StrBABorn1990Res{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBABorn1990Res;

//A_B_SHOW_ALL_REQ_SIG: msgId=4
typedef struct _StrABShowAllReq{
	int msgId;
} StrABShowAllReq;

//B_A_SHOW_ALL_RES_SIG: msgId=5
typedef struct _StrBAShowAllRes{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBAShowAllRes;

//A_B_SORT_ID_REQ_SIG: msgId=6
typedef struct _StrABSortIDReq{
	int msgId;
} StrABSortIDReq;

//B_A_SORT_ID_RES_SIG: msgId=7
typedef struct _StrBASortIDRes{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBASortIDRes;

//A_B_INSERT_NEW_REQ_SIG: msgId=8
typedef struct _StrABInsertNewReq{
	int msgId;
	StrStudentInfo studentInfo; //Array student info
} StrABInsertNewReq;

//B_A_INSERT_NEW_RES_SIG: msgId=9
typedef struct _StrBASortIDRes1{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBASortIDRes1;
#endif // _DataStruct_h_
