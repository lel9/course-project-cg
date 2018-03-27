#ifndef POLYGON_H
#define POLYGON_H

#include "objects/vertex.h"
class PolygonVert
{
public:
    PolygonVert() { }
    PolygonVert(const Vertex &f, const Vertex &s, const Vertex &t) :
        _first(f), _second(s), _third(t)
    {
        Point3D u = _second.point() - _first.point();
        Point3D v = _third.point() - _first.point();
        Point3D n = u.getCross(v);

        _planeEquation.setX(n.x());
        _planeEquation.setY(n.y());
        _planeEquation.setZ(n.z());
        Point3D p1 = _first.point();
        double d = -(n.x()*p1.x() + n.y()*p1.y() + n.z()*p1.z());
        _planeEquation.setW(d);
    }

    Vertex first() const { return _first; }
    Vertex second() const { return _second; }
    Vertex third() const { return _third; }
    Vertex& first() { return _first; }
    Vertex& second() { return _second; }
    Vertex& third() { return _third; }

    Point3D planeEquation() const { return _planeEquation; }

private:
    Vertex _first;
    Vertex _second;
    Vertex _third;
    Point3D _planeEquation;
};

class PolygonInt
{
public:
    PolygonInt() { }
    //PolygonInt(const PolygonInt &other);
    //PolygonInt(PolygonInt &&other);
    void addPoint(int pos, int number);
    void addNormal(int pos, int number);
    void addVertex(int pos, int point, int normal);

    int size() const { return _size; }
    int pointAt(int pos) const { return points[pos]; }
    int NormalAt(int pos) const { return normals[pos]; }

private:
    static const int _size = 3;
    int points[_size];
    int normals[_size];
    //int textures[_size];
};

#endif // POLYGON_H
