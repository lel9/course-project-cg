#ifndef TABLEMIDDLEFACTORY_H
#define TABLEMIDDLEFACTORY_H


#include "tablefactory.h"

class TableMiddleFactory : public TableFactory
{
public:
    TableMiddleFactory(QVector<shared_ptr<Scene>> scenes);
    shared_ptr<Scene> create() override;

private:
    QVector<shared_ptr<Scene>> _scenes;
};

#endif // TABLEMIDDLEFACTORY_H
