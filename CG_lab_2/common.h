#ifndef COMMON_H
#define COMMON_H
#include <QPointF>
#include <QList>

struct State
{
    QList <QPointF> p;
    unsigned int max;
    QPointF * d;
};

#endif // COMMON_H
