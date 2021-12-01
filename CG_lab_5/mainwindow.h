#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <common.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ControlState* get_state();

private slots:
    void on_horizontalSlider_X_valueChanged(int value);

    void on_horizontalSlider_Y_valueChanged(int value);

    void on_horizontalSlider_Z_valueChanged(int value);

private:
    Ui::MainWindow *ui;


signals:
    void send_control(ControlState*);

};
#endif // MAINWINDOW_H
