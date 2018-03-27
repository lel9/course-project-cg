#ifndef QtGraphicsTrackPointItem_H
#define QtGraphicsTrackPointItem_H

#include "scene_object.h"
#include "tracking/templatetracker.h"

#include "tracking/opencvtracker.h"

#include <QGraphicsItem>
#include <QPen>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

class GraphicsRectItem : public QGraphicsRectItem
{
public:
    GraphicsRectItem(QMenu *menu) : _menu(menu) {
    setCursor(QCursor(Qt::PointingHandCursor));
    setAcceptHoverEvents(true);
    }
    ~GraphicsRectItem() {  }
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {
        scene()->clearSelection();
        this->setSelected(true);
        _menu->exec(event->screenPos());
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsRectItem::mouseReleaseEvent(event);
        setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, false);
        setCursor(QCursor(Qt::PointingHandCursor));
    }

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsRectItem::mouseMoveEvent(event);

        QPointF pos = this->pos();

        if (pos.x() < 0)
            pos.setX(0);
        if (pos.y() < 0)
            pos.setY(0);
        int w = this->parentItem()->boundingRect().width() - this->rect().width();
        int h = this->parentItem()->boundingRect().height() - this->rect().height();
        if (pos.x() >= w)
            pos.setX(w);
        if (pos.y() >= h)
            pos.setY(h);

        this->setPos(pos);
    }

    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event)
    {
        QGraphicsItem::hoverMoveEvent(event);
        if (isEnabled())
        {
            if (flags().testFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable))
                setCursor(QCursor(Qt::OpenHandCursor));
            else
                setCursor(QCursor(Qt::PointingHandCursor));
        }
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsItem::mousePressEvent(event);
        if (this->flags().testFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable))
            setCursor(QCursor(Qt::ClosedHandCursor));
    }

private:
    QMenu *_menu;
};

class TrackPointItem : public Item
{    
public:
    TrackPointItem(QMenu *menu);
    ~TrackPointItem();

    virtual void setPosition(const QPointF &newPos) override;
    virtual QPointF position() const override;
    virtual bool isSelected() const override;
    virtual QSize size() const override;

    virtual void setMovable(bool enable) override;
    virtual void setEnabled(bool enable) override;
    virtual void setSize(const QSize &size) override;
    virtual void setColor(const QColor &color) override;

    virtual QGraphicsItem* graphicsItem() const override;


private:
    GraphicsRectItem *_graphicsitem;
};

class TrackPoint : public SceneObject
{
public:
    TrackPoint();
    ~TrackPoint();

    void setTraker(Tracker *tr);
    void setStartFrame(Image *img) override;
    virtual void findObjectPos(Image *img) override;
    virtual QPointF getObjectPos(Image *img) override;

    virtual Tracker* tracker() override { return _tracker; }

private:
    Tracker *_tracker;
};

#endif // QtGraphicsTrackPointItem_H
