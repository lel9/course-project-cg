#include "filereader.h"
//#include "exceptions.h"
//using namespace std;

FileReader::FileReader(const char *filename)
{
    open(filename);
}

void FileReader::open(const char* filename)
{
    file = fopen(filename, "r");
    //if (!file)
    //    throw FileOpenException("open");
}
void FileReader::close()
{
    fclose(file);
    file = nullptr;
}

int FileReader::readInt(bool &eof)
{
    int num;
    if (fscanf(file, "%d", &num) != 1)
        eof = true;
    else
        eof = false;
    return num;
}

float FileReader::readFloat(bool &eof)
{
    float num;
    if (fscanf(file, "%f", &num) != 1)
        eof = true;
    else
        eof = false;
    return num;
}

char FileReader::readChar(bool &eof)
{
    char ch;
    if (fscanf(file, "%c", &ch) != 1)
        eof = true;
    else
        eof = false;
    return ch;
}

std::string FileReader::readWord(bool &eof)
{
    std::string str;
    char c = readChar(eof);
    while (!eof && c != '\t' && c != ' ' && c != '\n')
    {
        str.push_back(c);
        c = readChar(eof);
    }
    str.push_back('\0');
    return str;
}

FileReader::~FileReader()
{
    if (file)
        close();
}
