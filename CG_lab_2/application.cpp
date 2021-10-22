#include "application.h"

#define T_STEP 0.001;

Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    m = new MainWindow;
    m->show();
    d = new DrawWindow;
    d->show();
    connect(m,SIGNAL(send_control(QPointF*)),
            this,SLOT(recieve_control(QPointF*)));
    connect(this,SIGNAL(send_state(State*)),
            d,SLOT(recive_state(State*)));
}

void Application::recieve_control(QPointF* p)
{
    qreal step = T_STEP;
    State s;
    s.d = p;
    s.max = 5;
    for (size_t i = 0; i < 4; i++)
    {
        unsigned int tmp = static_cast<unsigned int>(qAbs(p[i].x())>qAbs(p[i].y())?qAbs(p[i].x()):qAbs(p[i].y()));
        s.max = s.max>tmp?s.max:tmp;
    }

    for (size_t i = 0; i*step < 1; i++)
    {
        s.p.push_back(sub_calc(p,i*step));
    }

    emit send_state(&s);
}

QPointF Application::sub_calc(QPointF* p, qreal t)
{
    return qPow(1-t,3)*p[0] + 3*qPow(1-t,2)*t*p[1] + 3*(1-t)*qPow(t,2)*p[2] + qPow(t,3)*p[3];
}
