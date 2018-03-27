#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QVector>
#include <QTime>

#include <memory>
using namespace std;

#include "objects/item.h"

class Canvas : public QObject
{
    Q_OBJECT

public:
    Canvas();
    virtual ~Canvas() = default;

    virtual QWidget *widget() = 0;

    // базовая реализация
    virtual void addItem(const shared_ptr<Item> &item);
    virtual void removeItem(const shared_ptr<Item> &item);
    virtual int coordsCount() const;
    virtual int objsCount() const;

    virtual QTime getBaseTime() const { return baseTime; }
    virtual QTime currentTime() const { return _currentTime; }

    virtual QString timeFormat() const;
    virtual void setTimeFormat(const QString &format);
    virtual void updateTotalTime(const QTime &time);
    virtual void updateCurrentTime(const QTime &time);
    virtual double timeScale() const { return _timeScale; }
    virtual void setTimeScale(double scale) { _timeScale = scale; }
    virtual void setEnabled(bool enable);
    virtual bool save(const QString &);

    virtual void setCoefs(int , const QVector<double> &) { }

    // заглушки
    virtual void setCursor(const QCursor &) { }
    virtual void update() { }

    virtual void setHeader(int , const QString & ) { }
    virtual void setColor(int , const QColor & ) { }
    virtual void setTrackInfo(int , const float ) { }
    virtual void setTimeValues(const QVector<QTime> &times);
    virtual void setCoordsValues(int , const QVector<double> &) { }
    virtual QVector<double> coordsValues(int ) const { return QVector<double>(); }
    virtual QVector<QTime> timeValues() const { return _times; }

    virtual void registerVideoItem(const shared_ptr<Item> &) { }

signals:
    void updateCursorPos(QPointF);
    void sliderReleased(qint64 msec);

protected:
    QVector<shared_ptr<Item>> items;
    QString _timeFormat;
    QTime _currentTime;
    QTime _totalTime;
    QTime baseTime;
    double _timeScale;
    QVector<QTime> _times;

    QVector<QVector<double>> _coefs;

    int _objsCount;
    int _coordsCount;
};

#endif // CANVAS_H
