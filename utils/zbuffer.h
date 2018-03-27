#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QImage>
#include <QColor>

#include "objects/point3d.h"
#include "matrix.h"
#include "objects/rgb.h"
#include "objects/camera.h"
#include "objects/light.h"
#include "objects/model.h"

class ZBuffer
{
public:
    ZBuffer();
    ~ZBuffer();

    void setImage(QImage *img);
    void renderModel(const shared_ptr<Model> &model);

    void setCamera(const shared_ptr<Camera> &camera);
    void addLightSource(const shared_ptr<Light> &source);

private:
    void renderPolygon(PolygonVert &wpol3D, PolygonVert &wpolProj);
    void calcXZ(const Point3D &p1, const Point3D &p2,
                QVector<int> &resultX, QVector<double> &resultZ);
    void composeYGroup(PolygonVert &projected, PolygonVert &original,
                       Array<QVector<int>> &YGroupX,
                       Array<QVector<double>> &YGroupZ,
                       Array<QVector<Point3D>> &normales,
                       int &left, int &right);
    void sortVertices(PolygonVert &projected, PolygonVert &original);
    Rgb calcIntensity(const Point3D &point, const Point3D &normal);
    void interpolateNormales(const Point3D &first, const Point3D &second,
                             int len, QVector<Point3D> &normales);


private:
    shared_ptr<Camera> _camera;
    QVector<shared_ptr<Light>> _sources;

    QImage *workImage;
    Matrix<double> buffer;

    QVector<PolygonVert> polygonsProjected;
    QVector<PolygonVert> polygons3D;
    int pCount;
    Material modelMaterial;

    TransformMatrix scaleMatrix;
    TransformMatrix pvMatrix;
    TransformMatrix shiftMatrix;
};

#endif // ZBUFFER_H
