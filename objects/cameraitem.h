#ifndef CAMERAITEM_H
#define CAMERAITEM_H

#include "item.h"

class PixmapItem : public QGraphicsItem
{
public:
    PixmapItem() { img = new QImage(700,700, QImage::Format_RGB32);
                 img->fill(Qt::white); }
    ~PixmapItem() { delete img; }
    virtual QRectF boundingRect() const { return QRectF(0,0,img->width(), img->height()); }
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QImage *image() { return img; }
private:
    QImage *img;
};

class CameraItem : public Item
{
public:
    CameraItem();
    ~CameraItem();

    virtual QGraphicsItem* graphicsItem() const override;
    virtual QImage* image() override { return pixmap->image(); }

private:
    PixmapItem *pixmap;
};

#endif // CAMERAITEM_H
