#include "videoitem.h"
#include <QGraphicsSceneMouseEvent>

OpenCVVideoItem::OpenCVVideoItem()
{
    _graphicsitem = new GraphicsVideoItem;
    _graphicsitem->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIgnoresTransformations);
}

OpenCVVideoItem::~OpenCVVideoItem()
{
}

void OpenCVVideoItem::setPosition(const QPointF &newPos)
{
    _graphicsitem->setPos(newPos);
}

QPointF OpenCVVideoItem::position() const
{
    return _graphicsitem->pos();
}

bool OpenCVVideoItem::isVideoItem()
{
    return true;
}

bool OpenCVVideoItem::isSelected() const
{
    return _graphicsitem->isSelected();
}

void OpenCVVideoItem::setMovable(bool enable)
{
    _graphicsitem->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, enable);
}

void OpenCVVideoItem::setEnabled(bool enable)
{
    _graphicsitem->setEnabled(enable);
}

QGraphicsItem* OpenCVVideoItem::graphicsItem() const
{
    return _graphicsitem;
}

void OpenCVVideoItem::setImage(QImage img)
{
     _graphicsitem->setImage(img);
}
