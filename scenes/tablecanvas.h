#ifndef TABLECANVAS_H
#define TABLECANVAS_H

#include <QTableWidget>

#include "canvas.h"
#include "objects/item.h"

class myTableWidget : public QTableWidget
{
public:
    myTableWidget() = default;
    ~myTableWidget() = default;

    void closeEvent(QCloseEvent *)
    {
        this->hide();
    }
};

class TableCanvas : public Canvas
{
    Q_OBJECT

public:
    TableCanvas();
    ~TableCanvas();

    virtual void addItem(const shared_ptr<Item> &item) override;
    virtual void removeItem(const shared_ptr<Item> &item) override;

    virtual void setHeader(int objId, const QString &header) override;
    virtual void setTrackInfo(int objId, const float pos) override;

    virtual void setTimeValues(const QVector<QTime> &times) override;
    virtual void setCoordsValues(int obj, const QVector<double> &values) override;
    virtual QVector<double> coordsValues(int obj) const override;

    virtual QWidget *widget() override { return _table; }

    virtual bool save(const QString &filename);

private:
    void appendRow();

    myTableWidget *_table;  //Q
    QStringList headerList;
};

#endif // TABLECANVAS_H
