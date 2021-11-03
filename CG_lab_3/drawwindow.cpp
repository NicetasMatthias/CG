#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawWindow)
{
    ds = nullptr;
    ui->setupUi(this);
}

DrawWindow::~DrawWindow()
{
    delete ui;
}

void DrawWindow::recive_draw(draw_state *rds)
{
    ds=rds;
    repaint();
}


void DrawWindow::paintEvent (QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;

    support_state s;
    s.xred = 0.5;
    s.cw = 0.5*rect().width();
    s.ch = 0.5*rect().height();



    //qreal xred = 0.5;
    qreal xshift = 0.08;
    //qreal cw = 0.5*rect().width();
    //qreal ch = 0.5*rect().height();

    qreal xcw = s.cw * xshift;
    qreal xch = s.ch * xshift;
    qreal cmw = s.cw / 10;
    qreal cmh = s.ch / 10;

    int num = 5;
    if (ds!=nullptr)
    {
        num = ds->max;
    }
    s.ew = (s.cw - cmw) / (num + 5);
    s.eh = (s.ch - cmh) / (num + 5);
    //qreal ew = s.cw-cmw / (s.num + 2);

    qreal c = s.cw>s.ch?s.ch:s.cw;
    qreal cf = 0.03 * c;

    /*
    qreal cr = 0.015*(cw>ch?ch:cw);
    qreal crn = cr *0.2;
    qreal ca = 0.05*(cw>ch?ch:cw);
    qreal caa = ca * 0.4;
    int num = 5;
    qreal cnw = cw / num;
    qreal cnh = ch / num;
    qreal can = ca *0.2;
    qreal cnf = cf * 0.5;
    */
    font.setPointSize(cf);
    painter.setFont(font);

    painter.setPen(QPen(Qt::black));

    QLineF Ox(2*s.cw-cmw-s.cw*s.xred-xcw,0+cmh+s.ch*s.xred-xch,0+cmw+s.cw*s.xred+xcw,2*s.ch-cmh-s.ch*s.xred+xch);
    QLineF Oy(0+cmw,s.ch,2*s.cw-cmw,s.ch);
    QLineF Oz(s.cw,2*s.ch-cmh,s.cw,0+cmh);

    s.ex = Ox.unitVector().p2()-Ox.unitVector().p1();
    s.ey = Oy.unitVector().p2()-Oy.unitVector().p1();
    s.ez = Oz.unitVector().p2()-Oz.unitVector().p1();


    painter.drawLine(Ox);
    painter.drawLine(Oy);
    painter.drawLine(Oz);


    painter.drawText(Ox.p2()+ 2*cf*s.ex,"x");
    painter.drawText(Oy.p2()+ cf*s.ey,"y");
    painter.drawText(Oz.p2()+ cf*s.ez,"z");

    if (ds != nullptr)
    {
        painter.setPen(QPen(Qt::red));
        for (size_t i = 0; i < ds->num; i++)
        {
            for (size_t j = 0; j < ds->num; j++)
            {
                if (i != ds->num-1)
                {
                    painter.drawLine(transform(ds->d[i][j],s),transform(ds->d[i+1][j],s));
                }
                if (j != ds->num-1)
                {
                    painter.drawLine(transform(ds->d[i][j],s),transform(ds->d[i][j+1],s));
                }
            }
        }

    }




    /*
    QPointF f[4];
    f[0] = transform(4,-3,8,s);
    f[1] = transform(-2,5,2,s);
    f[2] = transform(0,1,-5,s);
    f[3] = transform(5,-5,5,s);*/
/*
    QMessageBox::information(0,"",  "A: ("+ QString::number(f[0].rx()) +";" + QString::number(f[0].ry())+
                                    "\nB: ("+ QString::number(f[1].rx()) +";" + QString::number(f[1].ry())+
                                    "\nC: ("+ QString::number(f[2].rx()) +";" + QString::number(f[2].ry())+
                                    "\nD: ("+ QString::number(f[3].rx()) +";" + QString::number(f[3].ry())+
                                    "\n ex.x = "+ QString::number(s.ex.rx()) + "   ex.y = " + QString::number(s.ex.ry()));
*/
/*    painter.setBrush(QBrush(Qt::CrossPattern));
    painter.drawPolygon(f,4);*/

}

QPointF DrawWindow::transform(PointF3D a, support_state s)
{
    QPointF tmp;
    tmp.setX(s.cw + (a.y*s.ey.rx()+ a.x*s.ex.rx()*s.xred )*s.ew);
    tmp.setY(s.ch + (a.z*s.ez.ry()+ a.x*s.ex.ry()*s.xred )*s.eh);

    return tmp;
}
