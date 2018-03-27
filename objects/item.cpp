#include "item.h"

Item::Item() :
    _color(Qt::black),
    _scale(1,1)
{

}

Item::~Item()
{

}

void Item::setPosition(const QPointF &newPos)
{
    emit positionChanged(newPos);
}

QPointF Item::position() const
{
    return QPointF(0,0);
}

bool Item::isVideoItem()
{
    return false;
}

bool Item::isSelected() const
{
    return false;
}

QColor Item::color() const
{
    return _color;
}

QSize Item::size() const
{
    return QSize();
}

void Item::setColor(const QColor &color)
{
    _color = color;
    emit colorChanged(color);
}

void Item::updateObjectName(const QString &name)
{
    setObjectName(name);
    graphicsItem()->setToolTip(name);
}

