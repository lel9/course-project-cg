#include "table_at_factory.h"
#include "dialog/tabledialog.h"
#include "scenes/graphcanvas.h"
#include "tracking/derivativecentral.h"

TableATFactory::TableATFactory(QVector<shared_ptr<Scene>> scenes) :
    _scenes(scenes)
{
    dia = new TableDialog;
}

shared_ptr<Scene> TableATFactory::create()
{
    table = make_unique<TableAT>();
    table->setObjectName(NameCreator::getInstance().createDiaName());

    dia->setGroupBoxTitle("Выберете XT диаграмму для расчета");
    execDia<shared_ptr<Scene>>(_scenes);

    if (dia->isOk())
    {
        table->setObjectName(dia->getTableName());
        createCanvas();

        QVector<int> indexes = dia->getSelectedIndexes();
        if (!indexes.isEmpty())
        {
            shared_ptr<Scene> resource = _scenes[indexes[0]];
            fastCreate(resource);
            table->setId(NameCreator::getInstance().createSceneId());
            _isCreated = true;
        }
    }
    else
    {
        NameCreator::getInstance()._diaTag--;
        table.reset();
    }

    return table;
}

shared_ptr<Scene> TableATFactory::fastCreate(const shared_ptr<Scene> &resource)
{
    createFromResource(resource);
    QVector<QTime> times = resource->timeValues();
    QVector<double> dtimes;
    for (int i = 0; i < times.length(); i++)
        dtimes << TimeConverter::QTimeToSec(times[i]);

    DerivativeRunge<double> der;
    der.setX(VectorConverter::QVectorToArray(dtimes));

    DerivativeRunge<double> derOne;
    derOne.setX(VectorConverter::QVectorToArray(dtimes));

    for (int i = 0; i < resource->objsCount(); i++)
    {
        const QVector<double> coefs = resource->getApprCoef(i);

        QVector<double> values;
        QVector<double> yVal = resource->coordsValues(i);

        if (coefs.isEmpty())
        {
            if (resource->type() == XT)
            {
                der.setY(VectorConverter::QVectorToArray(yVal));
                Array<double> res1 = der.calculate();
                QVector<double> pos = resource->prevCoordsValues(i);

                if (pos.size() > 1 && !yVal.isEmpty())
                    res1[0] = calcV0(pos, dtimes[0], yVal[0], dtimes[0] - dtimes[1]);

                derOne.setY(res1);
                values = VectorConverter::arrayToQVector(derOne.calculate());

                if (pos.size() > 1 && !yVal.isEmpty())
                    values[0] = calcStartAX(pos, dtimes[0], yVal[0], dtimes[0]-dtimes[1]);
            }
            else if (resource->type() == VT)
            {
                derOne.setY(VectorConverter::QVectorToArray(yVal));
                Array<double> res1 = derOne.calculate();

                QVector<double> pos = resource->prevCoordsValues(i);

                values = VectorConverter::arrayToQVector(res1);
                if (pos.size() > 1 && !yVal.isEmpty())
                    values[0] = calcStartAV(pos, dtimes[0], yVal[0], dtimes[1]-dtimes[0]);
            }



            table->setCoordsValues(i, values);
            table->update();
        }

        else
        {
            QVector<double> a;
            QVector<double> acoefs;
            if (resource->type() == XT)
                for (int l = 2; l < coefs.size(); l++)
                    acoefs << coefs[l]*l*(l-1);
            else if (resource->type() == VT)
                for (int l = 1; l < coefs.size(); l++)
                    acoefs << coefs[l]*l;

            for (int k = 0; k < dtimes.size(); k++)
            {
                double val = 0;
                for (int l = 0; l < acoefs.size(); l++)
                    val += qPow(dtimes[k]/resource->timeScale(), l)*acoefs[l];
                a << val;
            }
            table->setApprCoef(i, acoefs);
            table->setCoordsValues(i, a);
        }
    }

    return table;
}

double TableATFactory::calcStartAV(const QVector<double> &pos, double time0, double y0, double h)
{
    int n = pos.size();
    QVector<double> x;
    for (int i = 1; i <= n; i++)
        x << time0 - h*i;

    DerivativeCentral<double> derV1;
    derV1.setX(VectorConverter::QVectorToArray(x));
    derV1.setY(VectorConverter::QVectorToArray(pos));
    QVector<double> v1 = VectorConverter::arrayToQVector(derV1.calculate());

    return (y0-v1[0]) / h;
}

double TableATFactory::calcStartAX(const QVector<double> &prev, double t0, double y0, double th)
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

    Array<double> res = der.calculate(); // посчитали V

    return (res[0]-res[1])/-th;
}
