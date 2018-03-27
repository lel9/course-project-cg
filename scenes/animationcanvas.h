#ifndef ANIMATIONCANVAS_H
#define ANIMATIONCANVAS_H

#include "canvas.h"
#include <QLabel>
#include <QMouseEvent>

class ModelLabel : public QLabel
{
    Q_OBJECT
public:

    ModelLabel() { }

    void resizeEvent(QResizeEvent *event)
    {
        QLabel::resizeEvent(event);
        //this->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }

    void mousePressEvent(QMouseEvent *event)
    {
        lastPos = event->pos();
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        qreal dx = event->pos().x() - lastPos.x();
        qreal dy = event->pos().y() - lastPos.y();

        lastPos = event->pos();
        emit cameraMoved(dx, dy);
    }

signals:
    void cameraMoved(float, float);

private:
    QGraphicsScene *scene;
    QPointF lastPos;

};

class AnimationCanvas : public Canvas
{
    Q_OBJECT

public:
    AnimationCanvas();
    ~AnimationCanvas();

    virtual QWidget* widget() { return _view; }

    virtual void addItem(const shared_ptr<Item> &item) override;
    virtual void removeItem(const shared_ptr<Item> &item) override;
    virtual void update() override;

signals:
    void cameraMoved(float, float);

private:
    ModelLabel *_view;
};

#endif // ANIMATIONCANVAS_H
