#ifndef GAUSS_H
#define GAUSS_H

#include "utils/matrix.h"

template <typename T>
class Gauss
{
private:
    Matrix<T> _matrix;

public:
    Gauss(const Matrix<T> &matrix) : _matrix(matrix) { }

    Array<T> calculate()
    {
        int n = _matrix.rowCount();
        Array<T> result(n);
        triangular_matrix();
        for (int i = n - 1; i >= 0; i--)
        {
            T x = _matrix(i,n);
            for (int j = i + 1; j < n; j++)
                x -= _matrix(i,j)*result[j];
            result[i] = x;
        }
        return result;
    }

protected:
    void triangular_matrix()
    {
        int n = _matrix.rowCount();
        for (int i = 0; i < n; i++)
        {
            _matrix.divideRow(i, _matrix(i,i));
            for (int j = i + 1; j < n; j++)
                _matrix.addRow(j, i, -_matrix(j,i));
        }
    }
};

#endif // GAUSS_H
