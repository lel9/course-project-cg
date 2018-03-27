#ifndef TABLEXT_H
#define TABLEXT_H

#include "tablescene.h"

class TableXT : public TableScene
{
    Q_OBJECT
private:
    QVector<QVector<QPointF>> prevPos;
public:
    TableXT();
    virtual void addChild(const shared_ptr<SceneObject> &child) override;
    virtual void addChildren(const QVector<shared_ptr<SceneObject>> &children) override;
    virtual void removeChild(const shared_ptr<SceneObject> &pos) override;

    virtual QVector<double> prevCoordsValues(int obj) const;

    virtual void update();

    virtual Type type() override { return XT; }
    virtual shared_ptr<Scene> clone() override { return make_shared<TableXT>(); }

private slots:
    void updatePrevPos(QVector<QPointF> pos);
};

class TableVT : public TableScene
{
public:
    TableVT();

    virtual Type type() override { return VT; }
    virtual shared_ptr<Scene> clone() override { return make_shared<TableVT>(); }
};

class TableAT : public TableScene
{
public:
    TableAT() { }
    virtual void update() override;
    virtual Type type() override { return AT; }
    virtual shared_ptr<Scene> clone() override { return make_shared<TableAT>(); }
};

class TableFT : public TableScene
{
private:
    double m;
public:
    TableFT() { }
    virtual void update() override;
    virtual Type type() override { return FT; }
    virtual shared_ptr<Scene> clone() override { return make_shared<TableFT>(); }

    virtual void setCoordsValues(int obj, const QVector<double> &val) override;

    void setM(double massa) { m = massa; }
    double Massa() { return m; }
};

#endif // TABLEXT_H
