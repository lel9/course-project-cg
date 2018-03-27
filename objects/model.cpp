#include "model.h"
#include "utils/matrix_set.h"
Model::Model(bool moving) :
    isMoving(moving)
{
}

Model::~Model()
{

}

QVector<PolygonVert> Model::getProjectedPolygon(const TransformMatrix &pv,
                                                const TransformMatrix &scale,
                                                const TransformMatrix &shift) const
{
    QVector<Point3D> pts = points;
    for (Point3D &point : pts)
    {
        point.transform(pv);
        point.toAffine();
        point.transform(scale);
        point.transform(shift);
    }

//    QVector<Point3D> norms = normales;
//    for (Point3D &normal : norms)
//    {
//        normal.transform(pv);
//        normal.toAffine();
//        normal.transform(scale);
//        normal.transform(shift);
//    }

    //QVector<Point2D> texts = textures;

    QVector<PolygonVert> ppp;
    for (const PolygonInt &pInt : polygons)
    {
        Vertex first(pts[pInt.pointAt(0)]);
        Vertex second(pts[pInt.pointAt(1)]);
        Vertex third(pts[pInt.pointAt(2)]);
        ppp << PolygonVert(first, second, third);
    }
    return ppp;
}

void Model::transform(const TransformMatrix &m)
{
    TransformMatrix modelTransform = MatrixShift(-position3D()).create() *
            m * MatrixShift(position3D()).create();
    for (Point3D &point : points)
        point.transform(modelTransform);
    for (Point3D &normal : normales)
        normal.transform(modelTransform);

    composePolygonVert();
    SceneObject::transform(m);
}

void Model::setPosition3D(const Point3D &pos)
{
    _position3D.transform(MatrixShift(pos).create());
}

void Model::composePolygonVert()
{
    polygonsVert.clear();
    for (const PolygonInt &pInt : polygons)
    {
        Vertex first =  Vertex(points[pInt.pointAt(0)], normales[pInt.NormalAt(0)]);
        Vertex second = Vertex(points[pInt.pointAt(1)], normales[pInt.NormalAt(1)]);
        Vertex third =  Vertex(points[pInt.pointAt(2)], normales[pInt.NormalAt(2)]);
        polygonsVert << PolygonVert(first, second, third);
    }
}

const QVector<PolygonVert> &Model::getPolygonVertices() const
{
    return polygonsVert;
}

