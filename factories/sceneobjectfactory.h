#ifndef SCENEOBJECTFACTORY_H
#define SCENEOBJECTFACTORY_H

#include "objects/scene_object.h"

class SceneObjectFactory
{
public:
    SceneObjectFactory() = default;
    virtual ~SceneObjectFactory() = default;
    virtual shared_ptr<SceneObject> create() = 0;
};

#endif // SCENEOBJECTFACTORY_H
