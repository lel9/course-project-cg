#ifndef GRAY_IMAGE_H
#define GRAY_IMAGE_H

#include "image.h"

class GrayImage : public Image
{
private:
    uchar *_data;
public:
    GrayImage();
    GrayImage(int width, int height);
    GrayImage(uchar *data, int width, int height);
    GrayImage(GrayImage &&rvalue);
    GrayImage(const GrayImage &rvalue);

    ~GrayImage() { delete[] _data; }

    virtual void setPixel(uchar gray, int x, int y) override;
    virtual void setPixel(Rgb pixel, int x, int y) override;
    virtual Rgb pixel(int x, int y) const override;

    virtual uchar intensity(int x, int y) const override;
    virtual Image* piece(mPointI pos, int width, int height) const override;

    virtual pixelArray pixelRow(int row) const override;
    virtual pixelArray pixelColumn(int col) const override;
    virtual void setPixelRow(int row, uchar *data) override;
    virtual void setPixelColumn(int col, uchar *data) override;

    virtual Image *copy() override;
    virtual void clear() override;

    GrayImage& operator=(GrayImage &&rvalue);
    GrayImage& operator=(const GrayImage &rvalue);

    uchar* data() { return _data; }
};

#endif // GRAY_IMAGE_H
