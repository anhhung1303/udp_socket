#ifndef _DataStruct_h_
#define _DataStruct_h_

#define PACKAGE_MAX_LEN  512

typedef struct _StrStudentInfo{
	unsigned int index;
	char name[64];
	char date[16];
	unsigned int id;
	unsigned int age;
} StrStudentInfo;

#define A_B_STUDENT_INFO_REQ_SIG 0
typedef struct _StrABStudentInfoReq{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrABStudentInfoReq;

#define B_A_STUDENT_INFO_RES_SIG 1
typedef struct _StrBAStudentInfoRes{
	int msgId;
} StrBAStudentInfoRes;

#define A_B_BORN_1990_REQ_SIG 2
typedef struct _StrABBorn1990Req{
	int msgId;
} StrABBorn1990Req;

#define B_A_BORN_1990_RES_SIG 3
typedef struct _StrBABorn1990Res{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBABorn1990Res;

#define A_B_SHOW_ALL_REQ_SIG 4
typedef struct _StrABShowAllReq{
	int msgId;
} StrABShowAllReq;

#define B_A_SHOW_ALL_RES_SIG 5
typedef struct _StrBAShowAllRes{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBAShowAllRes;

#define A_B_SORT_ID_REQ_SIG 6
typedef struct _StrABSortIDReq{
	int msgId;
} StrABSortIDReq;

#define B_A_SORT_ID_RES_SIG 7
typedef struct _StrBASortIDRes{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBASortIDRes;

#define A_B_INSERT_NEW_REQ_SIG 8
typedef struct _StrABInsertNewReq{
	int msgId;
	StrStudentInfo studentInfo; //Array student info
} StrABInsertNewReq;

#define B_A_INSERT_NEW_RES_SIG 9
typedef struct _StrBASortIDRes1{
	int msgId;
	int numStudents; //Student number in array
	StrStudentInfo studentInfo[32]; //Array student info
} StrBASortIDRes1;
#endif // _DataStruct_h_
