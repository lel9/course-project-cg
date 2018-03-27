#include "zbuffer.h"
#define ROUND(x) int((x) + 0.5)

ZBuffer::ZBuffer() :
    workImage(nullptr),
    pCount(0)
{
}

ZBuffer::~ZBuffer()
{

}

void ZBuffer::setImage(QImage *img)
{
    workImage = img;
    workImage->fill(Qt::white);
    buffer.resize(img->height(), img->width());
    for (int i = 0; i < img->height(); i++)
        for (int j = 0; j < img->width(); j++)
            buffer(i, j) = INT_MIN;
    scaleMatrix = MatrixScale(Point3D(90, 90, 90)).create(); //fix me
    shiftMatrix = MatrixShift(Point3D(350, 300, 0)).create();
}

void ZBuffer::renderModel(const shared_ptr<Model> &model)
{
    if (workImage == nullptr)
        return;

    modelMaterial = model->getMaterial();
    polygonsProjected = model->getProjectedPolygon(pvMatrix, scaleMatrix, shiftMatrix);
    polygons3D = model->getPolygonVertices();
    pCount = qMin(polygons3D.length(), polygonsProjected.length());

    for (int i = 0; i < pCount; i++)
        renderPolygon(polygons3D[i], polygonsProjected[i]);
}

void ZBuffer::setCamera(const shared_ptr<Camera> &camera)
{
    _camera.reset();
    _camera = camera;
    pvMatrix = _camera->getPVMatrix();
}

void ZBuffer::addLightSource(const shared_ptr<Light> &source)
{
    _sources << source;
}


void ZBuffer::renderPolygon(PolygonVert &wpol3D, PolygonVert &wpolProj)
{
    if (wpolProj.planeEquation().z() == 0)
        return;

    // формируем у-группы, в каждой группе два икса
    int left, right;
    Array<QVector<int>> YGroupX(2);
    Array<QVector<double>> YGroupZ(2);
    Array<QVector<Point3D>> normales(2);
    composeYGroup(wpolProj, wpol3D, YGroupX, YGroupZ, normales, left, right);

    Point3D p1 = wpolProj.first().point();
    Point3D p2 = wpolProj.second().point();
    Point3D p3 = wpolProj.third().point();

    Point3D po1 = wpol3D.first().point();
    Point3D po2 = wpol3D.second().point();
    Point3D po3 = wpol3D.third().point();

    // растеризация с проверкой буфера
    int minY = ROUND(p1.y());
    int maxY = ROUND(p3.y());
    for (int y = minY, i = 0; y <= maxY; y++, i++)
    {
        Point3D n1 = normales[left][i], n2 = normales[right][i];
        int minX = YGroupX[left][i];
        int maxX = YGroupX[right][i];

        double z1 = YGroupZ[left][i], z2 = YGroupZ[right][i];
        int s = maxX-minX;
        double dz = (z2-z1)/s;
        double z = z1;

        for (int x = minX, j = 0; j <= s; x++, j++)
        {
            if (z > buffer(x, y))
            {
                buffer(x, y) = z;
                Point3D n;
                if (s < 2)
                    n = (n1+n2)*0.5;
                else
                {
                    double t = (double) j/s;
                    n = n1*(1-t) + n2*t;
                }

                Point3D orig(x, y, z);
                orig.toBarycenteric(p1 ,p2, p3);
                orig.toCartesian(po1, po2, po3);
                Rgb intensity = calcIntensity(orig, n);
                workImage->setPixel(x, y, intensity.toQRgb());
            }
            z += dz;
        }
    }
}

void ZBuffer::calcXZ(const Point3D &p1, const Point3D &p2,
                     QVector<int> &resultX, QVector<double> &resultZ)
{
    int n = ROUND(p2.y()) - ROUND(p1.y());

    double x, z, dx = 0, dz = 0;
    if (n != 0)
    {
        dx = (p2.x()-p1.x())/n;
        dz = (p2.z()-p1.z())/n;
    }
    x = p1.x();
    z = p1.z();

    for (int i = 0; i <= n; i++)
    {
        resultX << ROUND(x);
        x += dx;
        resultZ << z;
        z += dz;
    }

}

void ZBuffer::composeYGroup(PolygonVert &projected, PolygonVert &original,
                            Array<QVector<int>> &YGroupX,
                            Array<QVector<double>> &YGroupZ,
                            Array<QVector<Point3D>> &normales,
                            int &left, int &right)
{    
    sortVertices(projected, original);
    Point3D p1 = projected.first().point();
    Point3D p2 = projected.second().point();
    Point3D p3 = projected.third().point();

    Point3D n1 = original.first().normal();
    Point3D n2 = original.second().normal();
    Point3D n3 = original.third().normal();

    left = 0; right = 1;
    calcXZ(p1, p3, YGroupX[left], YGroupZ[left]);
    int l1 = YGroupX[left].length();
    interpolateNormales(n1, n3, l1, normales[left]);

    calcXZ(p1, p2, YGroupX[right], YGroupZ[right]);
    int l2 = YGroupX[right].length();
    interpolateNormales(n1, n2, l2, normales[right]);

    YGroupX[right].pop_back();   // чтобы один икс не попал дважды
    YGroupZ[right].pop_back();   // чтобы один зет не попал дважды
    normales[right].pop_back();
    l2--;

    calcXZ(p2, p3, YGroupX[right], YGroupZ[right]);
    int l3 = YGroupX[right].length()-l2;
    interpolateNormales(n2, n3, l3, normales[right]);

    int len = YGroupX[left].length()/2;
    if (YGroupX[left][len] > YGroupX[right][len])
        std::swap(left, right);
}

void ZBuffer::sortVertices(PolygonVert &projected, PolygonVert &original)
{
    if (projected.second().point().y() < projected.first().point().y())
    {
        std::swap(projected.second(), projected.first());
        std::swap(original.second(), original.first());
    }
    if (projected.third().point().y() < projected.first().point().y())
    {
        std::swap(projected.third(), projected.first());
        std::swap(original.third(), original.first());
    }
    if (projected.third().point().y() < projected.second().point().y())
    {
        std::swap(projected.third(), projected.second());
        std::swap(original.third(), original.second());
    }
}

Rgb ZBuffer::calcIntensity(const Point3D &point, const Point3D &normal)
{
    Rgb res;
    for (shared_ptr<Light> &source : _sources)
    {
        if (source->type() == Ambient)
            res += modelMaterial.Ka()*source->intensity();
        else if (source->type() == PointSource)
        {
            Point3D L = point - source->position3D();
            Point3D Ln = L.getNormalized();
            Point3D nn = normal.getNormalized();
            static const int K = 0;

            double factor = source->intensity()/(L.length()+K);
            double cosO = nn.getDot(-Ln);
            if (cosO > 0)
                res += modelMaterial.Kd()*cosO*factor;

            Point3D S = (_camera->position3D()-point).getNormalized();
            Point3D R = Ln + nn*(2*cosO);
            R.normalize();
            double cosA = S.getDot(R);
            if (cosA > 0)
                res += modelMaterial.Ks()*pow(cosA, 5)*factor;
        }
    }
    return res;
}

void ZBuffer::interpolateNormales(const Point3D &first, const Point3D &second,
                                  int len, QVector<Point3D> &normales)
{
    if (len < 2)
        normales << (first);// + second) * 0.5;
    else
    {
        len--;
        for (int i = 0; i <= len; i++)
        {
            double t = (double) i/len;
            normales << first*(1-t) + second*t;
        }
    }
}

