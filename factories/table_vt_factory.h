#ifndef TABLEVTFACTORY_H
#define TABLEVTFACTORY_H

#include "tablefactory.h"

class TableVTFactory : public TableFactory
{
public:
    TableVTFactory(QVector<shared_ptr<Scene>> scenes);

    shared_ptr<Scene> create() override;
private:
    QVector<shared_ptr<Scene>> _scenes;
};

#endif // TABLEVTFACTORY_H
