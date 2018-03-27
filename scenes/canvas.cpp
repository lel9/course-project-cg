#include "canvas.h"

Canvas::Canvas() :
    _timeFormat("mm:ss.zzz"),
     _timeScale(1),
    _objsCount(0),
    _coordsCount(0)
{

}

void Canvas::addItem(const shared_ptr<Item> &item)
{
    if (item->graphicsItem() != nullptr)
        items << item;
}

void Canvas::removeItem(const shared_ptr<Item> &item)
{
    items.removeOne(item);
}

int Canvas::coordsCount() const
{
    return _coordsCount;
}

int Canvas::objsCount() const
{
    return _objsCount;
}

QString Canvas::timeFormat() const
{
    return _timeFormat;
}

void Canvas::setTimeFormat(const QString &format)
{
    _timeFormat = format;
}

void Canvas::updateTotalTime(const QTime &time)
{
    _totalTime = time;
}

void Canvas::updateCurrentTime(const QTime &time)
{
    _currentTime = time;
}

void Canvas::setEnabled(bool enable)
{
    for (shared_ptr<Item> item : items)
        item->setEnabled(enable);
}

bool Canvas::save(const QString &)
{
    return true;
}

void Canvas::setTimeValues(const QVector<QTime> &times)
{
    _times = times;
    if (!times.isEmpty())
        baseTime = _times.first();
}
