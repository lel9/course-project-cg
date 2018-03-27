#include "camera_factory.h"

//#include "exceptions.h"
#include "utils/matrix_set.h"
#include "objects/cameraitem.h"

//#include "id_creator.h"

CameraFactory::CameraFactory(const char *filename) :
    reader(make_unique<FileReader>(filename))
{

}

shared_ptr<SceneObject> CameraFactory::create()
{
    camera = make_unique<Camera>();
    shared_ptr<Item> item = make_shared<CameraItem>();
    camera->setItem(item);

    readObjType();
    readView();
    char t = readType();
    while (isspace(t))
        t = readType();

    if (t == 'o')
        readOrthographic();
    else if (t == 'p')
        readPespective();
    //else
    //    throw ReaderException("create");

    //camera->setId(IdCreator::getInstance().nextId());
    return std::move(camera);
}

void CameraFactory::readObjType()
{
    bool eof;
    char t = reader->readChar(eof);
    Q_UNUSED(t);
    //if (eof)
    //    throw ReaderException("type");
    //if (t != 'c')
    //    throw ReaderException("type");
}

void CameraFactory::readView()
{
    camera->setPosition3D(readPosition());
    camera->setLookAt(readLookAt());
}

Point3D CameraFactory::readPosition()
{
    bool eof;
    Point3D position;
    position.setX(reader->readFloat(eof));
    position.setY(reader->readFloat(eof));
    position.setZ(reader->readFloat(eof));
    //if (eof)
    //    throw ReaderException("position");
    return position;
}

Point3D CameraFactory::readLookAt()
{
    bool eof;
    Point3D lookAt;
    lookAt.setX(reader->readFloat(eof));
    lookAt.setY(reader->readFloat(eof));
    lookAt.setZ(reader->readFloat(eof));
    //if (eof)
    //    throw ReaderException("lookat");
    return lookAt;
}

char CameraFactory::readType()
{
    bool eof;
    char t = reader->readChar(eof);
    //if (eof)
    //    throw ReaderException("type");
    return t;
}

void CameraFactory::readPespective()
{
    bool eof;
    float FOVx = reader->readFloat(eof);
    float FOVy = reader->readFloat(eof);
    float near = reader->readFloat(eof);
    float far = reader->readFloat(eof);
    //if (eof)
    //    throw ReaderException("perspective");
    camera->setProjectionMatrix(MatrixPerspectiveProjection(FOVx, FOVy, near, far).create());
}

void CameraFactory::readOrthographic()
{
    camera->setProjectionMatrix(MatrixOrthographicProjection().create());
}

