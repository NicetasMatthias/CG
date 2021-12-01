#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <common.h>

#include <QWidget>
#include <QPainter>

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

private:
    Ui::DrawWindow *ui;
    DrawState *d;

    QPointF* transform(Face f, support_state s);

public slots:
    void get_draw(DrawState*);

protected:
    void paintEvent (QPaintEvent *event);
};

#endif // DRAWWINDOW_H
