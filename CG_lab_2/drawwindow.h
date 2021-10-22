#ifndef DRAWWINDOW_H
#define DRAWWINDOW_H

#include <QWidget>
#include <QPainter>

#include <common.h>

namespace Ui {
class DrawWindow;
}

class DrawWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DrawWindow(QWidget *parent = nullptr);
    ~DrawWindow();

protected:
    void paintEvent (QPaintEvent *event);

public slots:
    void recive_state(State*);

private:
    Ui::DrawWindow *ui;
    State * draw_state;
};

#endif // DRAWWINDOW_H
