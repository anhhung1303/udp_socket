#ifndef _MESSAGE_BUFFER_H_
#define _MESSAGE_BUFFER_H_
#include <stdio.h>
#include <string>

using namespace std;
class Message{
private:
    int capacity;
    int limit;
    int pos;
public:
    char* buf;
    Message();
    Message(int capacity);
    Message(const char* data, int size);
    ~Message();
    Message* putByte(int b);
    Message* putBytes(const char* bytes, int size);
    Message* putByteArray(const char* bytes, int size);
    Message* putShort(int v);
    Message* putInt(int v);
    Message* putLong(long long v);
    Message* putString(string str);

    char* getBytes(int size);
    char getByte();
    short getShort();
    int getUnsignedShort();
    int getInt();
    long long getLong();
    bool getBool();
    long getDouble();
    char* getCharArray(int& size);
    string getString();
    inline int getCapacity() {
        return capacity;
    };
    inline int getLimit() {
        return limit;
    };
    inline int getPosition() {
        return pos;
    }
    inline void rewind() {
        pos = 0;
    };
};
#endif
