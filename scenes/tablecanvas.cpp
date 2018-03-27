#include "tablecanvas.h"
#include "utils/converter.h"

#include <QHeaderView>
TableCanvas::TableCanvas()
{

    _table = new myTableWidget;
    _table->setRowCount(0);
    _table->setColumnCount(1);

    headerList << "Время";
    _table->setHorizontalHeaderLabels(headerList);
}

TableCanvas::~TableCanvas()
{
    delete _table;
}

void TableCanvas::addItem(const shared_ptr<Item> &item)
{
    _table->setColumnCount(++_objsCount+1);
    headerList << item->objectName();
    _table->setHorizontalHeaderLabels(headerList);
    Canvas::addItem(item);
}

void TableCanvas::removeItem(const shared_ptr<Item> &item)
{
    for(int i = 0; i < _objsCount; i++)
    {
        if (item == items[i])
        {
            _table->removeColumn(i+1);
            _objsCount--;
        }
    }
    Canvas::removeItem(item);
}

void TableCanvas::setHeader(int objId, const QString &header)
{
    if (objId > _objsCount)
        return;
    headerList[objId+1] = header;
    _table->setHorizontalHeaderLabels(headerList);
}

#include <QTime>
void TableCanvas::setTrackInfo(int objId, const float pos)
{
    if (objId > _objsCount)
        return;

    if (!_coordsCount)
        baseTime = _currentTime;

    QTime t = TimeConverter::secToQTime(
                TimeConverter::QTimeToSec(_currentTime) -
                TimeConverter::QTimeToSec(baseTime)
                );
    double st = TimeConverter::QTimeToSec(t)/_timeScale;
    if (!_coordsCount || _times.last() != t)
    {
        appendRow();
        _table->item(_coordsCount-1, 0)->setText(QString::number(st));
        _times << t;
    }
    _table->item(_coordsCount-1, objId+1)->setText(QString::number(pos));
}

void TableCanvas::setTimeValues(const QVector<QTime> &times)
{
    Canvas::setTimeValues(times);

    int len =  times.length();
    int diff = len -_coordsCount;
    while (diff > 0)
    {
        appendRow();
        diff--;
    }
    for (int i = 0; i < len; i++)
    {
        double stime = TimeConverter::QTimeToSec(times[i]) / _timeScale;
        _table->item(i,0)->setText(QString::number(stime));
    }

    if (!times.isEmpty())
        baseTime = times.first();
}

void TableCanvas::setCoordsValues(int obj, const QVector<double> &values)
{
    int len =  values.length();
    int diff = len -_coordsCount;
    while (diff > 0)
    {
        appendRow();
        diff--;
    }
    for (int i = 0; i < len; i++)
        _table->item(i, obj+1)->setText(QString::number(values[i]));
}

QVector<double> TableCanvas::coordsValues(int obj) const
{
    QVector<double> result;
    for (int i = 0; i < _coordsCount; i++)
        result << _table->item(i,obj+1)->text().toDouble();
    return result;
}

#include <QFile>
bool TableCanvas::save(const QString &filename)
{
    QFile file(filename + ".txt");
    if (!file.open(QIODevice::WriteOnly))
        return false;

    foreach(QString header, headerList)
        file.write(QString(header + '\t').toLocal8Bit());
    file.putChar('\n');

    for (int i = 0; i < _table->rowCount(); i++)
    {
        for (int j = 0; j < _table->columnCount(); j++)
            file.write(QString(_table->item(i,j)->text() + '\t').toLocal8Bit());
        file.putChar('\n');
    }
    file.close();
    return true;
}

void TableCanvas::appendRow()
{
    _coordsCount++;
    _table->setRowCount(_coordsCount);
    for (int i = 0; i < _objsCount+1; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        _table->setItem(_coordsCount-1, i, item);
    }
}

