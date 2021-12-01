#ifndef APPLICATION_H
#define APPLICATION_H

#include <mainwindow.h>
#include <drawwindow.h>
#include <../math/mmath.h>

#include <QApplication>
#include <QObject>

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int argc, char *argv[]);
private:
    MainWindow *m;
    DrawWindow *d;
    QVector <PointF3D> default_points;
    bool is_visible(Face);
    PointF3D H,O;

private slots:
    void get_control(ControlState*);

signals:
    void send_draw(DrawState*);
};

#endif // APPLICATION_H
