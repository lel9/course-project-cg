#ifndef TRACKPOINTFACTORY_H
#define TRACKPOINTFACTORY_H

#include "sceneobjectfactory.h"

class TrackPointFactory : SceneObjectFactory
{
private:
    QMenu *_contextMenu;
public:
    TrackPointFactory(QMenu *menu);
    ~TrackPointFactory() = default;
    QColor getRandomColor();
    virtual shared_ptr<SceneObject> create() override;
};

#endif // TRACKPOINTFACTORY_H
