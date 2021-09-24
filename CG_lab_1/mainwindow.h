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
    void res();

private:
    Control_State get_state();

private slots:

    void on_pushButton_reset_clicked();

    void on_lineEdit_x_textChanged(const QString &arg1);

    void on_lineEdit_y_textChanged(const QString &arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_angle_textEdited(const QString &arg1);

signals:
    void update(Control_State);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
