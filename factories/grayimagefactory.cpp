#include "grayimagefactory.h"

GrayImageFactory::GrayImageFactory()
{

}

Image* GrayImageFactory::create(const QImage& img)
{    
    Image* gray_img = new GrayImage(img.width(), img.height());
    for (int i = 0; i < gray_img->height(); i++)
        for (int j = 0; j < gray_img->width(); j++)
            gray_img->setPixel((uchar) qGray(img.pixel(j,i)), i, j);
    return gray_img;
}

