#include "application.h"

#define STEP 0.04


Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    m = new MainWindow;
    m->show();
    d = new DrawWindow;
    d->show();
    connect(m,SIGNAL(send_control(control_state)),
            this,SLOT(get_control(control_state)));
    connect(this,SIGNAL(send_draw(draw_state*)),
            d,SLOT(recive_draw(draw_state*)));
}

void Application::get_control(control_state cs)
{
    draw_state *ds = new draw_state;
    double x_ang = 2*M_PI*cs.x_rot/360;
    double y_ang = 2*M_PI*cs.y_rot/360;
    double z_ang = 2*M_PI*cs.z_rot/360;

    Mmatrix Tx(3,3),Ty(3,3),Tz(3,3);

    //блок с нахождением максимальной координаты
    ds->max = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (qAbs(cs.p[i].x > ds->max))
        {
            ds->max = static_cast<int>(cs.p[i].x);
        }
        if (qAbs(cs.p[i].y > ds->max))
        {
            ds->max = static_cast<int>(cs.p[i].y);
        }
        if (qAbs(cs.p[i].y > ds->max))
        {
            ds->max = static_cast<int>(cs.p[i].y);
        }
    }

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



    for (size_t i = 0; i < 4; i++)
    {
        Mmatrix tmp(1,3),res(1,3);
        tmp.data[0][0] = cs.p[i].x;
        tmp.data[0][1] = cs.p[i].y;
        tmp.data[0][2] = cs.p[i].z;

        res = ((tmp * Tx) *Ty) * Tz;
        cs.p[i].x = res.data[0][0];
        cs.p[i].y = res.data[0][1];
        cs.p[i].z = res.data[0][2];
    }


    ds->num = static_cast <size_t> (1.0/STEP) +1;

    for (size_t i = 0; i < ds->num; i++)
    {
        std::vector <PointF3D> tmp;

        for (size_t j = 0; j < ds->num; j++)
        {
            PointF3D tmp_p;
            tmp_p.x = cs.p[0].x*(1-i*STEP)*(1-j*STEP) + cs.p[2].x*(1-i*STEP)*(j*STEP) + cs.p[1].x*(i*STEP)*(1-j*STEP) + cs.p[3].x*(i*STEP)*(j*STEP);
            tmp_p.y = cs.p[0].y*(1-i*STEP)*(1-j*STEP) + cs.p[2].y*(1-i*STEP)*(j*STEP) + cs.p[1].y*(i*STEP)*(1-j*STEP) + cs.p[3].y*(i*STEP)*(j*STEP);
            tmp_p.z = cs.p[0].z*(1-i*STEP)*(1-j*STEP) + cs.p[2].z*(1-i*STEP)*(j*STEP) + cs.p[1].z*(i*STEP)*(1-j*STEP) + cs.p[3].z*(i*STEP)*(j*STEP);
            tmp.push_back(tmp_p);
        }
        ds->d.push_back(tmp);
    }

    emit(send_draw(ds));
}
