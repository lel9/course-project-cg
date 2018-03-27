#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "mathtable.h"

template <typename T>
class Interpolator : public MathTable<T>
{
    typedef MathTable<T> M;

public:
    Interpolator(int order) : s(order) { }
    virtual ~Interpolator() = default;
    virtual Array<T> calculate() override;

    Array<T> getCoefs() const
    {
        return coefs;
    }

protected:
    Matrix<T> calcCoefficients();
    T polynom(T x);

protected:
    int s;
    Array<T> coefs;
};

#include "interpolator.hpp"

#endif // INTERPOLATOR_H
