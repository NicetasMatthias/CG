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

void DrawWindow::get_draw(DrawState *rds)
{
    d=rds;
    repaint();
}

void DrawWindow::paintEvent (QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    support_state s;
    s.cw = 0.5*rect().width();
    s.ch = 0.5*rect().height();
    s.ew = (s.cw) / (MY_SIZE*2);
    s.eh = (s.ch) / (MY_SIZE*2);

    if (d != nullptr)
    {
        QPen vp;
        vp.setColor(Qt::black);
        vp.setWidth(3);
        QPen np;
        np.setColor(Qt::red);
        np.setStyle(Qt::DotLine);
        vp.setWidth(3);


        for (qsizetype i = 0; i < d->faces.length(); i++)
        {
            if (d->faces[i].visible)
            {
                painter.setPen(vp);
            }
            else
            {
                painter.setPen(np);
            }
            painter.drawPolygon(transform(d->faces[i],s),d->faces[i].points.length());
        }
    }
}

QPointF* DrawWindow::transform(Face f, support_state s)
{
    QPointF *tmp = new QPointF[f.points.length()];
    for (qsizetype i = 0; i < f.points.length(); i++)
    {
        tmp[i].setX(s.cw + f.points[i].x*s.ew);
        tmp[i].setY(s.ch - f.points[i].y*s.eh);
    }
    return tmp;
}
