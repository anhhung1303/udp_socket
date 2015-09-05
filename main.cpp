#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "socketA.h"
#include "socketB.h"
#include "handle.h"

using namespace std;


int main(int argc, const char * argv[])
{
	int i;
	cout << "1. server\n";
	cout << "0. client\n";
	cin >> i;
	if (i == 1)
		(new SocketB())->start(8080);
	else
		(new SocketA())->start("127.0.0.1", 8080);

	cin >> i;
	switch(i) {
		case 1:
			handleFirstCase();
			break;
		case 2:
			handeSecondCase();
			break;
		case 3:
			handlelThirdCase();
			break;
		case 4:
			handleFourthCase();
			break;
		case 5:
			handleFifthCase();
			break;
	}
}
