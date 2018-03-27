#include "table_middle_factory.h"

TableMiddleFactory::TableMiddleFactory(QVector<shared_ptr<Scene>> scenes) :
     _scenes(scenes)
{
    dia = new TableDialog;
}

shared_ptr<Scene> TableMiddleFactory::create()
{
    table = make_shared<TableScene>();
    table->setObjectName(NameCreator::getInstance().createDiaName());
    dia->setGroupBoxTitle("Выберете диаграмму для расчета среднего");
    execDia<shared_ptr<Scene>>(_scenes);

    if (dia->isOk())
    {
        QVector<int> indexes = dia->getSelectedIndexes();
        if (!indexes.isEmpty())
        {
            shared_ptr<Scene> resource = _scenes[indexes[0]];
            if (resource->objsCount() != 0)
            {
                table = static_pointer_cast<TableScene>(resource->clone());
                table->setObjectName(dia->getTableName());
                createCanvas();
                createFromResource(resource);
                QVector<shared_ptr<SceneObject>> children = table->getChildren();
                for (int i = 1; i < children.length(); i++)
                    table->removeChild(children[i]);


                QVector<double> middleVal;
                QVector<QVector<double>> tableVal;
                for (int j = 0; j < resource->objsCount(); j++)
                    tableVal << resource->coordsValues(j);

                for (int i = 0; i < tableVal.first().length(); i++)
                {
                    double val = 0;
                    for (int j = 0; j < resource->objsCount(); j++)
                        val += tableVal[j][i];
                    middleVal << val/resource->objsCount();
                }

                table->setCoordsValues(0, middleVal);
                if (resource->getApprCoef(0).isEmpty())
                    table->update();

                table->setId(NameCreator::getInstance().createSceneId());
                _isCreated = true;
            }
        }
    }
    else
    {
        NameCreator::getInstance()._diaTag--;
        table.reset();
    }

    return table;
}
