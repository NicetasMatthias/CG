#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>

#include <mainwindow.h>
#include <drawwindow.h>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int, char**);

private:
    MainWindow *mw;
    DrawWindow *dw;
    State curr_state;
public slots:
    void Control_update(Control_State);

signals:
    void draw_update(State);
};

#endif // APPLICATION_H
