#ifndef MATHTABLE_H
#define MATHTABLE_H

#include "utils/matrix.h"
#define MIN(x,y) ((x) > (y) ? (y) : (x))

template <typename T>
class MathTable
{
public:
    MathTable() { }
    virtual ~MathTable() { }
    virtual Array<T> calculate() = 0;
    virtual void setX(const Array<T> &x) { X = x; }
    virtual void setY(const Array<T> &y) { Y = y;}
    virtual void setSize(int N) { minSize = N; }

protected:
    Array<T> X;
    Array<T> Y;
    int minSize;
};

#endif // MATHTABLE_H
