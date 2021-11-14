#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>

#include <common.h>

namespace Ui {
class DrawWindow;
}

struct support_state
{
    qreal cw;
    qreal ch;
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
    void paintEvent(QPaintEvent *event);

public slots:
    void recive_draw(DrawState*);

private:
    Ui::DrawWindow *ui;
    DrawState *d;
    QPointF transform(QPointF,support_state);
    QLineF transform(QLineF,support_state);
};

#endif // DRAWWINDOW_H
