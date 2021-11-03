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

control_state MainWindow::get_state()
{
    control_state tmp;
    tmp.x_rot = ui->lineEdit_x_rot->text().toDouble();
    tmp.y_rot = ui->lineEdit_y_rot->text().toDouble();
    tmp.z_rot = ui->lineEdit_z_rot->text().toDouble();

    tmp.p[0].x = ui->lineEdit_x_1->text().toDouble();
    tmp.p[0].y = ui->lineEdit_y_1->text().toDouble();
    tmp.p[0].z = ui->lineEdit_z_1->text().toDouble();

    tmp.p[1].x = ui->lineEdit_x_2->text().toDouble();
    tmp.p[1].y = ui->lineEdit_y_2->text().toDouble();
    tmp.p[1].z = ui->lineEdit_z_2->text().toDouble();

    tmp.p[2].x = ui->lineEdit_x_3->text().toDouble();
    tmp.p[2].y = ui->lineEdit_y_3->text().toDouble();
    tmp.p[2].z = ui->lineEdit_z_3->text().toDouble();

    tmp.p[3].x = ui->lineEdit_x_4->text().toDouble();
    tmp.p[3].y = ui->lineEdit_y_4->text().toDouble();
    tmp.p[3].z = ui->lineEdit_z_4->text().toDouble();

    return tmp;
}

void MainWindow::send_state()
{
    emit send_control(get_state());
}

//дикая пачка служебных слотов
void MainWindow::on_lineEdit_x_1_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_y_1_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_z_1_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_x_2_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_y_2_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_z_2_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_x_3_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_y_3_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_z_3_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_x_4_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_y_4_textChanged(const QString &arg1)
{
    send_state();
}
void MainWindow::on_lineEdit_z_4_textChanged(const QString &arg1)
{
    send_state();
}



void MainWindow::on_lineEdit_x_rot_textChanged(const QString &arg1)
{
    int tmp = static_cast<int>(arg1.toDouble()*100)%36001;
    ui->horizontalSlider_x->setValue(tmp);
    ui->lineEdit_x_rot->setText(QString::number(0.01*tmp));
    send_state();
}

void MainWindow::on_horizontalSlider_x_valueChanged(int value)
{
    ui->lineEdit_x_rot->setText(QString::number(0.01*value));
    send_state();
}

void MainWindow::on_lineEdit_y_rot_textChanged(const QString &arg1)
{
    int tmp = static_cast<int>(arg1.toDouble()*100)%36001;
    ui->horizontalSlider_y->setValue(tmp);
    ui->lineEdit_y_rot->setText(QString::number(0.01*tmp));
    send_state();
}

void MainWindow::on_horizontalSlider_y_valueChanged(int value)
{
    ui->lineEdit_y_rot->setText(QString::number(0.01*value));
    send_state();
}

void MainWindow::on_lineEdit_z_rot_textChanged(const QString &arg1)
{
    int tmp = static_cast<int>(arg1.toDouble()*100)%36001;
    ui->horizontalSlider_z->setValue(tmp);
    ui->lineEdit_z_rot->setText(QString::number(0.01*tmp));
    send_state();
}

void MainWindow::on_horizontalSlider_z_valueChanged(int value)
{
    ui->lineEdit_z_rot->setText(QString::number(0.01*value));
    send_state();
}
