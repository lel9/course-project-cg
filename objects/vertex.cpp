#include "vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(const Point3D &point, const Point3D &normal) :
    _point(point), _normal(normal)
{

}

Vertex::Vertex(const Point3D &point) :
    _point(point)
{

}

Vertex &Vertex::operator=(const Vertex &other)
{
    _point = other.point();
    _normal = other.normal();
    return *this;
}
