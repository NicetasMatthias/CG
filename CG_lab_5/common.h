#ifndef COMMON_H
#define COMMON_H

#include <QVector>
#include <QPointF>

#define MY_SIZE 5

struct PointF3D
{
    qreal x;
    qreal y;
    qreal z;
    PointF3D(qreal ix,qreal iy,qreal iz)
    {
        x = ix;
        y = iy;
        z = iz;
    }
    PointF3D()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};

struct Face
{
    QVector <PointF3D> points;
    bool visible;
    Face(PointF3D p1,PointF3D p2,PointF3D p3,PointF3D p4)
    {
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
        points.push_back(p4);
        visible = false;
    }
    Face()
    {
        visible = false;
    }
};

struct FaceD
{
    QPointF p[4];
};


struct ControlState
{
    qreal x_ang;
    qreal y_ang;
    qreal z_ang;
};

struct DrawState
{
    QVector <Face> faces;
};

#endif // COMMON_H
