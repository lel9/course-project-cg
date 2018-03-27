#include "table_ft_factory.h"
#include "scenes/tablext.h"
#include "dialog/tableftdialog.h"
#include "table_at_factory.h"

TableFTFactory::TableFTFactory(QVector<shared_ptr<Scene>> scenes) :
    _scenes(scenes)
{
    dia = new TableFTDialog;
}


shared_ptr<Scene> TableFTFactory::create()
{
    table = make_unique<TableFT>();
    table->setObjectName(NameCreator::getInstance().createDiaName());

    dia->setGroupBoxTitle("Выберете XT или AT диаграмму для расчета");
    execDia<shared_ptr<Scene>>(_scenes);

    if (dia->isOk())
    {
        table->setObjectName(dia->getTableName());
        createCanvas();

        QVector<int> indexes = dia->getSelectedIndexes();
        if (!indexes.isEmpty())
        {
            shared_ptr<Scene> resource = _scenes[indexes[0]];
            shared_ptr<Scene> res = resource;
            if (resource->type() == XT)
            {
                TableATFactory f;
                res = f.fastCreate(resource);
            }

            createFromResource(resource);

            shared_ptr<TableFT> ft = static_pointer_cast<TableFT>(table);
            ft->setM(dia->getM());
            for (int i = 0; i < resource->objsCount(); i++)
                table->setCoordsValues(i, res->coordsValues(i));
            table->update();
        }

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
