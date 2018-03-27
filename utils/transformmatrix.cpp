#include "transformmatrix.h"

TransformMatrix::TransformMatrix() :
    Matrix(size, size)
{
}

TransformMatrix::TransformMatrix(double matrix[size][size]) :
    Matrix(size, size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            data[i][j] = matrix[i][j];
}

TransformMatrix::TransformMatrix(double i11, double i22, double i33, double i44) :
    Matrix(size, size)
{
     for (int i = 0; i < size; i++)
         for (int j = 0; j < size; j++)
             if (i != j)
                 data[i][j] = 0;
     data[0][0] = i11;
     data[1][1] = i22;
     data[2][2] = i33;
     data[3][3] = i44;

}

TransformMatrix::TransformMatrix(const TransformMatrix &origin) :
    Matrix(origin)
{
}

TransformMatrix::TransformMatrix(TransformMatrix &&origin) :
    Matrix(origin)
{

}

TransformMatrix& TransformMatrix::operator=(const TransformMatrix &origin)
{
    Matrix::operator =(origin);
    return *this;
}

TransformMatrix &TransformMatrix::operator=(TransformMatrix &&origin)
{
    Matrix::operator =(origin);
    return *this;
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &other) const
{
    TransformMatrix result;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < other.size; j++)
            for(int k = 0; k < size; k++)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}

TransformMatrix::~TransformMatrix()
{
}
