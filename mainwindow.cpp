#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Save_button1, SIGNAL(clicked()), this, SLOT(saveButtonPressed1()));
    connect(ui->Save_button2, SIGNAL(clicked()), this, SLOT(saveButtonPressed2()));
    connect(ui->Show_button1, SIGNAL(clicked()), this, SLOT(showField1()));
    connect(ui->Show_button2, SIGNAL(clicked()), this, SLOT(showField2()));
}

void MainWindow::saveButtonPressed1()
{
    user_car.setAmount(ui->amount->value());
    user_car.setBrandName(ui->brand_name->text());
    user_car.setClimateControl(ui->climate_control);
    user_car.setDateLastDelivery(ui->date_last_delivery->date());
    user_car.setEngineV(ui->engine_v->value());
    user_car.setFrom_1To_100(ui->from_1_to_100->value());
    user_car.setHumanCapacity(ui->human_capatity->value());
    user_car.setEngineV(ui->engine_v->value());
    user_car.setMaxSpeed(ui->max_speed->value());
    user_car.setPrice(ui->price->value());
    // user_car.setType(static_cast<Car::Type>(ui->type->currentRow() - 1));
}
void MainWindow::saveButtonPressed2()
{
    // Здесь будет код для второй кнопки сохранения
}

void MainWindow::showField1()
{
    // Здесь будет код для отображения записи 1
}

void MainWindow::showField2()
{
    // Здесь будет код для отображения записи 2
}

MainWindow::~MainWindow()
{
    delete ui;
}