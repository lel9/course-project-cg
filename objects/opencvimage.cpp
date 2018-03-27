#include "opencvimage.h"

OpenCVImage::OpenCVImage(const cv::Mat &mat)
{
    mat.copyTo(_cvImg);
    _width = mat.cols;
    _height = mat.rows;
}

OpenCVImage::~OpenCVImage()
{

}

void OpenCVImage::setPixel(uchar gray, int x, int y)
{
    Q_UNUSED(gray);
    Q_UNUSED(x);
    Q_UNUSED(y);
}

void OpenCVImage::setPixel(Rgb pixel, int x, int y)
{
    Q_UNUSED(pixel);
    Q_UNUSED(x);
    Q_UNUSED(y);
}

Rgb OpenCVImage::pixel(int x, int y) const
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return Rgb();
}

uchar OpenCVImage::intensity(int x, int y) const
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return 0;
}

Image *OpenCVImage::piece(mPointI pos, int width, int height) const
{
    Q_UNUSED(pos);
    Q_UNUSED(width);
    Q_UNUSED(height);
    return nullptr;
}

pixelArray OpenCVImage::pixelRow(int row) const
{
    Q_UNUSED(row);
    return pixelArray(0);
}

pixelArray OpenCVImage::pixelColumn(int col) const
{
    Q_UNUSED(col);
    return pixelArray(0);
}

void OpenCVImage::setPixelRow(int row, uchar *data)
{
    Q_UNUSED(row);
    Q_UNUSED(data);
}

void OpenCVImage::setPixelColumn(int col, uchar *data)
{
    Q_UNUSED(col);
    Q_UNUSED(data);
}

Image *OpenCVImage::copy()
{
    return nullptr;
}

void OpenCVImage::clear()
{

}

cv::Mat OpenCVImage::mat() const
{
    return _cvImg;
}

