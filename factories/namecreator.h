#ifndef NAMECREATOR_H
#define NAMECREATOR_H

#include <QString>

class NameCreator
{
public:
    int _pointTag;
    int _diaTag;
    int _sceneId;
    static NameCreator &getInstance();

    QString createPointName();
    QString createDiaName();
    int createSceneId();

    NameCreator(const NameCreator &) = delete;
    NameCreator &operator =(const NameCreator &) = delete;

private:
    NameCreator();
};

#endif // NAMECREATOR_H
