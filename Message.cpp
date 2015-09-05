#include "Message.h"
#include <cstring>
using namespace std;
Message::Message(){
	//	capacity = 1000;
	pos = 0;
	//	buf = new char[capacity];
	buf = NULL;
}
Message::Message(int capacity){
	pos = 0;
	this->capacity = capacity;
	buf = new char[capacity];
}
Message::Message(const char* data, int size){
	pos = 0;
	capacity = size;
	limit = size;
	buf = new char[capacity];
	memcpy(buf, data, size);
}
Message::~Message(){
	delete[]buf;
};
Message* Message::putByte(int b){
	buf[pos++] = (char)b;
	limit = (pos == capacity ? pos : pos + 1);
	return this;
}
Message* Message::putByteArray(const char* bytes, int size){
	putShort(size);
	putBytes(bytes, size);
	return this;
}

Message* Message::putBytes(const char* bytes, int size){
	for (int i = 0; i < size; i++) {
		putByte(bytes[i]);
	}
	return this;
}

Message* Message::putShort(int v) {
	putByte((v >> 8) & 0xFF);
	putByte((v >> 0) & 0xFF);
	return this;
}
Message* Message::putInt(int v) {
	putByte((v >> 24) & 0xff);
	putByte((v >> 16) & 0xff);
	putByte((v >> 8) & 0xff);
	putByte((v >> 0) & 0xff);
	return this;
}
Message* Message::putLong(long long v) {
	putByte(v >> 56);
	putByte(v >> 48);
	putByte(v >> 40);
	putByte(v >> 32);
	putByte(v >> 24);
	putByte(v >> 16);
	putByte(v >> 8);
	putByte(v >> 0);
	return this;
}
Message* Message::putString(string str) {
	int size = str.size();
	putByteArray(str.c_str(), size);
	return this;
}
char Message::getByte() {
	char b = buf[pos++];
	return b;
}

bool Message::getBool() {
	char b = buf[pos++];
	if (b == 1)
		return true;
	else
		return false;
}
char* Message::getBytes(int size) {
	char *bytes = new char[size];
	for (int i = 0; i < size; i++) {
		bytes[i] = getByte();
	}
	return bytes;
}
short Message::getShort() {
	if (pos + 2 > limit) {
		return 0;
	}
	return (short)((getByte() << 8) + (getByte() & 255));
}
int Message::getUnsignedShort() {
	int a = (getByte() & 255) << 8;
	int b = (getByte() & 255) << 0;
	return a + b;
}
int Message::getInt() {
	return ((getByte() & 255) << 24) +
		((getByte() & 255) << 16) +
		((getByte() & 255) << 8) +
		((getByte() & 255) << 0);
}

long long Message::getLong(){
	return ((long long)(getByte() & 255) << 56) +
		((long long)(getByte() & 255) << 48) +
		((long long)(getByte() & 255) << 40) +
		((long long)(getByte() & 255) << 32) +
		((long long)(getByte() & 255) << 24) +
		((long long)(getByte() & 255) << 16) +
		((long long)(getByte() & 255) << 8) +
		((long long)(getByte() & 255) << 0);
}

char* Message::getCharArray(int& size) {
	size = getUnsignedShort();
	return getBytes(size);
}
string Message::getString(){
	int size = 0;
	char* out = getCharArray(size);
	std::string str(out, size);
	return str;
}
