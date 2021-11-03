#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <common.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    control_state get_state();
    void send_state();

signals:
    void send_control(control_state);

private slots:
    void on_lineEdit_x_1_textChanged(const QString &arg1);
    void on_lineEdit_y_1_textChanged(const QString &arg1);
    void on_lineEdit_z_1_textChanged(const QString &arg1);
    void on_lineEdit_x_2_textChanged(const QString &arg1);
    void on_lineEdit_y_2_textChanged(const QString &arg1);
    void on_lineEdit_z_2_textChanged(const QString &arg1);
    void on_lineEdit_x_3_textChanged(const QString &arg1);
    void on_lineEdit_y_3_textChanged(const QString &arg1);
    void on_lineEdit_z_3_textChanged(const QString &arg1);
    void on_lineEdit_x_4_textChanged(const QString &arg1);
    void on_lineEdit_y_4_textChanged(const QString &arg1);
    void on_lineEdit_z_4_textChanged(const QString &arg1);
    void on_lineEdit_x_rot_textChanged(const QString &arg1);
    void on_horizontalSlider_x_valueChanged(int value);
    void on_lineEdit_y_rot_textChanged(const QString &arg1);
    void on_horizontalSlider_y_valueChanged(int value);
    void on_lineEdit_z_rot_textChanged(const QString &arg1);
    void on_horizontalSlider_z_valueChanged(int value);
};
#endif // MAINWINDOW_H
