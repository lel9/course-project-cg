#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "scenes/scene.h"
#include "scenes/canvas.h"
#include "namecreator.h"

class SceneFactory
{
public:
    SceneFactory() : _isCreated(false) { }
    virtual ~SceneFactory() = default;
    virtual shared_ptr<Scene> create() = 0;
    virtual Canvas *createCanvas() = 0;
    virtual bool isCreated() { return _isCreated; }

protected:
    bool _isCreated;
};

#endif // SCENEFACTORY_H
