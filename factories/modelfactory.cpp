#include "modelfactory.h"

//#include "exceptions.h"
#include "utils/filereader.h"

#include "objects/modelitem.h"

ModelFactory::ModelFactory(const char *fileObj, const char *fileMdl, bool move) :
    readerObj(make_unique<FileReader>(fileObj)),
    readerMtl(make_unique<FileReader>(fileMdl)),
    moving(move)
{

}

shared_ptr<SceneObject> ModelFactory::create()
{
    model = make_unique<Model>(moving);

    //readObjType();
    //Point3D pos = readPosition();
    //model->setPosition3D(pos);
    readItems();
    model->setMaterial(readMaterial());

    shared_ptr<Item> item = make_shared<Item>();
    model->setItem(item);
    model->composePolygonVert();

    //model->setId(IdCreator::getInstance().nextId());

    shared_ptr<Model> smodel = std::move(model);
    return smodel;
}

void ModelFactory::readObjType()
{
    bool eof;
    readerObj->readChar(eof);
    //if (eof)
    //    throw readerObjException("type");
    //if (t != 'm')
    //    throw readerObjException("type");
}

Point3D ModelFactory::readPosition()
{
    bool eof;
    float v1 = readerObj->readFloat(eof);
    float v2 = readerObj->readFloat(eof);
    float v3 = readerObj->readFloat(eof);
    //if (eof)
    //    throw readerObjException("model position");
    return Point3D(v1, v2, v3);
}

void ModelFactory::readItems()
{
    bool eof = false;
    std::string current = readerObj->readWord(eof);

    while (!eof)
    {
        if (strcmp("f", current.data()) == 0)
            model->addPolygon(readTriangle());
        else if (strcmp("v", current.data()) == 0)
            model->addPoint(readPoint3D());
       // else if (strcmp("vt", current.data()) == 0)
       //     model->addTexture(readPoint2D());
        else if (strcmp("vn", current.data()) == 0)
            model->addNormal(readPoint3D());
        current = readerObj->readWord(eof);
    }
}


PolygonInt ModelFactory::readTriangle()
{
    bool eof;
    PolygonInt polygon;
    for (int i = 0; i < polygon.size(); i++)
    {
        polygon.addPoint(i, readerObj->readInt(eof)-1);
        readerObj->readChar(eof);
        readerObj->readChar(eof);
        polygon.addNormal(i, readerObj->readInt(eof)-1);
    }
    return polygon;
}

Point3D ModelFactory::readPoint3D()
{
    bool eof;
    float v1 = readerObj->readFloat(eof);
    float v2 = readerObj->readFloat(eof);
    float v3 = readerObj->readFloat(eof);
    //if (eof)
    //    throw readerObjException("model vertex");
    return(Point3D(v1, v2, v3));
}

Point2D ModelFactory::readPoint2D()
{
    bool eof;
    float v1 = readerObj->readFloat(eof);
    float v2 = readerObj->readFloat(eof);
    //if (eof)
    //    throw readerObjException("model vertex");
    return(Point2D(v1, v2));
}

Material ModelFactory::readMaterial()
{
    Material material;
    bool eof;
    std::string current = readerMtl->readWord(eof);
    while (!eof)
    {
        if (strcmp("Ns", current.data()) == 0)
            material.setNs(readerMtl->readFloat(eof));
        else if (strcmp("Ni", current.data()) == 0)
            material.setNi(readerMtl->readFloat(eof));
        else if (strcmp("Ka", current.data()) == 0)
            material.setKa(readColor());
        else if (strcmp("Kd", current.data()) == 0)
            material.setKd(readColor());
        else if (strcmp("Ks", current.data()) == 0)
            material.setKs(readColor());
        else if (strcmp("Ke", current.data()) == 0)
            material.setKe(readColor());
        else if (strcmp("d", current.data()) == 0)
            material.setD(readerMtl->readFloat(eof));
        else if (strcmp("illum", current.data()) == 0)
            material.setIllum(readerMtl->readInt(eof));
        current = readerMtl->readWord(eof);
    }
    return material;
}

Rgb ModelFactory::readColor()
{
    bool eof;
    uchar r = readerMtl->readFloat(eof) * 255 + 0.5;
    uchar g = readerMtl->readFloat(eof) * 255 + 0.5;
    uchar b = readerMtl->readFloat(eof) * 255 + 0.5;
    return Rgb(r, g, b);
}
