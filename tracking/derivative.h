#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include "mathtable.h"

template <typename T>
class Derivative : public MathTable<T>
{
    typedef MathTable<T> M;

public:
    Derivative() { }
    virtual ~Derivative() = default;
    virtual Array<T> calculate2()
    {
        M::minSize = MIN(M::X.size(), M::Y.size());

        Array<T> result(M::minSize);
        if (M::minSize <= 0)
            return result;

        result[0] =  AccuracyL();
        for (int i = 1; i < M::minSize-1; i++)
            result[i] = (M::Y[i+1]-2*M::Y[i]+M::Y[i-1]) /
                    ((M::X[1]-M::X[0])*(M::X[1]-M::X[0]));
        result[M::minSize-1] = AccuracyR();
        return result;
    }
protected:
    double OneSideL(int pos, int h = 1)
    {
        if (pos + h > M::minSize)
        {
            if (pos < M::minSize)
                return M::Y[pos]/h;
            else
                return 0;
        }
        return (M::Y[pos+h]-M::Y[pos])/(M::X[pos+h]-M::X[pos]);
    }

    double OneSideR(int pos, int h = 1)
    {
        if (pos - h < 0)
        {
            if (pos >= 0)
                return M::Y[pos]/h;
            else
                return 0;
        }
        return (M::Y[pos]-M::Y[pos-h])/(M::X[pos]-M::X[pos-h]);
    }

    double Central(int pos, int h = 1)
    {
        if (pos - h < 0)
        {
            if (pos + h > M::minSize)
                return 0;
            else
                return OneSideL(pos);
        }
        else if (pos + h > M::minSize)
                return OneSideR(pos);

        return (M::Y[pos+h]-M::Y[pos-h])/(M::X[pos+h]-M::X[pos-h]);
    }

    double AccuracyL()
    {
        if (M::minSize < 3)
            return OneSideL(0);
        return (-3*M::Y[0]+4*M::Y[1]-M::Y[2])/(M::X[2]-M::X[0]);
    }

    double AccuracyR()
    {
        if (M::minSize < 3)
            return OneSideR(M::minSize-1);
        return (3*M::Y[M::minSize-1]-4*M::Y[M::minSize-2]+M::Y[M::minSize-3])/
                (M::X[M::minSize-1]-M::X[M::minSize-3]);
    }
};

#endif // DERIVATIVE_H
