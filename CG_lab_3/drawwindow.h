#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>

#include <common.h>

#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class DrawWindow; }
QT_END_NAMESPACE

struct support_state
{
    qreal cw;
    qreal ch;
    qreal xred;
    QPointF ex;
    QPointF ey;
    QPointF ez;
    qreal ew;
    qreal eh;
};

class DrawWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWindow(QWidget *parent = nullptr);
    ~DrawWindow();

protected:
    void paintEvent (QPaintEvent *event);

public slots:
    void recive_draw(draw_state*);

private:
    Ui::DrawWindow *ui;

    draw_state *ds;

    QPointF transform(PointF3D a, support_state s);
};

#endif // DRAWWINDOW_H
