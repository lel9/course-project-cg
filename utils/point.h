#ifndef mPoint_H
#define mPoint_H

template <typename T>
class mPoint
{
private:
    T _x;
    T _y;

public:
    mPoint() = default;
    mPoint(const T &x, const T &y) : _x(x), _y(y) { }
    template <typename S>
    mPoint(const mPoint<S> &src) : _x( (T) src.x()), _y( (T) src.y()) { }
    ~mPoint() = default;

    T x() const { return _x; }
    T y() const { return _y; }
    void setX(T x) { _x = x; }
    void setY(T y) { _y = y; }

    mPoint<T>& operator = (const mPoint<T> &src);
    mPoint<T>& operator +=(const mPoint<T> &rvalue);
    mPoint<T>& operator -=(const mPoint<T> &rvalue);
    mPoint<T>  operator + (const mPoint<T> &rvalue) const;
    mPoint<T>  operator - (const mPoint<T> &rvalue) const;
};

typedef mPoint<float> mPointF;
typedef mPoint<int> mPointI;

#include "point.hpp"

#endif // mPoint_H
