#include "graphcanvas.h"
#include "utils/converter.h"

GraphCanvas::GraphCanvas()
{
    _plot = new myCustomPlot;
    _plot->legend->setVisible(true);
    _plot->setInteraction(QCP::iRangeZoom,true);   // Включаем взаимодействие удаления/приближения
    _plot->setInteraction(QCP::iRangeDrag, true);  // Включаем взаимодействие перетаскивания графика
    _plot->axisRect()->setRangeDrag(Qt::Horizontal);   // Включаем перетаскивание только по горизонтальной оси
    _plot->axisRect()->setRangeZoom(Qt::Horizontal);   // Включаем удаление/приближение только по горизонтальной оси

    connect(_plot, SIGNAL(mirrorXAction()), this, SLOT(on_mirrorX_triggered()));
    connect(_plot, SIGNAL(propAction()), this, SLOT(on_prop_triggered()));
    connect(_plot, SIGNAL(showLeg(bool)), this, SLOT(on_legend_triggered(bool)));

    dia = new GraphDialog;
}

GraphCanvas::~GraphCanvas()
{
    delete _plot;
    delete dia;
}

void GraphCanvas::addItem(const shared_ptr<Item> &item)
{
    _plot->addGraph();
    _plot->graph(_objsCount)->setPen(QPen(item->color()));
    _plot->graph(_objsCount)->setName(item->objectName());
    _objsCount++;
    _coefs << QVector<double>();
    _plot->rescaleAxes();
    _plot->replot();

    Canvas::addItem(item);
}

void GraphCanvas::removeItem(const shared_ptr<Item> &item)
{
    for (int i = 0; i < _objsCount; i++)
    {
        if (item == items[i])
        {
            _plot->removeGraph(i);
            _coefs.removeAt(i);
            _objsCount--;
        }
    }
    _plot->rescaleAxes();
    _plot->replot();

    Canvas::removeItem(item);
}

void GraphCanvas::setHeader(int objId, const QString &header)
{
    if (objId > _objsCount)
        return;

    _plot->graph(objId)->setName(header);
    _plot->replot();
}

void GraphCanvas::setColor(int objId, const QColor &color)
{
    if (objId > _objsCount)
        return;

    _plot->graph(objId)->setPen(QPen(color));
    _plot->replot();
}

void GraphCanvas::setTrackInfo(int objId, const float pos)
{
    if (objId > _objsCount)
        return;

    if (!_coordsCount)
        baseTime = _currentTime;

    QTime t = TimeConverter::secToQTime(
                TimeConverter::QTimeToSec(_currentTime) -
                TimeConverter::QTimeToSec(baseTime)
                );

    if (!_coordsCount || _times.last() != t)
    {
        _times << t;
        _coordsCount++;
    }

    double sec = TimeConverter::QTimeToSec(_times.last()) / _timeScale;

    _plot->graph(objId)->addData(sec, pos);
    _plot->rescaleAxes();
    _plot->replot();
}

void GraphCanvas::setCoefs(int i, const QVector<double> &coefs)
{
    _coefs[i] = coefs;
}

#define POINT_COUNT 50

double calcX(const QVector<double> &coefs, double x)
{
    double res = 0;
    for (int i = 0; i < coefs.length(); i++)
        res += qPow(x, i) * coefs[i];
    return res;
}

void GraphCanvas::setCoordsValues(int objId, const QVector<double> &values)
{
    if (objId > _objsCount)
        return;

    _coordsCount = values.length();
    QVector<double> dtimes;
    QVector<double> apprval;

    QVector<double> coefs = _coefs[objId];
    if (!coefs.isEmpty())
    {
        for (int i = 0; i < _coordsCount - 1; i++)
        {
            double delta = TimeConverter::QTimeToSec(_times[i+1]) - TimeConverter::QTimeToSec(_times[i]);
            double h = delta / POINT_COUNT;
            for (int j = 0; j < POINT_COUNT; j++)
            {
                dtimes << (TimeConverter::QTimeToSec(_times[i]) + h*j) / _timeScale;
                apprval << calcX(coefs, dtimes.last());
            }
        }
        dtimes << TimeConverter::QTimeToSec(_times.last()) / _timeScale;
        apprval << calcX(coefs, dtimes.last());
    }
    else
    {
        apprval = values;
        for (int i = 0; i < _coordsCount; i++)
            dtimes << TimeConverter::QTimeToSec(_times[i]) / _timeScale;
    }

    _plot->graph(objId)->setData(dtimes, apprval);
    _plot->rescaleAxes();
    _plot->replot();
}

QVector<double> GraphCanvas::coordsValues(int objId) const
{
    QVector<double> values;
    if (objId < _objsCount)
    {
        QList<QCPData> data = _plot->graph(objId)->data()->values();
        foreach (QCPData value, data)
            values << value.value;
    }
    return values;
}

bool GraphCanvas::save(const QString &filename)
{
    Qt::WindowStates last = _plot->windowState();
    _plot->setWindowState(Qt::WindowMaximized);
    bool res =  _plot->saveJpg(filename+".jpg");
    _plot->setWindowState(last);
    return res;
}

void GraphCanvas::on_mirrorX_triggered()
{
    for (int objId = 0; objId < _objsCount; objId++)
    {
        QVector<double> values;
        QVector<double> times;
        QList<QCPData> data = _plot->graph(objId)->data()->values();
        foreach (QCPData value, data)
        {
            times << value.key;
            values << -value.value;
        }
        _plot->graph(objId)->setData(times, values);
    }
    _plot->rescaleAxes();
    _plot->replot();
}

void GraphCanvas::on_prop_triggered()
{
    dia->setXLabel(_plot->xAxis->label());
    dia->setYLabel(_plot->yAxis->label());
    dia->setXRange(_plot->xAxis->range().lower, _plot->xAxis->range().upper);
    dia->setYRange(_plot->yAxis->range().lower, _plot->yAxis->range().upper);
    dia->exec();

    if (dia->isOk())
    {
        _plot->xAxis->setLabel(dia->xLabel());
        _plot->yAxis->setLabel(dia->yLabel());

        _plot->xAxis->setRange(dia->xStart(), dia->xStop());
        _plot->yAxis->setRange(dia->yStart(), dia->yStop());

        _plot->replot();
    }
}

void GraphCanvas::on_legend_triggered(bool cond)
{
    _plot->legend->setVisible(cond);
    _plot->replot();
}

