#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QPointF>
#include <QGraphicsItem>
#include "utils/transformmatrix.h"

class Item : public QObject
{
    Q_OBJECT

public:
    Item();
    virtual ~Item();

    virtual void setPosition(const QPointF &newPos);
    virtual QPointF position() const;
    virtual bool isVideoItem();
    virtual bool isSelected() const;
    virtual QColor color() const;
    virtual QSize size() const;
    virtual void setColor(const QColor &color);
    virtual void setSize(const QSize &) { }

    virtual void setScale(const qreal xFactor, const qreal yFactor) { _scale.setX(xFactor);
                                                                      _scale.setY(yFactor); }
    virtual QGraphicsItem* graphicsItem() const { return nullptr; }
    virtual QImage* image() { return nullptr; }

signals:
    void positionChanged(const QPointF &newPos);
    void colorChanged(const QColor &color);

public slots:
    virtual void setMovable(bool) { }
    virtual void setEnabled(bool) { }
    virtual void updateObjectName(const QString &name);

protected:
    QColor _color;
    QPointF _scale;
};

#endif // ITEM_H
