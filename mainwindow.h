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
    int last_amount = 0;
    Car *records[100] = {};
    Car *sorted[100] = {};
    int number = 0;
    void update_browser(Car* selectedCar = nullptr);

private slots:
    void addToBase(Car *current_record, int *number);
    void createRecord();
    void deleteRecord();
    void saveButtonPressed();
    void insert10();
    void onTypeChanged(const QString &text);
    void onAmountChanged(int newValue);
    void currentRowChanged(int row);
    void only_type();
    void cancel();

};
#endif // MAINWINDOW_H