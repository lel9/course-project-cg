#ifndef OPENCVIMAGE_H
#define OPENCVIMAGE_H

#include "image.h"
#include "opencv2/imgproc.hpp"

class OpenCVImage : public Image
{
public:
    OpenCVImage(const cv::Mat &mat);
    ~OpenCVImage();

    virtual void setPixel(uchar gray, int x, int y);
    virtual void setPixel(Rgb pixel, int x, int y);
    virtual Rgb pixel(int x, int y) const;
    virtual uchar intensity(int x, int y) const;
    virtual Image* piece(mPointI pos, int width, int height) const;
    virtual pixelArray pixelRow(int row) const;
    virtual pixelArray pixelColumn(int col) const;

    virtual void setPixelRow(int row, uchar *data);
    virtual void setPixelColumn(int col, uchar *data);

    virtual Image* copy();
    virtual void clear();

    cv::Mat mat() const;

private:
    cv::Mat _cvImg;
};

#endif // OPENCVIMAGE_H
