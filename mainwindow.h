#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void addPoint(double x, double y);
    void clearData();
    void plot();

private:
    Ui::MainWindow *ui;

    QVector<double> vec_x, vec_y;

private slots:
    void on_add_clicked();
    void on_clear_clicked();
    void digit_pressed();
    void on_decimal_released();
    void unary_operation_pressed();
    void on_clear_cal_released();
    void on_equal_released();
    void binary_operation_pressed();

};
#endif // MAINWINDOW_H
