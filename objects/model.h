#ifndef MODEL_H
#define MODEL_H

#include "scene_object.h"
#include "point3d.h"
#include "edge.h"
#include "polygon.h"
#include "material.h"
#include "vertex.h"
#include "utils/matrix.h"

class Model : public SceneObject
{
protected:
    QVector<Point3D> points;
    QVector<Point3D> normales;
   // QVector<Point2D> textures;
    QVector<PolygonInt> polygons;
    QVector<PolygonVert> polygonsVert;
    Material material;

    bool isMoving;

public:
    Model(bool moving);
    ~Model();

    const QVector<Point3D> &getPoints() const { return points; }
    const QVector<Point3D> &getNormales() const { return normales; }
   // const QVector<Point2D> &getTextures() const { return textures; }
    const QVector<PolygonInt> &getPolygons() const { return polygons; }
    const Material &getMaterial() const { return material; }
    bool isMovingModel() { return isMoving; }

    void addPoint(const Point3D &v) { points << v; }
    void addNormal(const Point3D &n) { normales << n; }
   // void addTexture(const Point2D &t) { textures << t; }
    void addPolygon(const PolygonInt &p) { polygons << p; }
    void setMaterial(const Material &mat) { material = mat; }

    virtual void transform(const TransformMatrix &m);
    virtual void setPosition3D(const Point3D &pos) override;

    void composePolygonVert();
    const QVector<PolygonVert> &getPolygonVertices() const;
    QVector<PolygonVert> getProjectedPolygon(const TransformMatrix &pv,
                                             const TransformMatrix &scale,
                                             const TransformMatrix &shift) const;
};

#endif // MODEL_H
