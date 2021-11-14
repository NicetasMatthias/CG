#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>
#include <QTime>
#include <mainwindow.h>
#include <drawwindow.h>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int, char**);

private:
    DrawWindow *d;
    MainWindow *m;
private slots:
    void recive_control(ControlState*);
signals:
    void send_draw(DrawState*);
};

#endif // APPLICATION_H
