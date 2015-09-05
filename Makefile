CC = g++
CFLAGS = -c
DEPS = DataStruct.h socketA.h socketB.h Message.h
all: socket

socket: main.o socketA.o socketB.o Message.o  handle.o
	$(CC) main.o socketA.o socketB.o Message.o handle.o -o socket

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

socketA.o: socketA.cpp
	$(CC) $(CFLAGS) socketA.cpp

socketB.o: socketB.cpp
	$(CC) $(CFLAGS) socketB.cpp

Message.o: Message.cpp
	$(CC) $(CFLAGS) Message.cpp

handle.o: handle.cpp
	$(CC) $(CFLAGS) handle.cpp

clean:
	rm -rf *o socket
