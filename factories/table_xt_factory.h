#ifndef TABLEXTFACTORY_H
#define TABLEXTFACTORY_H

#include "tablefactory.h"

class TableXTFactory : public TableFactory
{
public:
    TableXTFactory(QVector<shared_ptr<SceneObject>> points);
    ~TableXTFactory() = default;

    shared_ptr<Scene> create();

    void createFromResource(shared_ptr<Scene>) override { }
private:
    QVector<shared_ptr<SceneObject>> _points;
};

#endif // TABLEXTFACTORY_H
