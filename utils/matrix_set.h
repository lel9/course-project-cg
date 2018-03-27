#ifndef MATRIX_SET_H
#define MATRIX_SET_H

#include "transformmatrix.h"
#include "objects/point3d.h"

class MatrixFactory
{
public:
    MatrixFactory() = default;
    virtual ~MatrixFactory() = default;
    virtual TransformMatrix create() = 0;
};

class MatrixShift : public MatrixFactory
{
protected:
    Point3D move;
public:
    MatrixShift(const Point3D &mv) { move = mv; }
    virtual TransformMatrix create() override;
};

class MatrixScale : public MatrixFactory
{
protected:
    Point3D factors;
public:
    MatrixScale(const Point3D &f) { factors = f; }
    virtual TransformMatrix create() override;
};

class MatrixRotateX : public MatrixFactory
{
protected:
    float angle;
public:
    MatrixRotateX(const float a) { angle = a; }
    virtual TransformMatrix create() override;
};

class MatrixRotateY : public MatrixFactory
{
protected:
    float angle;
public:
    MatrixRotateY(const float a) { angle = a; }
    virtual TransformMatrix create() override;
};

class MatrixRotateZ : public MatrixFactory
{
protected:
    float angle;
public:
    MatrixRotateZ(const float a) { angle = a; }
    virtual TransformMatrix create() override;
};

class MatrixView : public MatrixFactory
{
protected:
    Point3D position;
    Point3D lookAt;
    Point3D up;
public:
    MatrixView(const Point3D &pos, const Point3D &l, const Point3D &u = Point3D(0, 1, 0))
    {
        position = pos;
        lookAt = l;
        up = u;
    }
    virtual TransformMatrix create() override;
};

class MatrixOrthographicProjection : public MatrixFactory
{
public:
    virtual TransformMatrix create() override;
};

class MatrixPerspectiveProjection : public MatrixFactory
{
protected:
    float FOVx;
    float FOVy;
    float nearZ;
    float farZ;
public:
    MatrixPerspectiveProjection(float Fx, float Fy, float nZ, float fZ)
    {
        FOVx = Fx;
        FOVy = Fy;
        nearZ = nZ;
        farZ = fZ;
    }

    virtual TransformMatrix create() override;
};

#endif // MATRIXF_SET_H
