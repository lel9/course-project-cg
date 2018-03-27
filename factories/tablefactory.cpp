#include "tablefactory.h"

#include "scenes/tablecanvas.h"
#include "scenes/graphcanvas.h"

TableFactory::TableFactory() : dia(nullptr)
{

}

Canvas *TableFactory::createCanvas()
{
    Canvas *canvas = nullptr;
    switch (dia->getCheckedRadioButton())
    {
    case 0:
        canvas = new TableCanvas;
        break;
    case 1:
        canvas = new GraphCanvas;
        break;
    }
    table->setCanvas(canvas);
    canvas->widget()->setWindowTitle(table->objectName());

    return canvas;
}

void TableFactory::createFromResource(shared_ptr<Scene> resource)
{
    table->addChildren(resource->getChildren());
    table->setTimeFormat(resource->timeFormat());
    table->setScale(resource->scale());
    table->setTimeScale(resource->timeScale());
    QVector<QTime> times = resource->timeValues();
    table->setTimeValues(times);
}

#include "tracking/derivativecentral.h"

double TableFactory::calcV0(const QVector<double> &prev, double y0, double t0, double th)
{
    QVector<double> y = prev;
    y.insert(0, y0);

    int n = y.length();
    QVector<double> x;
    for (int i = 0; i < n; i++)
        x << t0 + i*th;

    DerivativeCentral<double> der;
    der.setX(VectorConverter::QVectorToArray(x));
    der.setY(VectorConverter::QVectorToArray(y));

    return der.calculate()[0];
}

double TableFactory::calcVN(const QVector<double> &next, double yn, double yn1, double t0, double th)
{
    QVector<double> y = next;
    y.insert(0, yn);
    y.insert(0, yn1);

    int n = y.length();
    QVector<double> x;
    for (int i = 0; i < n-1; i++)
        x << t0 + i*th;
    x.insert(0, t0-th);

    DerivativeCentral<double> der;
    der.setX(VectorConverter::QVectorToArray(x));
    der.setY(VectorConverter::QVectorToArray(y));

    return der.calculate()[1];
}

