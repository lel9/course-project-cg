#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include "objects/image.h"
#include "utils/matrix.h"

class GaussianBlur
{
public:
    GaussianBlur();
    GaussianBlur(int sigma, double size);
    ~GaussianBlur();

    void updateKernel(double sigma, int size);
    void blur(Image *img);

    double sigma() { return _sigma; }
    int kernelSize() { return _size; }

private:
    double _sigma;
    int _size;
    Matrix<double> kernel;
};

#endif // GAUSSIANBLUR_H
