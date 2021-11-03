#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>

#include <mainwindow.h>
#include <drawwindow.h>
#include <../math/mmath.h>

class Application : public QApplication
{
    Q_OBJECT
private:
    MainWindow *m;
    DrawWindow *d;
public:
    Application(int, char**);
private slots:
    void get_control(control_state);
signals:
    void send_draw(draw_state*);
};

#endif // APPLICATION_H
