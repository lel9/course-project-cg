#ifndef IMAGE_H
#define IMAGE_H

#include "rgb.h"

struct pixelArray
{
    pixelArray(int n) : len(n) { _data = new uchar[n]; }
    ~pixelArray() { delete[] _data; }

    uchar *_data;
    int len;
};

#include "utils/point.h"

class Image
{
protected:
    int _width;
    int _height;
public:
    Image();
    Image(int width, int height);
    Image(Image &&rvalue);
    Image(const Image &rvalue);
    virtual ~Image() = default;

    int width() const  { return _width; }
    int height() const { return _height; }

    virtual void setPixel(uchar gray, int x, int y) = 0;
    virtual void setPixel(Rgb pixel, int x, int y) = 0;
    virtual Rgb pixel(int x, int y) const = 0;
    virtual uchar intensity(int x, int y) const = 0;
    virtual Image* piece(mPointI pos, int width, int height) const = 0;
    virtual pixelArray pixelRow(int row) const = 0;
    virtual pixelArray pixelColumn(int col) const = 0;

    virtual void setPixelRow(int row, uchar *data) = 0;
    virtual void setPixelColumn(int col, uchar *data) = 0;

    virtual Image* copy() = 0;
    virtual void clear() = 0;

};

#endif // IMAGE_H
