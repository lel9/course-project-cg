#ifndef VIDEOPLAYERFACTORY_H
#define VIDEOPLAYERFACTORY_H

#include "sceneobjectfactory.h"

class VideoPlayerFactory : public SceneObjectFactory
{
public:
    VideoPlayerFactory();
    ~VideoPlayerFactory() = default;
    virtual shared_ptr<SceneObject> create() override;
};

#endif // VIDEOPLAYERFACTORY_H
