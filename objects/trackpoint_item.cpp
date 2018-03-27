#include "trackpoint_item.h"

TrackPoint::TrackPoint()
{
    _tracker = new OpenCVTracker;
}

TrackPoint::~TrackPoint()
{
    delete _tracker;
}

void TrackPoint::setTraker(Tracker *tr)
{
    delete _tracker;
    _tracker = tr;
}

void TrackPoint::setStartFrame(Image *img)
{
    QPointF pos = _item->position();
    QSize size = _item->size();
    _tracker->setStartConfig(img, mPointF(pos.x()+size.width()/2., pos.y()+size.height()/2.));
}

void TrackPoint::findObjectPos(Image *img)
{
    _item->setPosition(getObjectPos(img));
}

QPointF TrackPoint::getObjectPos(Image *img)
{
    mPointF pos = _tracker->track(img);
    QSize size = _item->size();
    QPointF qpos(pos.x()-size.width()/2., pos.y()-size.height()/2.);
    return qpos;
}

TrackPointItem::TrackPointItem(QMenu *menu)
{
    _graphicsitem = new GraphicsRectItem(menu);
    _graphicsitem->setRect(0,0,10,10);
    _graphicsitem->setPen(QPen(Qt::red));
    _graphicsitem->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
}

TrackPointItem::~TrackPointItem()
{
}

void TrackPointItem::setPosition(const QPointF &newPos)
{
    _graphicsitem->setPos(newPos);
    Item::setPosition(newPos);
}

QPointF TrackPointItem::position() const
{
    return _graphicsitem->pos();
}

bool TrackPointItem::isSelected() const
{
    return _graphicsitem->isSelected();
}

QSize TrackPointItem::size() const
{
    return _graphicsitem->rect().size().toSize();
}

void TrackPointItem::setMovable(bool enable)
{
    _graphicsitem->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, enable);
}

void TrackPointItem::setEnabled(bool enable)
{
    _graphicsitem->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, enable);
    _graphicsitem->setEnabled(enable);
}

void TrackPointItem::setSize(const QSize &size)
{
    QRectF rect(_graphicsitem->rect());
    rect.setSize(size);
    _graphicsitem->setRect(rect);
}

void TrackPointItem::setColor(const QColor &color)
{
    _graphicsitem->setPen(QPen(color));
    Item::setColor(color);
}

QGraphicsItem* TrackPointItem::graphicsItem() const
{
    return _graphicsitem;
}
