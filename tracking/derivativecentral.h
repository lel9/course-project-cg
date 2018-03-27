#ifndef DERIVATIVECENTRAL_H
#define DERIVATIVECENTRAL_H

#include "derivative.h"

template <typename T>
class DerivativeCentral : public Derivative<T>
{
    typedef Derivative<T> B;

public:
    DerivativeCentral() = default;
    ~DerivativeCentral() = default;
    virtual Array<T> calculate() override
    {
        B::minSize = MIN(B::X.size(), B::Y.size());

        Array<T> result(B::minSize);
        if (B::minSize <= 0)
            return result;

        result[0] =  B::AccuracyL();
        for (int i = 1; i < B::minSize-1; i++)
            result[i] = B::Central(i);
        result[B::minSize-1] = B::AccuracyR();
        return result;
    }
};

template <typename T>
class DerivativeOneSide : public Derivative<T>
{
    typedef Derivative<T> B;

public:
    DerivativeOneSide() = default;
    ~DerivativeOneSide() = default;
    virtual Array<T> calculate() override
    {
        B::minSize = MIN(B::X.size(), B::Y.size());

        Array<T> result(B::minSize);
        if (B::minSize <= 0)
            return result;

        result[0] = B::OneSideL(0);
        for (int i = 1; i < B::minSize; i++)
            result[i] = B::OneSideR(i);
        return result;
    }
};

template <typename T>
class DerivativeRunge : public Derivative<T>
{
    typedef Derivative<T> B;

public:
    DerivativeRunge() = default;
    ~DerivativeRunge() = default;
    virtual Array<T> calculate() override
    {
        B::minSize = MIN(B::X.size(), B::Y.size());

        Array<T> result(B::minSize);
        if (B::minSize <= 0)
            return result;

        result[0] = B::AccuracyL();

        if (B::minSize <= 1)
            return result;

        result[1] = B::Central(1);
        for (int i = 2; i < B::minSize-2; i++)
            result[i] = B::Central(i, 1) + (B::Central(i, 1) - B::Central(i, 2)) / 3.0;

        if (B::minSize <= 2)
            return result;

        result[B::minSize-2] = B::Central(B::minSize-2);
        result[B::minSize-1] = B::AccuracyR();
        return result;
    }
};
#endif // DERIVATIVECENTRAL_H
