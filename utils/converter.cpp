#include "converter.h"

QTime TimeConverter::msecToQTime(qint64 msec)
{
    qint64 sec = msec/1000;
    return QTime((sec/3600)%60, (sec/60)%60, sec%60, msec%1000);
}

qint64 TimeConverter::QTimeToMsec(const QTime &time)
{
    return time.hour()*3600000 +
            time.minute()*60000 +
            time.second()*1000 +
            time.msec();
}

QTime TimeConverter::secToQTime(double sec)
{
    int secInt = (int) sec;
    int msec = (sec - secInt)*1000;
    return QTime((secInt/3600)%60, (secInt/60)%60, secInt%60, msec);
}

double TimeConverter::QTimeToSec(const QTime &time)
{
    return time.hour()*3600 +
            time.minute()*60 +
            time.second() +
            time.msec()/1000.;
}


QVector<double> VectorConverter::arrayToQVector(const Array<double> &array)
{
    QVector<double> res;
    for (int i = 0; i < array.size(); i++)
        res << array[i];
    return res;
}

Array<double> VectorConverter::QVectorToArray(const QVector<double> &vector)
{
    int N = vector.size();
    Array<double> res(N);
    for (int i = 0; i < N; i++)
        res[i] = vector[i];
    return res;
}
