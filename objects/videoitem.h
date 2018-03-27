#ifndef QtGraphicsVideoItem_H
#define QtGraphicsVideoItem_H

#include "scene_object.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class GraphicsVideoItem : public QGraphicsPixmapItem
{
public:
    GraphicsVideoItem() { setAcceptHoverEvents(true); }
    ~GraphicsVideoItem() { }
    void setImage(QImage img) { this->setPixmap(QPixmap::fromImage(img)); }

private:
    QImage _img;
};

class OpenCVVideoItem : public Item
{
    Q_OBJECT

public:
    OpenCVVideoItem();
    ~OpenCVVideoItem();

    virtual void setPosition(const QPointF &newPos) override;
    virtual QPointF position() const override;
    virtual bool isVideoItem() override;
    virtual bool isSelected() const override;

    virtual void setMovable(bool enable) override;
    virtual void setEnabled(bool enable) override;

    virtual QGraphicsItem* graphicsItem() const override;

public slots:
    void setImage(QImage img);

private:
    GraphicsVideoItem *_graphicsitem;

};

#endif // QtGraphicsVideoItem_H
