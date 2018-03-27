#ifndef FILEREADER_H
#define FILEREADER_H

#include "file_reader_base.h"

#include <stdio.h>

class FileReader : public BaseFileReader
{
protected:
    FILE *file;

public:
    FileReader(const char *filename);
    ~FileReader();

    virtual int readInt(bool &f) override;
    virtual float readFloat(bool &f) override;
    virtual char readChar(bool &f) override;
    virtual std::string readWord(bool &eof) override;

protected:
    void open(const char *filename);
    void close();
};

#endif // FILEREADER_H
