#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "validator.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Save_button, SIGNAL(clicked()), this, SLOT(saveButtonPressed()));
    //connect(ui->current, QOverload<QString>::of(&::), this, [this](int newValue)
            //{ ui->browse_session->setCurrentRow((int)current[8]); });

    connect(ui->browse_records, &QListWidget::currentRowChanged, this, &MainWindow::currentRowChanged);

    connect(ui->type_selector, &QComboBox::currentTextChanged, this, &MainWindow::onTypeChanged);

    connect(ui->amount, &QSpinBox::valueChanged, this, &MainWindow::onAmountChanged);

    connect(ui->Create_button, SIGNAL(clicked()), this, SLOT(createRecord()));

    ui->type_selector->addItems(CAR_TYPES);
    ui->firm_selector_2->addItems((FIRMS));
    ui->brand_name->setValidator(new Validator(this));
    QStringList records = {};
    ui->browse_records->addItems(records);
}

void MainWindow::createRecord()
{
    if (records[number].isValid())
    number++;
}

void MainWindow::saveButtonPressed()
{
        if (!ui->brand_name->hasAcceptableInput())
        {
            QMessageBox::warning(this, "Ошибка",
                                 "Название модели введено неверно!\n"
                                 "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
            return;
        }
        records[number].setCarFifm(ui->firm_selector_2->currentText());
        records[number].current_session = ui->current->text();
        records[number].setAmount(ui->amount->value());
        records[number].setBrandName(ui->brand_name->text());
        records[number].setClimateControl(ui->climate_control->isChecked());
        records[number].setDateLastDelivery(ui->date_last_delivery->date());
        records[number].setEngineV(ui->engine_v->value());
        records[number].setFrom_1To_100(ui->from_1_to_100->value());
        records[number].setHumanCapacity(ui->human_capacity->value());
        records[number].setMaxSpeed(ui->max_speed->value());
        records[number].setPrice(ui->price->value());
        records[number].setType(ui->type_selector->currentText());
        records[number].setWeightCapacity(ui->weight_capacity->value());
        QString info;
        info.append(records[number].getBrandName()).append("      ").append(QString::number(records[number].getAmount())).append("      ").append(QString::number(records[number].getPrice()));
        ui->browse_records->addItem(info);
}

// void MainWindow::showField()
// {
//     ui->current_session->setValue(1);
//     ui->current->setText("запись 1");
//     ui->firm_selector_2->setCurrentText(user_car_now.getCarFirm());
//     ui->brand_name->setText(user_car_now.getBrandName());
//     ui->type_selector->setCurrentText(user_car_now.getType());
//     ui->engine_v->setValue(user_car_now.getEngineV());

void MainWindow::onTypeChanged(const QString &text)
{
    bool isTrailer = (text == "прицеп");
    ui->firm_selector_2->setEnabled(!isTrailer);
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

void MainWindow::currentRowChanged(int row)
{
    //showField(row);
};


MainWindow::~MainWindow()
{
    delete ui;
}
