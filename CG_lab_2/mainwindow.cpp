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

void MainWindow::on_pushButton_clicked()
{
    QPointF *p = new QPointF[4];
    p[0].setX(ui->lineEdit_x_1->text().toDouble());
    p[0].setY(ui->lineEdit_y_1->text().toDouble());
    p[1].setX(ui->lineEdit_x_2->text().toDouble());
    p[1].setY(ui->lineEdit_y_2->text().toDouble());
    p[2].setX(ui->lineEdit_x_3->text().toDouble());
    p[2].setY(ui->lineEdit_y_3->text().toDouble());
    p[3].setX(ui->lineEdit_x_4->text().toDouble());
    p[3].setY(ui->lineEdit_y_4->text().toDouble());
    emit send_control(p);
}
