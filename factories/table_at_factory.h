#ifndef TABLEATFACTORY_H
#define TABLEATFACTORY_H

#include "tablefactory.h"
#include "scenes/tablext.h"

class TableATFactory : public TableFactory
{
public:
    TableATFactory() { table = make_shared<TableAT>(); }
    TableATFactory(QVector<shared_ptr<Scene>> scenes);

    shared_ptr<Scene> create() override;

    shared_ptr<Scene> fastCreate(const shared_ptr<Scene> &resource);

private:
    double calcStartAV(const QVector<double> &pos, double time0, double y0, double h);
    double calcStartAX(const QVector<double> &prev, double t0, double y0, double th);

private:
    QVector<shared_ptr<Scene>> _scenes;
};

#endif // TABLEATFACTORY_H
