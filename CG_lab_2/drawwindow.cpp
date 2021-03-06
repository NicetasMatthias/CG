#include "drawwindow.h"
#include "ui_drawwindow.h"

DrawWindow::DrawWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    draw_state = nullptr;
}

DrawWindow::~DrawWindow()
{
    delete ui;
}

void DrawWindow::recive_state(State* s)
{
    draw_state = s;
    repaint();
}

void DrawWindow::paintEvent (QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;

    qreal cw = 0.5*rect().width();
    qreal ch = 0.5*rect().height();
    qreal cr = 0.015*(cw>ch?ch:cw);
    qreal crn = cr *0.2;
    qreal ca = 0.05*(cw>ch?ch:cw);
    qreal caa = ca * 0.4;
    qreal cf = 0.06 *(cw>ch?ch:cw);
    int num;
    if (draw_state == nullptr)
    {
        num = 5;
    }
    else
    {
        num = draw_state->max + 2;
    }
    qreal cnw = cw / num;
    qreal cnh = ch / num;
    qreal can = ca *0.2;
    qreal cnf = cf * 0.5;

    font.setPointSize(cf);
    painter.setFont(font);

    painter.setPen(QPen(Qt::black));
    painter.drawLine(QLineF(0,ch,2*cw,ch));
    painter.drawLine(QLineF(cw,0,cw,2*ch));
    QPointF arr1[3],arr2[3];
    arr1[0] = QPointF(cw,0);
    arr1[1] = QPointF(cw-caa,ca);
    arr1[2] = QPointF(cw+caa,ca);
    arr2[0] = QPointF(2*cw,ch);
    arr2[1] = QPointF(2*cw-ca,ch+caa);
    arr2[2] = QPointF(2*cw-ca,ch-caa);
    painter.setBrush(QBrush(Qt::black));
    painter.drawPolygon(arr1,3);
    painter.drawPolygon(arr2,3);
    painter.drawText(arr1[2],"y");
    painter.drawText(arr2[2],"x");


    font.setPointSize(cnf);
    painter.setFont(font);
    for (int i = 0; i < num ; i++)
    {
        painter.drawLine(cw+i*cnw,ch+can,cw+i*cnw,ch-can);
        painter.drawLine(cw-i*cnw,ch+can,cw-i*cnw,ch-can);
        painter.drawLine(cw-can,ch+i*cnh,cw+can,ch+i*cnh);
        painter.drawLine(cw-can,ch-i*cnh,cw+can,ch-i*cnh);
        if (i == 0)
        {
            painter.drawText(cw+i*cnw+can,ch-2*can,QString::number(i));
        }
        else
        {
            painter.drawText(cw+i*cnw,ch-2*can,QString::number(i));
            painter.drawText(cw-i*cnw,ch-2*can,QString::number(-i));
            painter.drawText(cw+2*can,ch+i*cnh,QString::number(-i));
            painter.drawText(cw+2*can,ch-i*cnh,QString::number(i));
        }
    }

    if (draw_state == nullptr)
    {
        return;
    }
    else
    {

        for (size_t i = 0; i < 4; i++)
        {
            QPen pen;
            pen.setColor(QColor::fromRgb(0, 191, 255));
            pen.setWidth(1);
            pen.setBrush(QBrush(QColor::fromRgb(30, 144, 255)));
            painter.setPen(pen);
            font.setPointSize(cf*0.5);
            painter.setFont(font);

            qreal rx = cw + draw_state->d[i].x()*cnw;
            qreal ry = ch - draw_state->d[i].y()*cnh;
            if (i!=3)
            {
                qreal rnx = cw + draw_state->d[i+1].x()*cnw;
                qreal rny = ch - draw_state->d[i+1].y()*cnh;
                painter.drawLine(QPointF(rx,ry),QPointF(rnx,rny));
            }
            pen.setColor(Qt::black);
            painter.setPen(pen);
            painter.drawText(QPointF(rx+cr,ry+cf*0.5),"P"+QString::number(i+1));            
            pen.setColor(QColor::fromRgb(30, 144, 255));
            painter.setPen(pen);
            painter.drawEllipse(rx-cr*0.5,ry-cr*0.5,cr,cr);
        }
        QPen pen;
        pen.setColor(QColor::fromRgb(255, 127, 80));
        painter.setPen(pen);

        for (qsizetype i = 0; i < draw_state->p.length(); i++)
        {
            qreal rx = cw + draw_state->p[i].x()*cnw;
            qreal ry = ch - draw_state->p[i].y()*cnh;
            painter.drawEllipse(rx-crn*0.5,ry-crn*0.5,crn,crn);
        }




/*        painter.drawEllipse(cw + draw_state.p.x()*cnw - 0.5*cr,ch - draw_state.p.y()*cnh - 0.5*cr,cr,cr);
        painter.setBrush(QBrush(Qt::transparent));
        QPointF tmp[4];
        for (int i = 0; i<4; i++)
        {
            tmp[i].setX(cw + draw_state.f[i].x()*cnw);
            tmp[i].setY(ch - draw_state.f[i].y()*cnh);
        }
        painter.drawPolygon(tmp,4);*/
    }


}
