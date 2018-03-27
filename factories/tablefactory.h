#ifndef TABLEFACTORY_H
#define TABLEFACTORY_H

#include "scenefactory.h"

#include "dialog/tabledialog.h"
#include "utils/converter.h"
#include "scenes/tablescene.h"

class TableFactory : public SceneFactory
{
public:
    TableFactory();
    virtual ~TableFactory() { if (dia) delete dia; }

    virtual shared_ptr<Scene> create() = 0;
    virtual Canvas *createCanvas();
    virtual void createFromResource(shared_ptr<Scene> resource);

    template <typename T>
    void execDia(const QVector<T> &objs)
    {
        if (!dia)
            return;

        dia->setTableName(table->objectName());
        QVector<QString> names;
        foreach (T obj, objs)
            names << obj->objectName();
        dia->setPointList(names);
        dia->exec();
    }

protected:
    double calcV0(const QVector<double> &prev, double y0, double t0, double th);
    double calcVN(const QVector<double> &next, double yn, double yn1, double t0, double th);

protected:
    TableDialog *dia;
    shared_ptr<TableScene> table;
};

#endif // TABLEFACTORY_H
