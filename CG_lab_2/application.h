#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QObject>
#include <QtMath>

#include <mainwindow.h>
#include <drawwindow.h>

class Application : public QApplication
{
    Q_OBJECT
private:
    MainWindow *m;
    DrawWindow *d;

    QPointF sub_calc(QPointF*, qreal);
public:
    Application(int, char**);
public slots:
    void recieve_control(QPointF*);
signals:
    void send_state(State*);
};

#endif // APPLICATION_H
