#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DIF 0.01

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
    ControlState *c = new ControlState;
    c->p1.setX(ui->lineEdit_x_1->text().toDouble());
    c->p1.setY(ui->lineEdit_y_1->text().toDouble());
    c->p2.setX(ui->lineEdit_x_2->text().toDouble());
    c->p2.setY(ui->lineEdit_y_2->text().toDouble());
    if (abs(c->p1.x()-c->p2.x())<DIF||abs(c->p1.y()-c->p2.y())<DIF)
    {
        QMessageBox::warning(nullptr,"Ошибка","Необходимо указать координаты противоположных углов прямоугольника");
        delete c;
        return;
    }
    c->sec_num = ui->spinBox->value();
    emit(send_control(c));
}

