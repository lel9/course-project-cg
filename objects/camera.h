#ifndef CAMERA_H
#define CAMERA_H

#include "scene_object.h"
#include "utils/matrix_set.h"

class Camera : public SceneObject
{
protected:
    TransformMatrix viewMatrix;
    TransformMatrix projectionMatrix;
    Point3D look_At;

public:
    Camera() { }
    ~Camera() { }

    void setProjectionMatrix(const TransformMatrix &m) { projectionMatrix = m; }
    void setLookAt(const Point3D &pos) {look_At = pos; setViewMatrix(); }
    Point3D lookAt() { return look_At; }
    TransformMatrix getPVMatrix() { return projectionMatrix * viewMatrix; }

    void transform(const TransformMatrix &m) { SceneObject::transform(m);
                                               look_At.transform(m);
                                               setViewMatrix(); }
    void setPosition3D(const Point3D &pos) { SceneObject::setPosition3D(pos);
                                             setViewMatrix(); }

protected:
    void setViewMatrix()
    {
        viewMatrix = MatrixView(_position3D, look_At).create();
    }
};

#endif // CAMERA_H
