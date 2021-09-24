#ifndef COMMON_H
#define COMMON_H

#include <QPointF>
#include "../math/mmath.h"

struct Control_State
{
    bool is_reset;
    bool point_changed;
    double p_x;
    double p_y;
    double angle;
};

struct State
{
    QPointF f[4];
    QPointF p;
    int max;
};


#endif // COMMON_H
