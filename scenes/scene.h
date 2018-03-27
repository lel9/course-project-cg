#ifndef SCENE_H
#define SCENE_H

#include "objects/scene_object.h"
#include "canvas.h"

enum Type { Video, Animate, XT, VT, AT, FT, UnknownType };

class Scene : public QObject
{
    Q_OBJECT

public:
    explicit Scene();
    virtual ~Scene();

    virtual Type type() { return UnknownType; }
    virtual shared_ptr<Scene> clone() { return nullptr; }
    virtual void setCanvas(Canvas *canvas);

    virtual void addChild(const shared_ptr<SceneObject> &child);
    virtual void addChildren(const QVector<shared_ptr<SceneObject>> &children);
    virtual void removeChild(const shared_ptr<SceneObject> &pos);

    virtual QVector<shared_ptr<SceneObject>> selectedChildren() const;
    virtual QVector<shared_ptr<SceneObject>> &getChildren();

    virtual void setScale(double scale);
    virtual double scale() const;
    virtual void setTimeScale(double scale);
    virtual double timeScale() const;

    virtual void update() { }

    int id() const;
    void setId(int id);
    int parentId() const;
    void setParentId(int id) { _parentId = id; }

    // делегаты
    virtual QWidget *widget();

    virtual bool loadDataFromFile(const QString &);
    virtual bool save(QString &dir);

    virtual void setTrackInfo(int obj, const float info);
    virtual void setTimeValues(const QVector<QTime> &val);
    virtual void setCoordsValues(int obj, const QVector<double> &val);

    virtual QVector<double> coordsValues(int obj) const;
    virtual QVector<double> prevCoordsValues(int obj) const;
    virtual QVector<double> nextCoordsValues(int obj) const;

    virtual QVector<QTime> timeValues() const;
//    virtual QTime startTrackTime(int obj) const;
//    virtual QTime stopTrackTime(int obj) const;

    virtual QTime baseTime() const;

    virtual int coordsCount() const;
    virtual int objsCount() const;

    virtual const QVector<double> &getApprCoef(int i) const;
    virtual void setApprCoef(int i, const QVector<double> &coefs);

    virtual QString timeFormat() const;
    virtual void setTimeFormat(const QString &format);

    virtual void setEnabled(bool enable);
    virtual void setCursor(const QCursor &cursor);

    signals:
    void updateCursorPos(QPointF);

protected:
    Canvas *_canvas;
    QVector<shared_ptr<SceneObject>> _children;
    double _scale;
    int _id;

    int _parentId;

    QVector<QVector<double>> apprCoef;

};

#endif // SCENE_H
