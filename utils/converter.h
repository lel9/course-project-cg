#ifndef TIMECONVERTER_H
#define TIMECONVERTER_H

#include <QTime>

class TimeConverter
{
public:
    TimeConverter() = default;
    static QTime msecToQTime(qint64 msec);
    static qint64 QTimeToMsec(const QTime &time);
    static QTime secToQTime(double sec);
    static double QTimeToSec(const QTime &time);

};

#include <QVector>
#include "matrix.h"

class VectorConverter
{
public:
    VectorConverter() = default;
    static QVector<double> arrayToQVector(const Array<double> &array);
    static Array<double> QVectorToArray(const QVector<double> &vector);
};

#endif // TIMECONVERTER_H
