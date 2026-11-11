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

    connect(ui->Delete_button, SIGNAL(clicked()), this, SLOT(deleteRecord()));

    ui->type_selector->addItems(CAR_TYPES);
    ui->firm_selector_2->addItems((FIRMS));
    ui->brand_name->setValidator(new Validator(this));
    // QStringList records = {};
    // ui->browse_records->addItems(records);
}



void MainWindow::update_browser()
{
    Car* selectedCar = nullptr;
    int mod_row = ui->browse_records->currentRow();
    if (mod_row >= 0 && mod_row < number) {
        selectedCar = records[mod_row];
    }

    int change = 1;
    for (int count = 1; count < number && change != 0; count++)
    {
        Car* buf = nullptr;
        change = 0;
        for (int num = count; num < number; num++)
        {
            if ((*records[num]) < (*records[num - 1]) )
            {
                buf = records[num];
                records[num - 1] = records[num];
                records[num] = buf;
                change = 1;
            }
        }
    }
    ui->browse_records->clear();
    int new_selected_row = -1;

    for (int item = 0; item < number; item++)
    {
        records[item]->number_record = item;
        QString info;
        info.append(records[item]->getBrandName()).append("      ").append(QString::number(records[item]->getAmount())).append("      ").append(QString::number(records[item]->getPrice()));
        ui->browse_records->addItem(info);

        if (records[item] == selectedCar)
        {
            new_selected_row = item;
        }
    }
    if (new_selected_row != -1)
    {
        ui->browse_records->setCurrentRow(new_selected_row);
    }
    else
    {
        ui->browse_records->setCurrentRow(number-1);
    }
}

void MainWindow::createRecord()
{
    if (number >= 100)
    {
        QMessageBox::warning(this, "Ошибка", "переполнение хранилища (лимит 100 записей).\n"
                                             "удалите хотя бы одну запись для создания новой");
        return;
    }

    // if (records[number] != nullptr)
    // {
    //     delete records[number];
    //     records[number] = nullptr;
    // }

    if (!ui->brand_name->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Название модели введено неверно!\n"
                             "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
        return;
    }
    Car *current_record = new Car();
    records[number] = current_record;
    records[number]->setCarFifm(ui->firm_selector_2->currentText());
    records[number]->number_record = number;
    records[number]->setAmount(ui->amount->value());
    records[number]->setBrandName(ui->brand_name->text());
    records[number]->setClimateControl(ui->climate_control->isChecked());
    records[number]->setDateLastDelivery(ui->date_last_delivery->date());
    records[number]->setEngineV(ui->engine_v->value());
    records[number]->setFrom_1To_100(ui->from_1_to_100->value());
    records[number]->setHumanCapacity(ui->human_capacity->value());
    records[number]->setMaxSpeed(ui->max_speed->value());
    records[number]->setPrice(ui->price->value());
    records[number]->setType(ui->type_selector->currentText());
    records[number]->setWeightCapacity(ui->weight_capacity->value());

    number++;

    update_browser();
    int found = false;
    for (int i = 0; i < number && !found; i++)
    {
        if (records[i] == current_record)
        {
            ui->browse_records->setCurrentRow(i);
            found = true;
        }
    }
}

void MainWindow::deleteRecord()
{
    int row = ui->browse_records->currentRow();
    if (row < 0 || row >= number) return;

    delete records[row];

    for (int item = row; item < number; item++)
    {
        records[item] = records[item + 1];
    }
    records[number - 1] = nullptr;
    number--;

    update_browser();
}

void MainWindow::saveButtonPressed()
{
    int row = ui->browse_records->currentRow();
    if (row < 0 || row >= number) return;

    if (!ui->brand_name->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Название модели введено неверно!\n"
                             "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
        return;
    }

    records[row]->setCarFifm(ui->firm_selector_2->currentText());
    records[row]->setAmount(ui->amount->value());
    records[row]->setBrandName(ui->brand_name->text());
    records[row]->setClimateControl(ui->climate_control->isChecked());
    records[row]->setDateLastDelivery(ui->date_last_delivery->date());
    records[row]->setEngineV(ui->engine_v->value());
    records[row]->setFrom_1To_100(ui->from_1_to_100->value());
    records[row]->setHumanCapacity(ui->human_capacity->value());
    records[row]->setMaxSpeed(ui->max_speed->value());
    records[row]->setPrice(ui->price->value());
    records[row]->setType(ui->type_selector->currentText());
    records[row]->setWeightCapacity(ui->weight_capacity->value());

    update_browser();
}

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
    if (row < 0 || row >= number) return;

    ui->brand_name->setText(records[row]->getBrandName());
    ui->amount->setValue(records[row]->getAmount());
    ui->price->setValue(records[row]->getPrice());
    ui->engine_v->setValue(records[row]->getEngineV());
    ui->human_capacity->setValue(records[row]->getHumanCapacity());
    ui->weight_capacity->setValue(records[row]->getWeightCapacity());
    ui->max_speed->setValue(records[row]->getMaxSpeed());
    ui->from_1_to_100->setValue(records[row]->getFrom_1To_100());
    ui->climate_control->setChecked(records[row]->getClimateControl());
    ui->type_selector->setCurrentText(records[row]->getType());
    ui->firm_selector_2->setCurrentText(records[row]->getCarFirm());
    ui->date_last_delivery->setDate(records[row]->getDateLastDelivery());
};




MainWindow::~MainWindow()
{
    for (int i = 0; i < 100; ++i)
    {
        delete records[i];
        records[i] = nullptr;
    }
    delete ui;
}
