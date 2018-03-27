#include "gaussianblur.h"

#include "math.h"
#define M_PI		3.14159265358979323846

double Gauss(double sigma, int x, int y)
{
    return (1.0/(2* M_PI *sigma*sigma))*exp(-(x*x+y*y)/(2*sigma*sigma));
}

GaussianBlur::GaussianBlur() :
    _sigma(0),
    _size(0)
{

}

GaussianBlur::GaussianBlur(int sigma, double size) :
    _sigma(sigma),
    _size(size)
{
    updateKernel(sigma, size);
}

GaussianBlur::~GaussianBlur()
{

}

void GaussianBlur::updateKernel(double sigma, int size)
{
    _sigma = sigma;
    _size = size;
    kernel.resize(_size, _size);

    double sum = 0;

    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
        {
            kernel(i,j) = Gauss(_sigma, i-_size/2, j-_size/2);
            sum += kernel(i,j);
        }


    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            kernel(i,j) /= sum;
}

void GaussianBlur::blur(Image *img)
{
    Image *saved = img->copy();

    int height = img->height();
    int width = img->width();

    int pixelPosX;
    int pixelPosY;
    double result;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            result = 0;

            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    pixelPosX = (x + j - _size / 2 + width)%width;
                    pixelPosY = (y + i - _size / 2 + height)%height;

                    uchar color = saved->intensity(pixelPosY, pixelPosX);

                    double kernelVal = kernel(i,j);

                    result += color * kernelVal;
                }
            }

            img->setPixel(static_cast<uchar>(result), y, x);
        }
    }
}

