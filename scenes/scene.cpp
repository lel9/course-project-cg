#include "scene.h"

Scene::Scene() :
    _canvas(nullptr),
    _scale(1),
    _id(0),
    _parentId(-1)
{

}

Scene::~Scene()
{
    _children.clear();
}

void Scene::setCanvas(Canvas *canvas)
{
    if (_canvas)
        delete _canvas;
    _canvas = canvas;
}

void Scene::addChild(const shared_ptr<SceneObject> &child)
{
    _children << child;
    if (_canvas)
        _canvas->addItem(child->item());
}

void Scene::addChildren(const QVector<shared_ptr<SceneObject>> &children)
{
    _children += children;
    if (_canvas)
    {
        for (shared_ptr<SceneObject> child : children)
            _canvas->addItem(child->item());
    }
}

QVector<shared_ptr<SceneObject>> Scene::selectedChildren() const
{
    QVector<shared_ptr<SceneObject>> result;
    foreach (shared_ptr<SceneObject>child, _children)
        if (child->item()->isSelected())
            result << child;
    return result;
}

QVector<shared_ptr<SceneObject>> &Scene::getChildren()
{
    return _children;
}

void Scene::setScale(double scale)
{
    _scale = scale;
}

double Scene::scale() const
{
    return _scale;
}

void Scene::setTimeScale(double scale)
{
    if (_canvas)
        _canvas->setTimeScale(scale);
}

double Scene::timeScale() const
{
    if (_canvas)
        return _canvas->timeScale();
    return 1;
}

void Scene::removeChild(const shared_ptr<SceneObject> &pos)
{
    if(_children.removeOne(pos))
    {
        if (_canvas)
            _canvas->removeItem(pos->item());
    }
}

bool Scene::loadDataFromFile(const QString &)
{
    return false;
}

bool Scene::save(QString &dir)
{
    if (_canvas)
        return _canvas->save(dir + "\\" + objectName());
    return false;
}

/*void Scene::setHeader(int obj, const QString &header)
{
    return _canvas->setHeader(obj, header);
}

void Scene::setColor(int obj, const QColor &color)
{
    return _canvas->setColor(obj, color);
}*/

void Scene::setTrackInfo(int obj, const float info)
{
    if (_canvas)
        _canvas->setTrackInfo(obj, info);
}

void Scene::setTimeValues(const QVector<QTime> &val)
{
    if (_canvas)
        _canvas->setTimeValues(val);
}

void Scene::setCoordsValues(int obj, const QVector<double> &val)
{
    if (_canvas)
        _canvas->setCoordsValues(obj, val);
}

QVector<double> Scene::coordsValues(int obj) const
{
    if (_canvas)
        return _canvas->coordsValues(obj);
    return QVector<double>();
}

QVector<double> Scene::prevCoordsValues(int obj) const
{
    shared_ptr<SceneObject> child = _children[obj];
    QVector<QPointF> pos = child->prevPositions();
    QVector<double> res;
    for (int i = 0; i < pos.length(); i++)
        res << pos[i].y();
    return res;
}

QVector<double> Scene::nextCoordsValues(int obj) const
{
    shared_ptr<SceneObject> child = _children[obj];
    QVector<QPointF> pos = child->nextPositions();
    QVector<double> res;
    for (int i = 0; i < pos.length(); i++)
        res << pos[i].y();
    return res;
}

QVector<QTime> Scene::timeValues() const
{
    if (_canvas)
        return _canvas->timeValues();
    return QVector<QTime>();
}

//QTime Scene::startTrackTime(int obj) const
//{
//    return _children[obj]->timeStart();
//}

//QTime Scene::stopTrackTime(int obj) const
//{
//    return _children[obj]->timeStop();
//}

QTime Scene::baseTime() const
{
    if (_canvas)
        return _canvas->getBaseTime();
    return QTime();
}

int Scene::coordsCount() const
{
    if (_canvas)
        return _canvas->coordsCount();
    return 0;
}

int Scene::objsCount() const
{
    if (_canvas)
        return _canvas->objsCount();
    return 0;
}

const QVector<double>& Scene::getApprCoef(int i) const
{
    return apprCoef[i];
}

void Scene::setApprCoef(int i, const QVector<double> &coefs)
{
    apprCoef[i] = coefs;
    if (_canvas)
        _canvas->setCoefs(i, coefs);
}

QString Scene::timeFormat() const
{
    if (_canvas)
        return _canvas->timeFormat();
    return QString();
}

void Scene::setTimeFormat(const QString &format)
{
    if (_canvas)
        _canvas->setTimeFormat(format);
}

void Scene::setEnabled(bool enable)
{
    if (_canvas)
        _canvas->setEnabled(enable);
}

void Scene::setCursor(const QCursor &cursor)
{
    if (_canvas)
        _canvas->setCursor(cursor);
}

int Scene::id() const
{
    return _id;
}

void Scene::setId(int id)
{
    _id = id;
}

int Scene::parentId() const
{
    return _parentId;
}

QWidget *Scene::widget()
{
    return _canvas->widget();
}

