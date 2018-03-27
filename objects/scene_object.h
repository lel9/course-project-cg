#ifndef SceneObject_H
#define SceneObject_H

#include <memory>
using namespace std;

#include <QObject>
#include <QTime>

class Image;
class Tracker;


#include "item.h"
#include "point3d.h"

class SceneObject : public QObject
{
    Q_OBJECT
public:
    SceneObject();
    SceneObject(const Point3D &pos);
    virtual ~SceneObject();

    virtual bool isVideo();

    virtual int id();
    virtual void setId(int id);

    virtual shared_ptr<Item> item();
    virtual void setItem(const shared_ptr<Item> &item);

    virtual void setStartFrame(Image *) { }
    virtual Tracker* tracker() { return nullptr; }
    virtual void findObjectPos(Image *) { }
    virtual QPointF getObjectPos(Image *) { return QPointF(); }
    virtual void transform(const TransformMatrix &m);

    virtual void setPosition3D(const Point3D &pos) { _position3D = pos; }
    virtual const Point3D &position3D() { return _position3D; }

    virtual void setPrevPositions(const QVector<QPointF> &pos) { _prevPositions = pos; emit prevPosChanged(pos);}
    virtual void setNextPositions(const QVector<QPointF> &pos) { _nextPositions = pos; }
    virtual QVector<QPointF> prevPositions() const { return _prevPositions; }
    virtual QVector<QPointF> nextPositions() const { return _nextPositions; }

//    virtual QTime timeStart() const { return _timeStart; }
//    virtual QTime timeStop() const { return _timeStop; }
//    virtual void setTimeStart(const QTime &time) { _timeStart = time; }
//    virtual void setTimeStop(const QTime &time) { _timeStop = time; }

signals:
    void prevPosChanged(QVector<QPointF> pos);

protected:
    int _id;
    shared_ptr<Item> _item;
    Point3D _position3D;

    QVector<QPointF> _prevPositions;
//    QTime _timeStart;
    QVector<QPointF> _nextPositions;
//    QTime _timeStop;
};

#endif // SceneObject_H
