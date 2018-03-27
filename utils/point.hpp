#include "point.h"

template <typename T>
mPoint<T>& mPoint<T>::operator =(const mPoint<T> &src)
{
    _x = (T) src.x();
    _y = (T) src.y();
    return *this;
}

template <typename T>
mPoint<T>& mPoint<T>::operator +=(const mPoint<T> &rvalue)
{
    _x += rvalue.x();
    _y += rvalue.y();
    return *this;
}

template <typename T>
mPoint<T>& mPoint<T>::operator -=(const mPoint<T> &rvalue)
{
    _x -= rvalue.x();
    _y -= rvalue.y();
    return *this;
}

template <typename T>
mPoint<T> mPoint<T>::operator +(const mPoint<T> &rvalue) const
{
    return mPoint<T>(_x + rvalue.x(), _y + rvalue.y());
}

template <typename T>
mPoint<T> mPoint<T>::operator -(const mPoint<T> &rvalue) const
{
    return mPoint<T>(_x - rvalue.x(), _y - rvalue.y());
}
