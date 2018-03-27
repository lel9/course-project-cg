#include "image.h"

Image::Image() :
    _width(0), _height(0)
{

}

Image::Image(int width, int height) :
    _width(width), _height(height)
{

}

Image::Image(Image &&rvalue) :
    _width(rvalue._width), _height(rvalue._height)
{
    rvalue._width = 0;
    rvalue._height = 0;
}

Image::Image(const Image &rvalue) :
    _width(rvalue._width), _height(rvalue._height)
{

}

