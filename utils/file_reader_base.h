#ifndef FILEREADERBASE_H
#define FILEREADERBASE_H

#include <string>

class BaseFileReader
{
public:
    virtual ~BaseFileReader() { }

    virtual int readInt(bool &eof) = 0;
    virtual float readFloat(bool &eof) = 0;
    virtual char readChar(bool &eof) = 0;
    virtual std::string readWord(bool &eof) = 0;
};

#endif // FILEREADERBASE_H
