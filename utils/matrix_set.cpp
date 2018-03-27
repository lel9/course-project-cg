#include "matrix_set.h"

#include <cmath>

TransformMatrix MatrixShift::create()
{
    TransformMatrix result;
    result(0, 0) = 1;
    result(1, 1) = 1;
    result(2, 2) = 1;
    result(0, 3) = move.x();
    result(1, 3) = move.y();
    result(2, 3) = move.z();
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixScale::create()
{
    TransformMatrix result;
    result(0, 0) = factors.x();
    result(1, 1) = factors.y();
    result(2, 2) = factors.z();
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixRotateX::create()
{
    TransformMatrix result;
    result(0, 0) = 1;
    result(1, 1) = cos(angle);
    result(1, 2) = sin(angle);
    result(2, 1) = -sin(angle);
    result(2, 2) = cos(angle);
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixRotateY::create()
{
    TransformMatrix result;
    result(1, 1) = 1;
    result(0, 0) = cos(angle);
    result(0, 2) = -sin(angle);
    result(2, 0) = sin(angle);
    result(2, 2) = cos(angle);
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixRotateZ::create()
{
    TransformMatrix result;
    result(2, 2) = 1;
    result(1, 1) = cos(angle);
    result(1, 0) = -sin(angle);
    result(0, 1) = sin(angle);
    result(0, 0) = cos(angle);
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixView::create()
{
    Point3D zaxis = (lookAt - position).getNormalized();
    Point3D xaxis = zaxis.getCross(up).getNormalized();
    Point3D yaxis = xaxis.getCross(zaxis);

    double mat[4][4] = {{xaxis.x(), xaxis.y(), xaxis.z(), -xaxis.getDot(position)},
                       {yaxis.x(), yaxis.y(), yaxis.z(), -yaxis.getDot(position)},
                       {zaxis.x(), zaxis.y(), zaxis.z(), -zaxis.getDot(position)},
                       {0, 0, 0, 1}};

    TransformMatrix result (mat);

    return result;
}

TransformMatrix MatrixOrthographicProjection::create()
{
    TransformMatrix result;
    result(0, 0) = 1;
    result(1, 1) = 1;
    result(3, 3) = 1;
    return result;
}

TransformMatrix MatrixPerspectiveProjection::create()
{
    TransformMatrix result;
    result(0, 0) = atan(FOVx / 2);
    result(1, 1) = atan(FOVy / 2);
    result(2, 2) = -(farZ + nearZ) / (farZ - nearZ);
    result(3, 2) = -(2 * farZ*nearZ) / (farZ - nearZ);
    result(2, 3) = -1;
    result(3, 3) = 0;
    return result;
}
