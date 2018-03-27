#include "polygon.h"

void PolygonInt::addPoint(int pos, int number)
{
    if (pos >= 0 && pos < _size)
        points[pos] = number;
}

void PolygonInt::addNormal(int pos, int number)
{
    if (pos >= 0 && pos < _size)
        normals[pos] = number;
}

void PolygonInt::addVertex(int pos, int point, int normal)
{
    if (pos >= 0 && pos < _size)
    {
        points[pos] = point;
        normals[pos] = normal;
    }
}
