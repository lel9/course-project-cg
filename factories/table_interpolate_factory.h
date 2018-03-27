#ifndef TABLEINTERPOLATEFACTORY_H
#define TABLEINTERPOLATEFACTORY_H

#include "tablefactory.h"

class TableInterpolateFactory : public TableFactory
{
public:
    TableInterpolateFactory(QVector<shared_ptr<Scene>> scenes);
    shared_ptr<Scene> create() override;

private:
    QVector<shared_ptr<Scene>> _scenes;
};

#endif // TABLEINTERPOLATEFACTORY_H
