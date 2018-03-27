#ifndef GRAYIMAGEFACTORY_H
#define GRAYIMAGEFACTORY_H

#include "objects/gray_image.h"
#include <QImage>

class GrayImageFactory
{
public:
    GrayImageFactory();
    Image* create(const QImage& img);
};

#endif // GRAYIMAGEFACTORY_H
