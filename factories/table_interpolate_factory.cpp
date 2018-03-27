#include "table_interpolate_factory.h"
#include "dialog/interpolatedialog.h"
#include "tracking/interpolator.h"

TableInterpolateFactory::TableInterpolateFactory(QVector<shared_ptr<Scene>> scenes) :
     _scenes(scenes)
{
    dia = new InterpolateDialog;
}

shared_ptr<Scene> TableInterpolateFactory::create()
{
    table = make_shared<TableScene>();
    table->setObjectName(NameCreator::getInstance().createDiaName());
    execDia<shared_ptr<Scene>>(_scenes);

    if (dia->isOk())
    {
        QVector<int> indexes = dia->getSelectedIndexes();
        if (!indexes.isEmpty())
        {
            shared_ptr<Scene> resource = _scenes[indexes[0]];
            table = static_pointer_cast<TableScene>(resource->clone());
            table->setObjectName(dia->getTableName());
            createCanvas();
            createFromResource(resource);

            QVector<double> dtimes;
            QVector<QTime> times = table->timeValues();
            for (int i = 0; i < times.length(); i++)
                dtimes << TimeConverter::QTimeToSec(times[i]) / resource->timeScale();

            Interpolator<double> interpolator(dia->getOrder());
            interpolator.setX(VectorConverter::QVectorToArray(dtimes));

            for (int i = 0; i < resource->objsCount(); i++)
            {
                QVector<double> y = resource->coordsValues(i);
                for (int j = 0; j < y.length(); j++)
                {
                    y[j] *= resource->scale(); // там не масштабированные координаты
                    if (resource->type() == VT || resource->type() == AT)
                        y[j] *= resource->timeScale();
                }
                interpolator.setY(VectorConverter::QVectorToArray(y));
                QVector<double> v = VectorConverter::arrayToQVector(interpolator.calculate());
                table->setApprCoef(i, VectorConverter::arrayToQVector(interpolator.getCoefs()));
                table->setCoordsValues(i, v);
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
