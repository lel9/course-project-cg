#ifndef RECT_H
#define RECT_H

#include "point.h"

template <typename T>
class Rect
{
private:
    mPoint<T> _leftTop;
    int _width;
    int _height;
public:
    Rect() { }
    Rect(const mPoint<T> &leftTop, const int width, const int height) :
        _leftTop(leftTop), _width(width), _height(height) { }
    ~Rect() { }

    void setLeftTop(const mPoint<T> &leftTop) { _leftTop = leftTop; }
    void setWidth(const int width) { _width = width; }
    void setHeight(const int height) { _height = height; }

    mPoint<T> leftTop() const { return _leftTop; }
    int width() const { return _width; }
    int height() const { return _height; }
};

#endif // RECT_H
