#ifndef TABLEFTFACTORY_H
#define TABLEFTFACTORY_H

#include "tablefactory.h"

class TableFTFactory : public TableFactory
{
public:
    TableFTFactory(QVector<shared_ptr<Scene>> scenes);
    shared_ptr<Scene> create() override;

private:
    QVector<shared_ptr<Scene>> _scenes;
};

#endif // TABLEFTFACTORY_H
