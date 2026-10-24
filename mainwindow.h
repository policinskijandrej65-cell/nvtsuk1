#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "car.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    Car user_car_prev;
    Car user_car_now;
    int last_amount = 0;

private slots:
    void saveButtonPressed1();
    void saveButtonPressed2();
    void showField1();
    void showField2();
    void onTypeChanged(const QString &text);
    void onAmountChanged(int newValue);
    void currentRowChanged(int row);

};
#endif // MAINWINDOW_H