#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

ControlState* MainWindow::get_state()
{
    ControlState *tmp = new ControlState;

    tmp->x_ang = static_cast <qreal> (ui->horizontalSlider_X->value()) / 10;
    tmp->y_ang = static_cast <qreal> (ui->horizontalSlider_Y->value()) / 10;
    tmp->z_ang = static_cast <qreal> (ui->horizontalSlider_Z->value()) / 10;

    return tmp;
}

void MainWindow::on_horizontalSlider_X_valueChanged(int value)
{
    Q_UNUSED(value);
    emit send_control(get_state());
}

void MainWindow::on_horizontalSlider_Y_valueChanged(int value)
{
    Q_UNUSED(value);
    emit send_control(get_state());
}

void MainWindow::on_horizontalSlider_Z_valueChanged(int value)
{
    Q_UNUSED(value);
    emit send_control(get_state());
}
