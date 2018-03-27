#include "animationcanvas.h"
#include <QGraphicsScene>

AnimationCanvas::AnimationCanvas()
{
    _view = new ModelLabel;
    connect(_view, SIGNAL(cameraMoved(float, float)),
            this, SIGNAL(cameraMoved(float, float)));
}

AnimationCanvas::~AnimationCanvas()
{
    delete _view;
}

void AnimationCanvas::addItem(const shared_ptr<Item> &item)
{
    if (item->image())
    {
        _view->setPixmap(QPixmap::fromImage(*item->image()));
        Canvas::addItem(item);
    }
}

void AnimationCanvas::removeItem(const shared_ptr<Item> &item)
{
    Canvas::removeItem(item);
}

void AnimationCanvas::update()
{
    _view->setPixmap(QPixmap::fromImage(*items[0]->image()));
}

