#ifndef TransformMatrix_H
#define TransformMatrix_H

#include "matrix.h"

class TransformMatrix : public Matrix<double>
{
private:
    static const int size = 4;

public:
    using Matrix::Matrix;
    TransformMatrix();
    TransformMatrix(double matrix[size][size]);
    TransformMatrix(double i11, double i22, double i33, double i44);
    TransformMatrix(const TransformMatrix &origin);
    TransformMatrix(TransformMatrix &&origin);
    ~TransformMatrix();

    TransformMatrix &operator=(const TransformMatrix &origin);
    TransformMatrix &operator=(TransformMatrix &&origin);
    TransformMatrix operator*(const TransformMatrix &origin) const;
};

#endif // TransformMatrix_H
