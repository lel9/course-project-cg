#ifndef VERTEX_H
#define VERTEX_H

#include "point3d.h"
class Vertex
{
private:
    Point3D _point;
    //Point2D _texture;
    Point3D _normal;
public:
    Vertex();
    Vertex(const Point3D &point, const Point3D &normal);
    Vertex(const Point3D &point);

    Point3D point() const { return _point; }
    //Point2D texture() const { return _texture; }
    Point3D normal() const { return _normal; }

    Vertex &operator=(const Vertex &other);
};

#endif // VERTEX_H
