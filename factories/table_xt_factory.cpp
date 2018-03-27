#include "table_xt_factory.h"
#include "dialog/tabledialog.h"
#include "scenes/tablext.h"
#include "scenes/graphcanvas.h"

TableXTFactory::TableXTFactory(QVector<shared_ptr<SceneObject>> points) :
    _points(points)
{
    dia = new TableDialog;
}

shared_ptr<Scene> TableXTFactory::create()
{
    table = make_unique<TableXT>();
    table->setObjectName(NameCreator::getInstance().createDiaName());

    dia->setMultiSelection(true);
    execDia<shared_ptr<SceneObject>>(_points);

    if (dia->isOk())
    {
        table->setObjectName(dia->getTableName());
        createCanvas();

        QVector<int> indexes = dia->getSelectedIndexes();
        foreach(int i, indexes)
            table->addChild(_points[i]);

        table->setId(NameCreator::getInstance().createSceneId());
        _isCreated = true;
    }
    else
    {
        NameCreator::getInstance()._diaTag--;
        table.reset();
    }

    return table;
}
