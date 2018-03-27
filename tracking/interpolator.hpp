#include "interpolator.h"

#include <QtMath>
#include <QGenericMatrix>

#include "gauss.h"

double f(double x, int n)
{
    return qPow(x, n);
}

template <typename T>
T Interpolator<T>::polynom(T x)
{
    T res = 0;
    for (int i = 0; i < coefs.size(); i++)
    {
        res += coefs[i]*qPow(x, i);
        //printf("%.5e ", coef[i]);
    }
    return res;
}

template <typename T>
Matrix<T> Interpolator<T>::calcCoefficients()
{
    int n = s+1;

    Matrix<T> coefficients(n, n+1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            coefficients(i,j) = 0;
            for (int k = 0; k < M::minSize; k++)
                coefficients(i,j) += f(M::X[k], j)*f(M::X[k], i);
        }

        coefficients(i,n) = 0;
        for (int k = 0; k < M::minSize; k++)
            coefficients(i,n) += M::Y[k]*f(M::X[k], i);
    }

    return coefficients;
}

template <typename T>
Array<T> Interpolator<T>::calculate()
{
    M::minSize = MIN(M::X.size(), M::Y.size());

    Matrix<T> coefficients = calcCoefficients();
    Gauss<T> g(coefficients);
    coefs = g.calculate();

    Array<T> result(M::minSize);
    for (int i = 0; i < M::minSize; i++)
        result[i] = polynom(M::X[i]);

    return result;
}























//#include "interpolator.h"
//#include "math.h"

//// Возвращает таблицу для вычисления полинома
//template <typename T>
//Array<T> Interpolator<T>::GetPolinomeTable(const Array<T> &ConfigTableX, const Array<T> &ConfigTableY)
//{
//    int n = s+1;
//    Array<T> PolinomeTableY(ConfigTableY);

//    double dx, dy;
//    for (int i = 1; i < n; i++)
//    {
//        dx = ConfigTableX[0]-ConfigTableX[i];
//        for (int j = n-1; j >= i; j--)
//        {
//            dy = PolinomeTableY[j-1]-PolinomeTableY[j];
//            PolinomeTableY[j] = dy/dx;
//        }
//    };

//    return PolinomeTableY;
//}

//// Вычисление y с помощью полинома Ньютона
//template <typename T>
//T Interpolator<T>::Polinome(T x, const Array<T> &PTX, const Array<T> &PTY)
//{
//    T y = PTY[0];
//    T tmp = 1;
//    for (unsigned int i = 0; i < s; i++)
//    {
//        tmp *= x-PTX[i];
//        y += tmp*PTY[i+1];
//    }
//    return y;
//}

//// Интерполяция
//template <typename T>
//Array<T> Interpolator<T>::calculate()
//{
//    M::minSize = MIN(M::X.size(), M::Y.size());
//    int size = (M::minSize-1)*point_count + M::minSize;
//    Array<T> result(size);

//    int k = 0;
//    for (int i = 0; i < M::minSize-1; i++)
//    {
//        //result[k++] = M::Y[i];
//        double h = (double)(M::X[i+1]-M::X[i])/(point_count+1);
//        double x = M::X[i];

//        for (int j = 0; j < (int)point_count+1; j++)
//        {
//            int pos = i;
//            if (pos-floor((s+1)/2.0)+1<0)
//                pos = 0;
//            else if (pos+ceil((s+1)/2.0) > M::minSize-1)
//                pos = M::minSize-(s+1);
//            else
//                pos -= floor((s+1)/2.0)-1;

//            Array<T> ConfigTableX, ConfigTableY;
//            ConfigTableX = M::X.slice(pos, s+1);
//            ConfigTableY = M::Y.slice(pos, s+1);

//            // таблица для вычисления полинома
//            Array<T> PolinomeTable = GetPolinomeTable(ConfigTableX, ConfigTableY);
//            result[k++] = Polinome(x, ConfigTableX, PolinomeTable);
//            x += h;
//        }
//    }
//    result[k] = M::Y[M::minSize-1];

//    return result;
//}
