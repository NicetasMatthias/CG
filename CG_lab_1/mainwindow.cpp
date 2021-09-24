#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::res()
{
    on_pushButton_reset_clicked();
}

Control_State MainWindow::get_state()
{
    Control_State tmp;
    tmp.is_reset = false;
    tmp.point_changed = false;
    tmp.p_x = ui->lineEdit_x->text().toDouble();
    tmp.p_y = ui->lineEdit_y->text().toDouble();
    tmp.angle = ui->horizontalSlider->value()/100;
    return tmp;
}


void MainWindow::on_pushButton_reset_clicked()
{
    ui->lineEdit_x->setText(QString::number(0));
    ui->lineEdit_y->setText(QString::number(0));
    ui->lineEdit_angle->setText(QString::number(0));
    Control_State tmp = get_state();
    tmp.is_reset = true;
    emit update(tmp);
}

void MainWindow::on_lineEdit_x_textChanged(const QString &arg1)
{
    ui->lineEdit_angle->setText(QString::number(0));
    Control_State tmp = get_state();
    tmp.point_changed = true;
    emit update(tmp);
}

void MainWindow::on_lineEdit_y_textChanged(const QString &arg1)
{
    ui->lineEdit_angle->setText(QString::number(0));
    Control_State tmp = get_state();
    tmp.point_changed = true;
    emit update(tmp);}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit_angle->setText(QString::number(value*1.0/100));
    emit update(get_state());
}

void MainWindow::on_lineEdit_angle_textEdited(const QString &arg1)
{
    ui->horizontalSlider->setValue(arg1.toDouble()*100);
}
