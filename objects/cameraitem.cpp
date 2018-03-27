#include "cameraitem.h"

CameraItem::CameraItem()
{
    pixmap = new PixmapItem;
}

CameraItem::~CameraItem()
{
    delete pixmap;
}

QGraphicsItem *CameraItem::graphicsItem() const
{
    return pixmap;
}

#include <QPainter>
void PixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(this->pos(), *img);
}
