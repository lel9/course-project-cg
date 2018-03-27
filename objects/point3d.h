#ifndef POINT3D_H
#define POINT3D_H

#include "utils/transformmatrix.h"

class Point3D
{
private:
    static const int size = 4;
    double _data[size];
public:
    Point3D();
    Point3D(double x, double y, double z, double w = 1);
    Point3D(const Point3D &origin);

    ~Point3D();

    double x() const { return _data[0]; }
    double y() const { return _data[1]; }
    double z() const { return _data[2]; }
    double w() const { return _data[3]; }

    void setX(double x) { _data[0] = x; }
    void setY(double y) { _data[1] = y; }
    void setZ(double z) { _data[2] = z; }
    void setW(double w) { _data[3] = w; }

    void toAffine();
    void toBarycenteric(const Point3D &a, const Point3D &b, const Point3D &c);
    void toCartesian(const Point3D &a, const Point3D &b, const Point3D &c);

    double length() const;

    void normalize();
    Point3D getNormalized() const;

    void transform(const TransformMatrix &m);
    Point3D getTransformed(const TransformMatrix &m) const;

    void cross(const Point3D &other);
    Point3D getCross(const Point3D &other) const;

    double getDot(const Point3D &other) const;

    Point3D operator*(const double factor) const;

    Point3D &operator=(const Point3D &origin);

    Point3D operator+(const Point3D &other) const;
    Point3D operator-(const Point3D &other) const;
    Point3D operator-() const;
};

class Point2D : public Array<double>
{
private:
    static const int size = 3;
public:
    Point2D() { }
    Point2D(double x, double y, double w = 1) : Array(size)
    { _data[0] = x; _data[1] = y; _data[2] = w; }
    Point2D(const Point2D &origin) : Array(origin) { }
    Point2D(Point2D &&origin) : Array(origin) { }
    ~Point2D() { }

    Point2D& operator=(const Point2D &origin)
    {
        Array::operator=(origin);
        return *this;
    }

    Point2D& operator=(Point2D &&origin)
    {
        Array::operator=(origin);
        return *this;
    }
};

#endif // POINT3D_H
