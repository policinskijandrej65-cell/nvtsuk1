#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "validator.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Save_button1, SIGNAL(clicked()), this, SLOT(saveButtonPressed1()));
    connect(ui->Save_button2, SIGNAL(clicked()), this, SLOT(saveButtonPressed2()));
    connect(ui->Show_button1, SIGNAL(clicked()), this, SLOT(showField1()));
    connect(ui->Show_button2, SIGNAL(clicked()), this, SLOT(showField2()));
    connect(ui->current_session, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int newValue)
            { ui->browse_session->setCurrentRow(newValue - 1); });

    connect(ui->browse_session, &QListWidget::currentRowChanged, this, [this](int row) {
        if (row == 0) showField1();
        else if (row == 1) showField2();
    });

    connect(ui->type_selector, &QComboBox::currentTextChanged, this, &MainWindow::onTypeChanged);

    connect(ui->amount, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onAmountChanged);

    ui->type_selector->addItems(CAR_TYPES);
    ui->brand_name->setValidator(new Validator(this));
    QStringList sessions = {"session 1", "session 2"};
    ui->browse_session->addItems(sessions);
}

void MainWindow::saveButtonPressed1()
{
    if (ui->current_session->value() == 1)
    {
        if (!ui->brand_name->hasAcceptableInput())
        {
            QMessageBox::warning(this, "Ошибка",
                                 "Название модели введено неверно!\n"
                                 "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
            return;
        }
        user_car_now.current_session = ui->current_session->value();
        user_car_now.setAmount(ui->amount->value());
        user_car_now.setBrandName(ui->brand_name->text());
        user_car_now.setClimateControl(ui->climate_control->isChecked());
        user_car_now.setDateLastDelivery(ui->date_last_delivery->date());
        user_car_now.setEngineV(ui->engine_v->value());
        user_car_now.setFrom_1To_100(ui->from_1_to_100->value());
        user_car_now.setHumanCapacity(ui->human_capacity->value());
        user_car_now.setMaxSpeed(ui->max_speed->value());
        user_car_now.setPrice(ui->price->value());
        user_car_now.setType(ui->type_selector->currentText());
        user_car_now.setWeightCapacity(ui->weight_capacity->value());
    }

}
void MainWindow::saveButtonPressed2()
{
    if (ui->current_session->value() == 2)
    {
        if (!ui->brand_name->hasAcceptableInput())
        {
            QMessageBox::warning(this, "Ошибка",
                                 "Название модели введено неверно!\n"
                                 "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
            return;
        }
        user_car_prev.current_session = ui->current_session->value();
        user_car_prev.setAmount(ui->amount->value());
        user_car_prev.setBrandName(ui->brand_name->text());
        user_car_prev.setClimateControl(ui->climate_control->isChecked());
        user_car_prev.setDateLastDelivery(ui->date_last_delivery->date());
        user_car_prev.setEngineV(ui->engine_v->value());
        user_car_prev.setFrom_1To_100(ui->from_1_to_100->value());
        user_car_prev.setHumanCapacity(ui->human_capacity->value());
        user_car_prev.setMaxSpeed(ui->max_speed->value());
        user_car_prev.setPrice(ui->price->value());
        user_car_prev.setType(ui->type_selector->currentText());
        user_car_prev.setWeightCapacity(ui->weight_capacity->value());
    }
}

void MainWindow::showField1()
{
    ui->current_session->setValue(1);
    ui->brand_name->setText(user_car_now.getBrandName());
    ui->type_selector->setCurrentText(user_car_now.getType());
    ui->engine_v->setValue(user_car_now.getEngineV());
    ui->human_capacity->setValue(user_car_now.getHumanCapacity());
    ui->weight_capacity->setValue(user_car_now.getWeightCapacity());
    ui->max_speed->setValue(user_car_now.getMaxSpeed());
    ui->from_1_to_100->setValue(user_car_now.getFrom_1To_100());
    ui->climate_control->setChecked(user_car_now.getClimateControl());
    ui->amount->setValue(user_car_now.getAmount());
    ui->price->setValue(user_car_now.getPrice());
    ui->date_last_delivery->setDate(user_car_now.getDateLastDelivery());
    onTypeChanged(ui->type_selector->currentText());
    last_amount = user_car_now.getAmount();
}

void MainWindow::showField2()
{
    ui->current_session->setValue(2);
    ui->brand_name->setText(user_car_prev.getBrandName());
    ui->type_selector->setCurrentText(user_car_prev.getType());
    ui->engine_v->setValue(user_car_prev.getEngineV());
    ui->human_capacity->setValue(user_car_prev.getHumanCapacity());
    ui->weight_capacity->setValue(user_car_prev.getWeightCapacity());
    ui->max_speed->setValue(user_car_prev.getMaxSpeed());
    ui->from_1_to_100->setValue(user_car_prev.getFrom_1To_100());
    ui->climate_control->setChecked(user_car_prev.getClimateControl());
    ui->amount->setValue(user_car_prev.getAmount());
    ui->price->setValue(user_car_prev.getPrice());
    ui->date_last_delivery->setDate(user_car_prev.getDateLastDelivery());
    onTypeChanged(ui->type_selector->currentText());
    last_amount = user_car_prev.getAmount();
}

void MainWindow::onTypeChanged(const QString &text)
{
    bool isTrailer = (text == "trailer");

    ui->engine_v->setEnabled(!isTrailer);
    ui->human_capacity->setEnabled(!isTrailer);
    ui->max_speed->setEnabled(!isTrailer);
    ui->from_1_to_100->setEnabled(!isTrailer);
    ui->climate_control->setEnabled(!isTrailer);
}

void MainWindow::onAmountChanged(int newValue)
{
    if (newValue > last_amount)
    {
        ui->date_last_delivery->setDate(QDate::currentDate());
    }
    last_amount = newValue;
}

MainWindow::~MainWindow()
{
    delete ui;
}