#include "table_vt_factory.h"
#include "dialog/tabledialog.h"
#include "scenes/tablext.h"
#include "scenes/graphcanvas.h"
#include "tracking/derivativecentral.h"

TableVTFactory::TableVTFactory(QVector<shared_ptr<Scene>> scenes) :
    _scenes(scenes)
{
    dia = new TableDialog;
}

shared_ptr<Scene> TableVTFactory::create()
{
    table = make_unique<TableVT>();
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
            createFromResource(resource);

            QVector<double> dtimes;
            QVector<QTime> times = table->timeValues();
            for (int i = 0; i < times.length(); i++)
                dtimes << TimeConverter::QTimeToSec(times[i]);

            DerivativeRunge<double> der;
            der.setX(VectorConverter::QVectorToArray(dtimes));

            for (int i = 0; i < resource->objsCount(); i++)
            {
                const QVector<double> coefs = resource->getApprCoef(i);
                if (coefs.isEmpty())
                {
                    QVector<double> coords = resource->coordsValues(i);
                    der.setY(VectorConverter::QVectorToArray(coords));
                    QVector<double> res = VectorConverter::arrayToQVector(der.calculate());

                    QVector<double> prev = resource->prevCoordsValues(i);
                    if (prev.length() > 1 && res.length() > 0)
                        res[0] = calcV0(prev, coords[0], dtimes[0], dtimes[0]-dtimes[1]);

                    QVector<double> next = resource->nextCoordsValues(i);
                    int l = coords.length();
                    if (next.length() > 0 && res.length() > 0)
                        res[res.length()-1] = calcVN(next, coords[l-1], coords[l-2], dtimes.last(), dtimes[1]-dtimes[0]);

                    table->setCoordsValues(i, res);
                    table->update();
                }
                else
                {
                    QVector<double> speed;
                    QVector<double> speedCoefs;
                    for (int l = 1; l < coefs.size(); l++)
                        speedCoefs << l*coefs[l];
                    for (int k = 0; k < dtimes.size(); k++)
                    {
                        double val = 0;
                        for (int l = 0; l < speedCoefs.size(); l++)
                            val += speedCoefs[l]*qPow(dtimes[k]/resource->timeScale(), l);
                        speed << val;

                    }
                    table->setApprCoef(i, speedCoefs);
                    table->setCoordsValues(i, speed);
                }
            }

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


