#include "scene_object.h"

SceneObject::SceneObject() :
    _item(nullptr)
{

}

SceneObject::SceneObject(const Point3D &pos) :
    _item(nullptr),
    _position3D(pos)
{

}

SceneObject::~SceneObject()
{
    _item.reset();
}

bool SceneObject::isVideo()
{
    return false;
}

int SceneObject::id()
{
    return _id;
}

void SceneObject::setId(int id)
{
    _id = id;
}

shared_ptr<Item> SceneObject::item()
{
    return _item;
}

void SceneObject::setItem(const shared_ptr<Item> &item)
{
    if (_item)
        _item.reset();
    _item = item;
    connect(this, SIGNAL(objectNameChanged(QString)),
            item.get(), SLOT(updateObjectName(QString)));
}

void SceneObject::transform(const TransformMatrix &m)
{
    _position3D.transform(m);
}
