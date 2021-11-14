#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawWindow)
{
    ui->setupUi(this);
    d = nullptr;
}

DrawWindow::~DrawWindow()
{
    delete ui;
}

void DrawWindow::recive_draw(DrawState *rds)
{
    d=rds;
    repaint();
}

void DrawWindow::paintEvent (QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;

    support_state s;
    s.cw = 0.5*rect().width();
    s.ch = 0.5*rect().height();


    int n;
    if (d == nullptr)
    {
        n = 5;
    }
    else
    {
        n = d->lim;
    }

    s.ew = (s.cw) / (n);
    s.eh = (s.ch) / (n);

    qreal c = s.cw>s.ch?s.ch:s.cw;
    qreal ca = 0.05*c;
    qreal caa = ca * 0.4;
    qreal cf = 0.1 * c;
    font.setPointSize(cf);
    painter.setFont(font);

    QPen mp;
    mp.setColor(Qt::black);
    mp.setWidth(3);
    QPen sp;
    sp.setColor(Qt::blue);
    sp.setWidth(2);
    QPen ip;
    ip.setColor(Qt::green);
    ip.setWidth(2);
    QPen op;
    op.setColor(QColor::fromRgb(255, 128, 0));
    op.setWidth(2);
    painter.setPen(mp);

    painter.drawLine(QLineF(0,s.ch,2*s.cw,s.ch));
    painter.drawLine(QLineF(s.cw,0,s.cw,2*s.ch));
    QPointF arr1[3],arr2[3];
    arr1[0] = QPointF(s.cw,0);
    arr1[1] = QPointF(s.cw-caa,ca);
    arr1[2] = QPointF(s.cw+caa,ca);
    arr2[0] = QPointF(2*s.cw,s.ch);
    arr2[1] = QPointF(2*s.cw-ca,s.ch+caa);
    arr2[2] = QPointF(2*s.cw-ca,s.ch-caa);
    painter.setBrush(QBrush(Qt::black));
    painter.drawPolygon(arr1,3);
    painter.drawPolygon(arr2,3);
    painter.drawText(arr1[2]+QPointF(0,0.5*cf),"y");
    painter.drawText(arr2[2]-QPointF(0.5*cf,0),"x");

    if (d != nullptr)
    {
        QPointF square[4];
        for (size_t i = 0; i<4; i++)
        {
            square[i] = transform(d->p[i],s);
        }
        painter.setBrush(QBrush(Qt::transparent));
        painter.setPen(sp);
        painter.drawPolygon(square,4);


        for (size_t i = 0; i < d->sec.size(); i++)
        {
            switch (d->sec[i].visible)
            {
            case 0:
            {
                painter.setPen(op);
                painter.drawLine(transform(d->sec[i].line,s));
                break;
            }
            case 1:
            {
                painter.setPen(ip);
                painter.drawLine(transform(d->sec[i].line,s));
                break;
            }
            case 2:
            {
                painter.setPen(op);
                painter.drawLine(transform(d->sec[i].line,s));
                painter.setPen(ip);
                QLineF tmp;
                tmp.setP1(QPointF(d->sec[i].line.p1()+(d->sec[i].line.p2()-d->sec[i].line.p1())*d->sec[i].t[0]));
                tmp.setP2(QPointF(d->sec[i].line.p1()+(d->sec[i].line.p2()-d->sec[i].line.p1())*d->sec[i].t[1]));
                painter.drawLine(transform(tmp,s));
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }


}

QPointF DrawWindow::transform(QPointF a, support_state s)
{
    QPointF tmp;
    tmp.setX(s.cw + a.x()*s.ew);
    tmp.setY(s.ch - a.y()*s.eh);
    return tmp;
}

QLineF DrawWindow::transform(QLineF a, support_state s)
{
    QLineF tmp;
    tmp.setP1(transform(a.p1(),s));
    tmp.setP2(transform(a.p2(),s));
    return tmp;
}
