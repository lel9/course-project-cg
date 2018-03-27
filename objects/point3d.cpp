#include "point3d.h"

#include <cmath>

Point3D::Point3D()
{
    _data[0] = 0;
    _data[1] = 0;
    _data[2] = 0;
    _data[3] = 1;
}

Point3D::Point3D(double x, double y, double z, double w)
{
    _data[0] = x;
    _data[1] = y;
    _data[2] = z;
    _data[3] = w;
}

Point3D::Point3D(const Point3D &origin)
{
    _data[0] = origin._data[0];
    _data[1] = origin._data[1];
    _data[2] = origin._data[2];
    _data[3] = origin._data[3];
}

Point3D::~Point3D()
{

}

void Point3D::toAffine()
{
    _data[0] /= _data[3];
    _data[1] /= _data[3];
    _data[2] /= _data[3];
    _data[3] = 1;
}

void Point3D::toBarycenteric(const Point3D &a, const Point3D &b, const Point3D &c)
{
    Point3D v0 = b - a, v1 = c - a, v2 = *this - a;
    double d00 = v0.getDot(v0);
    double d01 = v0.getDot(v1);
    double d11 = v1.getDot(v1);
    double d20 = v2.getDot(v0);
    double d21 = v2.getDot(v1);
    double denom = d00*d11 - d01*d01;
    _data[1] = (d11*d20 - d01*d21) / denom;
    _data[2] = (d00*d21 - d01*d20) / denom;
    _data[0] = 1.0 - (_data[1] + _data[2]);
    _data[3] = 1;
}

void Point3D::toCartesian(const Point3D &a, const Point3D &b, const Point3D &c)
{
    *this = a*_data[0] + b*_data[1] + c*_data[2];
}

void Point3D::normalize()
{
    double l = length();
    _data[0] /= l;
    _data[1] /= l;
    _data[2] /= l;
}

Point3D Point3D::getNormalized() const
{
    Point3D result(*this);
    double l = length();
    result._data[0] /= l;
    result._data[1] /= l;
    result._data[2] /= l;
    return result;
}

void Point3D::transform(const TransformMatrix &m)
{
    *this = this->getTransformed(m);
}

Point3D Point3D::getTransformed(const TransformMatrix &m) const
{
    Point3D result(0,0,0,0);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result._data[i] += m(i, j) * _data[j];
    return result;
}

void Point3D::cross(const Point3D &other)
{
    *this = this->getCross(other);
}

Point3D Point3D::getCross(const Point3D &other) const
{
    Point3D result;
    result._data[0] = _data[1] * other._data[2] - _data[2]*other._data[1];
    result._data[1] = _data[2] * other._data[0] - _data[0]*other._data[2];
    result._data[2] = _data[0] * other._data[1] - _data[1]*other._data[0];
    return result;
}


double Point3D::getDot(const Point3D &other) const
{
    return _data[0]*other._data[0] + _data[1]*other._data[1] + _data[2]*other._data[2];
}

Point3D Point3D::operator*(const double factor) const
{
    Point3D result;
    result._data[0] = _data[0] * factor;
    result._data[1] = _data[1] * factor;
    result._data[2] = _data[2] * factor;
    return result;
}

double Point3D::length() const
{
    double result = _data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2];
    return sqrt(result);
}

Point3D& Point3D::operator=(const Point3D &origin)
{
    _data[0] = origin._data[0];
    _data[1] = origin._data[1];
    _data[2] = origin._data[2];
    _data[3] = origin._data[3];
    return *this;
}

Point3D Point3D::operator+(const Point3D &other) const
{
    Point3D result(_data[0]+other._data[0], _data[1]+other._data[1], _data[2]+other._data[2]);
    return result;
}

Point3D Point3D::operator-(const Point3D &other) const
{
    Point3D result(_data[0]-other._data[0], _data[1]-other._data[1], _data[2]-other._data[2]);
    return result;
}

Point3D Point3D::operator-() const
{
    Point3D result;
    result._data[0] = -_data[0];
    result._data[1] = -_data[1];
    result._data[2] = -_data[2];
    return result;
}


