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
    ui->type_selector->addItems(CAR_TYPES);
}

void MainWindow::saveButtonPressed1()
{
    user_car_now.setAmount(ui->amount->value());
    user_car_now.setBrandName(ui->brand_name->text());
    user_car_now.setClimateControl(ui->climate_control);
    user_car_now.setDateLastDelivery(ui->date_last_delivery->date());
    user_car_now.setEngineV(ui->engine_v->value());
    user_car_now.setFrom_1To_100(ui->from_1_to_100->value());
    user_car_now.setHumanCapacity(ui->human_capatity->value());
    user_car_now.setEngineV(ui->engine_v->value());
    user_car_now.setMaxSpeed(ui->max_speed->value());
    user_car_now.setPrice(ui->price->value());
    // user_car.setType(static_cast<Car::Type>(ui->type->currentRow() - 1));
}
void MainWindow::saveButtonPressed2()
{
    user_car_prev.setAmount(ui->amount->value());
    user_car_prev.setBrandName(ui->brand_name->text());
    user_car_prev.setClimateControl(ui->climate_control);
    user_car_prev.setDateLastDelivery(ui->date_last_delivery->date());
    user_car_prev.setEngineV(ui->engine_v->value());
    user_car_prev.setFrom_1To_100(ui->from_1_to_100->value());
    user_car_prev.setHumanCapacity(ui->human_capatity->value());
    user_car_prev.setEngineV(ui->engine_v->value());
    user_car_prev.setMaxSpeed(ui->max_speed->value());
    user_car_prev.setPrice(ui->price->value());
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