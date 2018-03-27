#include "namecreator.h"

NameCreator &NameCreator::getInstance()
{
    static NameCreator nameCreator;
    return nameCreator;
}

QString NameCreator::createPointName()
{
    return("Точка " + QString::number(++_pointTag));
}

QString NameCreator::createDiaName()
{
    return("Диаграмма " + QString::number(++_diaTag));
}

int NameCreator::createSceneId()
{
    return (_sceneId++);
}

NameCreator::NameCreator() :
    _pointTag(0),
    _diaTag(0),
    _sceneId(0)
{
}


