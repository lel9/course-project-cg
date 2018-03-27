#ifndef TABLESCENE_H
#define TABLESCENE_H

#include "scene.h"
#include "canvas.h"

#include <QTime>

class TableScene : public Scene
{
    Q_OBJECT

public:
    TableScene();

    virtual void addChild(const shared_ptr<SceneObject> &child) override;
    virtual void addChildren(const QVector<shared_ptr<SceneObject>> &children) override;
    virtual void removeChild(const shared_ptr<SceneObject> &pos);

    virtual void setScale(double scale) override;
    void update() override;

    virtual QVector<double> coordsValues(int obj) const;
    virtual void setCoordsValues(int obj, const QVector<double> &val);

    virtual QVector<double> prevCoordsValues(int obj) const;
    virtual QVector<double> nextCoordsValues(int obj) const;

public slots:
    void updateHeader(const QString &newName);
    void updateColor(const QColor &color);
    void updateTrackInfo(const QPointF &newPointPos);

    void on_currentTimeChanged(qint64 time);

protected:
    QVector<QVector<double>> _values;
    QVector<double> baseVal;
};

#endif // TABLESCENE_H
