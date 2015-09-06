CC = g++
CFLAGS = -c
DEPS = DataStruct.h socketA.h socketB.h Message.h

all: socketA socketB

socketA: socketA.o  Message.o
	$(CC) socketA.o  Message.o -o socketA

socketB: socketB.o Message.o
	$(CC) socketB.o Message.o -o socketB

socketA.o: socketA.cpp
	$(CC) $(CFLAGS) socketA.cpp

socketB.o: socketB.cpp
	$(CC) $(CFLAGS) socketB.cpp

Message.o: Message.cpp
	$(CC) $(CFLAGS) Message.cpp

clean:
	rm -rf *o socketA socketB
