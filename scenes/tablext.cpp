#include "tablext.h"

TableXT::TableXT()
{

}

void TableXT::addChild(const shared_ptr<SceneObject> &child)
{
    TableScene::addChild(child);
    connect(child->item().get(), SIGNAL(positionChanged(QPointF)),
            this, SLOT(updateTrackInfo(QPointF)));
    connect(child.get(), SIGNAL(prevPosChanged(QVector<QPointF>)),
            this, SLOT(updatePrevPos(QVector<QPointF>)));
    prevPos << QVector<QPointF>();

}

void TableXT::addChildren(const QVector<shared_ptr<SceneObject>> &children)
{
    TableScene::addChildren(children);
    foreach (shared_ptr<SceneObject> child, children)
    {
        connect(child->item().get(), SIGNAL(positionChanged(QPointF)),
                this, SLOT(updateTrackInfo(QPointF)));
        connect(child.get(), SIGNAL(prevPosChanged(QVector<QPointF>)),
                this, SLOT(updatePrevPos(QVector<QPointF>)));
        prevPos << QVector<QPointF>();
    }
}

void TableXT::removeChild(const shared_ptr<SceneObject> &pos)
{
    int index = _children.indexOf(pos);
    if (index >= 0 && index < _children.length())
        prevPos.remove(index);
    TableScene::removeChild(pos);
}

QVector<double> TableXT::prevCoordsValues(int obj) const
{
    QVector<double> res;
    int n = prevPos[obj].length();
    res.resize(n);
    for (int i = 0; i < n; i++)
        res[i] = prevPos[obj][i].y() - baseVal[obj];
    return res;
}

void TableXT::update()
{
    for (int i = 0; i < _canvas->objsCount(); i++)
    {
        QVector<double> values = _values[i];
        for(int j = 0; j < values.length(); j++)
            values[j] *= _scale;
        _canvas->setCoordsValues(i, values);
    }
}

void TableXT::updatePrevPos(QVector<QPointF> pos)
{
    int i = 0;
    auto child = _children.begin();
    for ( ; child < _children.end() && (*child).get() != sender(); child++, i++)
        ;
    if (child != _children.end())
    {
        if (prevPos[i].isEmpty())
            prevPos[i] = pos;
    }
}

TableVT::TableVT()
{

}

void TableAT::update()
{
    if (_canvas)
    {
        for (int i = 0; i < _canvas->objsCount(); i++)
        {
            QVector<double> values = _values[i];
            for(int j = 0; j < values.length(); j++)
                values[j] *= _scale*_canvas->timeScale()*_canvas->timeScale();
            _canvas->setCoordsValues(i, values);
        }
    }
}

void TableFT::update()
{
    for (int i = 0; i < _canvas->objsCount(); i++)
    {
        QVector<double> values = _values[i];
        for(int j = 0; j < values.length(); j++)
            values[j] *= _scale*_canvas->timeScale()*_canvas->timeScale();
        _canvas->setCoordsValues(i, values);
    }
}

void TableFT::setCoordsValues(int obj, const QVector<double> &val)
{
    TableScene::setCoordsValues(obj, val);
    for (int i = 0; i < _values[obj].length(); i++)
        _values[obj][i] *= m;
}
