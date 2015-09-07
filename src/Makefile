CC = g++
CFLAGS = -c
DEPS = DataStruct.h socketA.h socketB.h Message.h ListStudent.h

all: socketA socketB

socketA: socketA.o  Message.o ListStudent.o
	$(CC) socketA.o  Message.o ListStudent.o -o socketA

socketB: socketB.o Message.o ListStudent.o
	$(CC) socketB.o Message.o ListStudent.o -o socketB

socketA.o: socketA.cpp
	$(CC) $(CFLAGS) socketA.cpp

socketB.o: socketB.cpp
	$(CC) $(CFLAGS) socketB.cpp

Message.o: Message.cpp
	$(CC) $(CFLAGS) Message.cpp

ListStudent.o: ListStudent.cpp
	$(CC) $(CFLAGS) ListStudent.cpp

clean:
	rm -rf *o socketA socketB
