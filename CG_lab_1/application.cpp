#include "application.h"

#define F_S 5

Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    mw = new MainWindow;
    dw = new DrawWindow;
    mw->show();
    dw->show();
    connect(mw,SIGNAL(update(Control_State)),
            this,SLOT(Control_update(Control_State)));
    connect(this,SIGNAL(draw_update(State)),
            dw,SLOT(recive_state(State)));
    mw->res();
}

void Application::Control_update(Control_State cs)
{
    State new_state;
    new_state.f[0] = QPointF(-F_S,F_S);
    new_state.f[1] = QPointF(F_S,F_S);
    new_state.f[2] = QPointF(F_S,-F_S);
    new_state.f[3] = QPointF(-F_S,-F_S);
    if (cs.is_reset)
    {
        new_state.p = QPointF(0,0);
        new_state.max = 5;
    }
    else if (cs.point_changed)
    {
        new_state.p = QPointF(cs.p_x,cs.p_y);
        new_state.max = 5;
    }
    else
    {
        new_state.max = qMax(cs.p_x,cs.p_y);
        double angle = 2*M_PI*cs.angle/360;
        Mmatrix T (3,3);
        T.data[0][0] = cos(angle);
        T.data[0][1] = sin(angle);
        T.data[0][2] = 0;
        T.data[1][0] = -sin(angle);
        T.data[1][1] = cos(angle);
        T.data[1][2] = 0;
        T.data[2][0] = -cs.p_x*(cos(angle)-1) + cs.p_y*sin(angle);
        T.data[2][1] = -cs.p_y*(cos(angle)-1) - cs.p_x*sin(angle);
        T.data[2][2] = 1;

        for (int i = 0; i < 4; i++)
        {
            Mmatrix tmp(1,3),res(1,3);
            tmp.data[0][0] = new_state.f[i].x();
            tmp.data[0][1] = new_state.f[i].y();
            tmp.data[0][2] = 1;
            res = tmp * T;
            new_state.f[i].setX(res.data[0][0]);
            new_state.f[i].setY(res.data[0][1]);
            if (qMax(new_state.f[i].x(),new_state.f[i].y()) > new_state.max)
            {
                new_state.max = qMax(new_state.f[i].x(),new_state.f[i].y());
            }
        }
        new_state.p = QPointF(cs.p_x,cs.p_y);
    }
    curr_state = new_state;

    emit draw_update(curr_state);
}
