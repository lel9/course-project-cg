#include "gray_image.h"

GrayImage::GrayImage() :
    _data(nullptr)
{

}

GrayImage::GrayImage(int width, int height) :
    Image(width, height)
{
    _data = new uchar[_width*_height];
}

GrayImage::GrayImage(uchar *data, int width, int height) :
    Image(width, height), _data(data)
{

}

GrayImage::GrayImage(GrayImage &&rvalue) :
    _data(rvalue._data)
{
    rvalue._data = nullptr;
}

GrayImage::GrayImage(const GrayImage &rvalue) :
    Image::Image(rvalue)
{
    _data = new uchar[rvalue._width*rvalue._height];
    for (int i = 0; i < rvalue._width*rvalue._height; i++)
        _data[i] = rvalue._data[i];
}

void GrayImage::setPixel(uchar gray, int x, int y)
{
    _data[x*_width+y] = gray;
}

void GrayImage::setPixel(Rgb pixel, int x, int y)
{
    if (pixel.red() - pixel.green() - pixel.blue() != 0)
        _data[x*_width+y] = (pixel.red()*11+pixel.green()*16+pixel.blue()*5)/32;
    else
        _data[x*_width+y] = pixel.red();
}

Rgb GrayImage::pixel(int x, int y) const
{
    return Rgb(_data[x*_width+y], _data[x*_width+y], _data[x*_width+y]);
}

uchar GrayImage::intensity(int x, int y) const
{
    return _data[x*_width+y];
}

Image* GrayImage::piece(mPointI pos, int width, int height) const
{
    Image *img = new GrayImage(width, height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            img->setPixel(this->pixel(i+pos.y(), j+pos.x()), i, j);
    return img;
}

pixelArray GrayImage::pixelRow(int row) const
{
    pixelArray res(_width);
    if (row > _height-1 || row < 0)
        return res;   // а лучше exeption

    int offset = row*_width;
    for (int i = 0; i < _width; i++)
        res._data[i] = _data[offset + i];
    return res;
}

pixelArray GrayImage::pixelColumn(int col) const
{
    pixelArray res(_height);
    if (col > _width-1 || col < 0)
        return res;
    for (int i = 0; i < _height; i++)
        res._data[i] = _data[col + i*_width];
    return res;
}

void GrayImage::setPixelRow(int row, uchar *data)
{
    if (row > _height-1 || row < 0)
        return;

    int offset = row*_width;
    for (int i = 0; i < _width; i++)
        _data[offset + i] = data[i];
}

void GrayImage::setPixelColumn(int col, uchar *data)
{
    if (col > _width-1 || col < 0)
        return;

    for (int i = 0; i < _height; i++)
        _data[col + i*_width] = data[i];
}

Image* GrayImage::copy()
{
    uchar *data = new uchar[_width*_height];
    for (int i = 0; i < _width*_height; i++)
        data[i] = _data[i];
    GrayImage *img = new GrayImage(data, _width, _height);
    return img;
}

void GrayImage::clear()
{
    _width = _height = 0;
    delete _data;
    _data = nullptr;
}

GrayImage& GrayImage::operator=(GrayImage &&rvalue)
{
    _data = rvalue._data;
    _width = rvalue._width;
    _height = rvalue._height;

    rvalue._data = nullptr;
    rvalue._width = 0;
    rvalue._height = 0;

    return *this;
}

GrayImage &GrayImage::operator=(const GrayImage &rvalue)
{
    _width = rvalue._width;
    _height = rvalue._height;
    _data = new uchar[_width*_height];
    for (int i = 0; i < _width*_height; i++)
        _data[i] = rvalue._data[i];
    return *this;
}

