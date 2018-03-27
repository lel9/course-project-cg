#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include "utils/filereader.h"
#include "sceneobjectfactory.h"
#include "objects/model.h"

class ModelFactory : public SceneObjectFactory
{
protected:
    unique_ptr<FileReader> readerObj;
    unique_ptr<FileReader> readerMtl;

    unique_ptr <Model> model;
    bool moving;

public:
    ModelFactory(const char *fileObj, const char *fileMdl, bool move);
    virtual shared_ptr<SceneObject> create() override;

protected:
    void readObjType();
    Point3D readPosition();
    void readItems();
    PolygonInt readTriangle();
    Point3D readPoint3D();
    Point2D readPoint2D();
    Material readMaterial();
    Rgb readColor();


};

#endif // MODELFACTORY_H
