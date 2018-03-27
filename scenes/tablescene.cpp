#include "tablescene.h"

TableScene::TableScene()
{

}

void TableScene::addChild(const shared_ptr<SceneObject> &child)
{
    Scene::addChild(child);
    connect(child.get(), SIGNAL(objectNameChanged(QString)),
            this, SLOT(updateHeader(QString)));
    connect(child->item().get(), SIGNAL(colorChanged(QColor)),
            this, SLOT(updateColor(QColor)));
    _values << QVector<double>();
    apprCoef << QVector<double>();
    baseVal << 0;
}

void TableScene::addChildren(const QVector<shared_ptr<SceneObject>> &children)
{
    Scene::addChildren(children);
    foreach (shared_ptr<SceneObject> child, children)
    {
        connect(child.get(), SIGNAL(objectNameChanged(QString)),
                this, SLOT(updateHeader(QString)));
        connect(child->item().get(), SIGNAL(colorChanged(QColor)),
                this, SLOT(updateColor(QColor)));
        _values << QVector<double>();
        apprCoef << QVector<double>();
        baseVal << 0;
    }

}

void TableScene::removeChild(const shared_ptr<SceneObject> &pos)
{
    int index = _children.indexOf(pos);
    if (index >= 0 && index < _children.length())
    {
        _values.removeAt(index);
        apprCoef.removeAt(index);
        baseVal.removeAt(index);
    }
    Scene::removeChild(pos);
}

void TableScene::setScale(double scale)
{
    Scene::setScale(scale);
}

void TableScene::update()
{
    if (_canvas)
    {
        for (int i = 0; i < _canvas->objsCount(); i++)
        {
            QVector<double> values = _values[i];
            for(int j = 0; j < values.length(); j++)
                values[j] *= _scale*_canvas->timeScale();
            _canvas->setCoordsValues(i, values);
        }
    }
}

QVector<double> TableScene::coordsValues(int obj) const
{
    return _values[obj];
}

void TableScene::setCoordsValues(int obj, const QVector<double> &val)
{
    Scene::setCoordsValues(obj, val);
    _values[obj] = val;
    if (!val.isEmpty())
        baseVal[obj] = val.first();
}

QVector<double> TableScene::prevCoordsValues(int obj) const
{
    QVector<double> res = Scene::prevCoordsValues(obj);
    for (int i = 0; i < res.length(); i++)
        res[i] -= baseVal[obj];
    return res;
}

QVector<double> TableScene::nextCoordsValues(int obj) const
{
    QVector<double> res = Scene::nextCoordsValues(obj);
    for (int i = 0; i < res.length(); i++)
        res[i] -= baseVal[obj];
    return res;
}

void TableScene::updateHeader(const QString &newName)
{
    int i = 0;
    auto child = _children.begin();
    for ( ; child < _children.end() && (*child).get() != sender();
          child++, i++)
        ;
    if (child != _children.end())
        _canvas->setHeader(i, newName);
}

void TableScene::updateColor(const QColor &color)
{
    int i = 0;
    auto child = _children.begin();
    for ( ; child < _children.end() && (*child)->item().get() != sender();
          child++, i++)
        ;

    if (child != _children.end())
        _canvas->setColor(i, color);
}

#include "utils/converter.h"
void TableScene::updateTrackInfo(const QPointF &newPointPos)
{
    int i = 0;
    auto child = _children.begin();
    for ( ; child < _children.end() && (*child)->item().get() != sender();
          child++, i++)
        ;
    if (child != _children.end())
    {
        if (_values[i].isEmpty())
            baseVal[i] = newPointPos.y();

        double val = newPointPos.y()-baseVal[i];
        _canvas->setTrackInfo(i, val*_scale);
        if (_values[i].length() == _canvas->timeValues().length() - 1)
            _values[i] << val;
    }
}

void TableScene::on_currentTimeChanged(qint64 time)
{
    qint64 time1000 = time/1000;
    _canvas->updateCurrentTime(QTime((time1000/3600)%60, (time1000/60)%60,
                                      time1000%60, time%1000));
}

