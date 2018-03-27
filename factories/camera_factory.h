#ifndef CAMERAFACTORY_H
#define CAMERAFACTORY_H


#include "utils/filereader.h"
#include "sceneobjectfactory.h"
#include "objects/camera.h"

class CameraFactory : public SceneObjectFactory
{
protected:
    unique_ptr<FileReader> reader;

public:
    CameraFactory(const char *filename);

    virtual shared_ptr<SceneObject> create() override;

protected:
    void readObjType();
    void readView();
    Point3D readPosition();
    Point3D readLookAt();
    char readType();
    void readPespective();
    void readOrthographic();

    unique_ptr<Camera> camera;
};

#endif // CAMERAFACTORY_H
