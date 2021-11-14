#ifndef COMMON_H
#define COMMON_H

#include <QPointF>
#include <QLineF>
#include <vector>

struct MyLineF
{
    QLineF line;
    short visible;  // 0 - полностью вне окна
                    // 1 - полностью в окне
                    // 2 - частично в окне
    std::vector <qreal> t;
};

struct ControlState
{
    QPointF p1;
    QPointF p2;
    size_t sec_num;
};

struct DrawState
{
    QPointF p[4];
    std::vector <MyLineF> sec;
    int lim;
};


#endif // COMMON_H
