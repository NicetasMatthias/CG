#include "application.h"

#define SIZE 5

Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    d = new DrawWindow;
    d->show();
    m = new MainWindow;
    m->show();
    default_points.push_back(PointF3D(-MY_SIZE,MY_SIZE,MY_SIZE));
    default_points.push_back(PointF3D(MY_SIZE,MY_SIZE,MY_SIZE));
    default_points.push_back(PointF3D(MY_SIZE,-MY_SIZE,MY_SIZE));
    default_points.push_back(PointF3D(-MY_SIZE,-MY_SIZE,MY_SIZE));
    default_points.push_back(PointF3D(-MY_SIZE,MY_SIZE,-MY_SIZE));
    default_points.push_back(PointF3D(MY_SIZE,MY_SIZE,-MY_SIZE));
    default_points.push_back(PointF3D(MY_SIZE,-MY_SIZE,-MY_SIZE));
    default_points.push_back(PointF3D(-MY_SIZE,-MY_SIZE,-MY_SIZE));
    O = PointF3D(0,0,0);
    H = PointF3D(0,0,MY_SIZE*50);

    connect(m,SIGNAL(send_control(ControlState*)),
            this,SLOT(get_control(ControlState*)));
    connect(this,SIGNAL(send_draw(DrawState*)),
            d,SLOT(get_draw(DrawState*)));
    emit m->send_control(m->get_state());
}

void Application::get_control(ControlState *c)
{
    DrawState *d = new DrawState;
    QVector <PointF3D> points;
    double x_ang = 2*M_PI*c->x_ang/360;
    double y_ang = 2*M_PI*c->y_ang/360;
    double z_ang = 2*M_PI*c->z_ang/360;

    Mmatrix Tx(3,3),Ty(3,3),Tz(3,3);

    //Матрица поворота по x
    Tx.data[0][0] = 1;
    Tx.data[0][1] = 0;
    Tx.data[0][2] = 0;
    Tx.data[1][0] = 0;
    Tx.data[1][1] = cos(x_ang);
    Tx.data[1][2] = -sin(x_ang);
    Tx.data[2][0] = 0;
    Tx.data[2][1] = sin(x_ang);
    Tx.data[2][2] = cos(x_ang);

    //Матрица поворота по y
    Ty.data[0][0] = cos(y_ang);
    Ty.data[0][1] = 0;
    Ty.data[0][2] = sin(y_ang);
    Ty.data[1][0] = 0;
    Ty.data[1][1] = 1;
    Ty.data[1][2] = 0;
    Ty.data[2][0] = -sin(y_ang);
    Ty.data[2][1] = 0;
    Ty.data[2][2] = cos(y_ang);

    //Матрица поворота по z
    Tz.data[0][0] = cos(z_ang);
    Tz.data[0][1] = -sin(z_ang);
    Tz.data[0][2] = 0;
    Tz.data[1][0] = sin(z_ang);
    Tz.data[1][1] = cos(z_ang);
    Tz.data[1][2] = 0;
    Tz.data[2][0] = 0;
    Tz.data[2][1] = 0;
    Tz.data[2][2] = 1;

    for (qsizetype i = 0; i < default_points.length(); i++)
    {
        Mmatrix tmp(1,3),res(1,3);
        tmp.data[0][0] = default_points[i].x;
        tmp.data[0][1] = default_points[i].y;
        tmp.data[0][2] = default_points[i].z;

        res = ((tmp * Tx) *Ty) * Tz;

        points.push_back(PointF3D(res.data[0][0],res.data[0][1],res.data[0][2]));
    }

    d->faces.push_back(Face(points[0],points[1],points[2],points[3]));
    d->faces.push_back(Face(points[0],points[4],points[5],points[1]));
    d->faces.push_back(Face(points[3],points[2],points[6],points[7]));
    d->faces.push_back(Face(points[0],points[4],points[7],points[3]));
    d->faces.push_back(Face(points[1],points[5],points[6],points[2]));
    d->faces.push_back(Face(points[4],points[7],points[6],points[5]));

    for (qsizetype i = 0; i < d->faces.length(); i++)
    {
        d->faces[i].visible = is_visible(d->faces[i]);
    }

    emit send_draw(d);
    return;
}

bool Application::is_visible(Face f)
{
    Mmatrix To(3,3),Th(3,3);

    //Матрица для O
    To.data[0][0] = O.x-f.points[0].x;
    To.data[0][1] = O.y-f.points[0].y;
    To.data[0][2] = O.z-f.points[0].z;
    To.data[1][0] = f.points[1].x-f.points[0].x;
    To.data[1][1] = f.points[1].y-f.points[0].y;
    To.data[1][2] = f.points[1].z-f.points[0].z;
    To.data[2][0] = f.points[2].x-f.points[0].x;
    To.data[2][1] = f.points[2].y-f.points[0].y;
    To.data[2][2] = f.points[2].z-f.points[0].z;

    //Матрица для H
    Th.data[0][0] = H.x-f.points[0].x;
    Th.data[0][1] = H.y-f.points[0].y;
    Th.data[0][2] = H.z-f.points[0].z;
    Th.data[1][0] = f.points[1].x-f.points[0].x;
    Th.data[1][1] = f.points[1].y-f.points[0].y;
    Th.data[1][2] = f.points[1].z-f.points[0].z;
    Th.data[2][0] = f.points[2].x-f.points[0].x;
    Th.data[2][1] = f.points[2].y-f.points[0].y;
    Th.data[2][2] = f.points[2].z-f.points[0].z;

    if (To.determinant()*Th.determinant() < 0)
    {
        return true;
    }
    {
        return false;
    }
}
