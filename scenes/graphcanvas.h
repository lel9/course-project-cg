#ifndef GRAPHCANVAS_H
#define GRAPHCANVAS_H

#include "canvas.h"
#include "qcustomplot/qcustomplot.h"

#include <QAction>

class myCustomPlot : public QCustomPlot
{
    Q_OBJECT

public:
    myCustomPlot()
    {
        menu = new QMenu;
        mirrorX = new QAction("Отразить по оси X", this);
        showProperties = new QAction("Свойства...", this);
        showLegend = new QAction("Скрыть легенду", this);
        menu->addAction(mirrorX);
        menu->addAction(showLegend);
        menu->addAction(showProperties);

        connect(mirrorX, SIGNAL(triggered(bool)), this, SLOT(on_mirrorX_triggered()));
        connect(showLegend, SIGNAL(triggered(bool)), this, SLOT(on_showLegend_triggered()));
        connect(showProperties, SIGNAL(triggered(bool)), this, SLOT(on_showProperties_triggered()));
    }

    ~myCustomPlot()
    {
        delete menu;
        delete mirrorX;
        delete showProperties;
        delete showLegend;
    }

    void closeEvent(QCloseEvent *)
    {
        this->hide();
    }

    void contextMenuEvent(QContextMenuEvent *event)
    {
        menu->exec(event->globalPos());
    }

public slots:
    void on_mirrorX_triggered()
    {
        emit mirrorXAction();
    }

    void on_showProperties_triggered()
    {
        emit propAction();
    }

    void on_showLegend_triggered()
    {
        if (showLegend->text() == "Показать легенду")
        {
            showLegend->setText("Скрыть легенду");
            emit showLeg(true);
        }
        else if (showLegend->text() == "Скрыть легенду")
        {
            showLegend->setText("Показать легенду");
            emit showLeg(false);
        }

    }

signals:
    void mirrorXAction();
    void propAction();
    void showLeg(bool);

private:
    QMenu *menu;
    QAction *mirrorX;
    QAction *showProperties;
    QAction *showLegend;
};

#include "dialog/graphdialog.h"

class GraphCanvas : public Canvas
{
    Q_OBJECT

public:
    GraphCanvas();
    ~GraphCanvas();
    virtual void addItem(const shared_ptr<Item> &item);
    virtual void removeItem(const shared_ptr<Item> &item);

    virtual void setHeader(int objId, const QString &header) override;
    virtual void setColor(int objId, const QColor &color) override;
    virtual void setTrackInfo(int objId, const float pos) override;

    virtual void setCoefs(int i, const QVector<double> &coefs) override;

    virtual void setCoordsValues(int objId, const QVector<double> &values) override;
    virtual QVector<double> coordsValues(int objId) const override;

    virtual QWidget *widget() { return _plot; }

    virtual bool save(const QString &filename) override;

public slots:
    void on_mirrorX_triggered();
    void on_prop_triggered();
    void on_legend_triggered(bool cond);

private:
    myCustomPlot *_plot;
    QStringList headerList;
    GraphDialog *dia;
};

#endif // GRAPHCANVAS_H
