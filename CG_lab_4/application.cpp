#include "application.h"

#define SPREAD_COEFFICIENT 1.5

Application::Application(int argc, char *argv[])
    : QApplication(argc,argv)
{
    d = new DrawWindow;
    m = new MainWindow;
    d->show();
    m->show();
    connect(m,SIGNAL(send_control(ControlState*)),
            this,SLOT(recive_control(ControlState*)));
    connect(this,SIGNAL(send_draw(DrawState*)),
            d,SLOT(recive_draw(DrawState*)));
}

void Application::recive_control(ControlState* c)
{
    DrawState *d = new DrawState;
    d->p[0] = c->p1;
    d->p[1] = QPointF(c->p1.x(),c->p2.y());
    d->p[2] = c->p2;
    d->p[3] = QPointF(c->p2.x(),c->p1.y());

    qreal Xl = qMin(c->p1.x(),c->p2.x());
    qreal Xr = qMax(c->p1.x(),c->p2.x());
    qreal Yu = qMax(c->p1.y(),c->p2.y());
    qreal Yd = qMin(c->p1.y(),c->p2.y());

    int lim = static_cast <int> (qMax(qMax(abs(Xl),abs(Xr)),qMax(abs(Yu),abs(Yd)))*100*SPREAD_COEFFICIENT);
    d->lim = (lim/100)+1;
    for (size_t i = 0; i<c->sec_num; i++)
    {
        MyLineF tmp;

        //блок генерации отрезка
        srand(QTime::currentTime().msecsSinceStartOfDay()*(i+1));
        tmp.line.setP1(QPointF((rand()%(lim*2)-lim)*0.01,(rand()%(lim*2)-lim)*0.01));
        tmp.line.setP2(QPointF((rand()%(lim*2)-lim)*0.01,(rand()%(lim*2)-lim)*0.01));

        //блок определения видимости отрезков
        unsigned short code1 = 0, code2 = 0;
        //вычисления для p1
        if (tmp.line.p1().x() < Xl) code1 += 8;
        if (tmp.line.p1().x() > Xr) code1 += 4;
        if (tmp.line.p1().y() < Yd) code1 += 2;
        if (tmp.line.p1().y() > Yu) code1 += 1;
        //вычисления для p2
        if (tmp.line.p2().x() < Xl) code2 += 8;
        if (tmp.line.p2().x() > Xr) code2 += 4;
        if (tmp.line.p2().y() < Yd) code2 += 2;
        if (tmp.line.p2().y() > Yu) code2 += 1;

        if ((code1 == 0)&&(code2 == 0))
        {
            //отсечение полностью видимых отрезков
            tmp.visible = 1;
        }
        else if((code1&code2) != 0)
        {
            //отсечение тривиально невидимых отрезков
            tmp.visible = 0;
        }
        else
        {
            //блок обработки нетривиальных отрезков
            qreal t1,t2,t3,t4;
            if ((tmp.line.p2().x()-tmp.line.p1().x())!=0)
            {
                //условие пересечения левой границы
                t1 = (Xl-tmp.line.p1().x())/(tmp.line.p2().x()-tmp.line.p1().x());
                if ((t1 >= 0)&&(t1 <= 1))
                {
                    if (((tmp.line.p1().y()+(tmp.line.p2().y()-tmp.line.p1().y())*t1) >= Yd)&&((tmp.line.p1().y()+(tmp.line.p2().y()-tmp.line.p1().y())*t1) <= Yu))
                    {
                        tmp.t.push_back(t1);
                    }
                }
                //условие пересечения правой границы
                t2 = (Xr-tmp.line.p1().x())/(tmp.line.p2().x()-tmp.line.p1().x());
                if ((t2 >= 0)&&(t2 <= 1))
                {
                    if (((tmp.line.p1().y()+(tmp.line.p2().y()-tmp.line.p1().y())*t2) >= Yd)&&((tmp.line.p1().y()+(tmp.line.p2().y()-tmp.line.p1().y())*t2) <= Yu))
                    {
                        tmp.t.push_back(t2);
                    }
                }
            }

            if ((tmp.line.p2().y()-tmp.line.p1().y())!=0)
            {
                //условие пересечения нижней границы
                t3 = (Yd-tmp.line.p1().y())/(tmp.line.p2().y()-tmp.line.p1().y());
                if ((t3 >= 0)&&(t3 <= 1))
                {
                    if (((tmp.line.p1().x()+(tmp.line.p2().x()-tmp.line.p1().x())*t3) >= Xl)&&((tmp.line.p1().x()+(tmp.line.p2().x()-tmp.line.p1().x())*t3) <= Xr))
                    {
                        tmp.t.push_back(t3);
                    }
                }
                //условие пересечения верхней границы
                t4 = (Yu-tmp.line.p1().y())/(tmp.line.p2().y()-tmp.line.p1().y());
                if ((t4 >= 0)&&(t4 <= 1))
                {
                    if (((tmp.line.p1().x()+(tmp.line.p2().x()-tmp.line.p1().x())*t4) >= Xl)&&((tmp.line.p1().x()+(tmp.line.p2().x()-tmp.line.p1().x())*t4) <= Xr))
                    {
                        tmp.t.push_back(t4);
                    }
                }
            }

            if (tmp.t.size()==0)
            {
                tmp.visible = 0;
            }
            else
            {
                tmp.visible = 2;
                if(tmp.t.size()==1)
                {
                    if (code1 == 0)
                    {
                        tmp.t.push_back(0);
                    }
                    else
                    {
                        tmp.t.push_back(1);
                    }
                }
            }
        }


        d->sec.push_back(tmp);
    }

    emit(send_draw(d));

    delete c;
}
