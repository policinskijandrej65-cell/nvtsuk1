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

    connect(ui->browse_records, &QListWidget::currentRowChanged, this, &MainWindow::currentRowChanged);

    connect(ui->type_selector, &QComboBox::currentTextChanged, this, &MainWindow::onTypeChanged);

    connect(ui->amount, &QSpinBox::valueChanged, this, &MainWindow::onAmountChanged);

    connect(ui->Create_button, SIGNAL(clicked()), this, SLOT(createRecord()));

    connect(ui->Delete_button, SIGNAL(clicked()), this, SLOT(deleteRecord()));

    connect(ui->insert10, SIGNAL(clicked()), this, SLOT(insert10()));

    ui->type_selector->addItems(CAR_TYPES);
    ui->firm_selector_2->addItems((FIRMS));
    ui->brand_name->setValidator(new Validator(this));
}


void MainWindow::addToBase(Car *records[], Car *current_record, int *number)
{
    records[*number] = current_record;
    records[*number]->setCarFifm(ui->firm_selector_2->currentText());
    records[*number]->number_record = *number;
    records[*number]->setAmount(ui->amount->value());
    records[*number]->setBrandName(ui->brand_name->text());
    records[*number]->setClimateControl(ui->climate_control->isChecked());
    records[*number]->setDateLastDelivery(ui->date_last_delivery->date());
    records[*number]->setEngineV(ui->engine_v->value());
    records[*number]->setFrom_1To_100(ui->from_1_to_100->value());
    records[*number]->setHumanCapacity(ui->human_capacity->value());
    records[*number]->setMaxSpeed(ui->max_speed->value());
    records[*number]->setPrice(ui->price->value());
    records[*number]->setType(ui->type_selector->currentText());
    records[*number]->setWeightCapacity(ui->weight_capacity->value());

    (*number)++;
}

void MainWindow::update_browser()
{
    if (number < 0) return;
    int mod_row = ui->browse_records->currentRow();
    if (mod_row < 0)
    {
        mod_row = 0;
    }
    if (mod_row >= number)
    {
    mod_row = number - 1;
    }

    Car* selectedCar = records[mod_row];
    //найти selectedCar, удалить его с текущей позиции и закрыть место удаления
    int old_pos = 0;
    for (old_pos; old_pos<number && records[old_pos] != selectedCar; old_pos++);
    for (int new_pos = old_pos; new_pos < number - 1; new_pos++)
    {
        records[new_pos] = records[new_pos + 1];
    }
    number--;

    //найти место вставки
    int pos = 0;
    for (pos; pos < number && *records[pos] < *selectedCar; pos++ );

    //сдвинуть все элементы от нужного места вправо и вставить
    for (int move = number; move > pos ; move--)
    {
        records[move] = records[move - 1];
    }
    records[pos] = selectedCar;
    number++;

    ui->browse_records->clear();

    for (int item = 0; item < number; item++)
    {
        records[item]->number_record = item;
        QString info;
        info.append(records[item]->getBrandName()).append("      ").append(QString::number(records[item]->getAmount())).append("      ").append(QString::number(records[item]->getPrice()));
        ui->browse_records->addItem(info);
    }
    ui->browse_records->setCurrentRow(pos);


}



void MainWindow::createRecord()
{
    if (number >= 100)
    {
        QMessageBox::warning(this, "Ошибка", "переполнение хранилища (лимит 100 записей).\n"
                                             "удалите хотя бы одну запись для создания новой");
        return;
    }

    if (!ui->brand_name->hasAcceptableInput())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Название модели введено неверно!\n"
                             "Оно должно начинаться с буквы и содержать только латинские буквы и цифры.");
        return;
    }
    Car *current_record = new Car();

    addToBase(records, current_record, &number);
    int found = false;
    for (int i = 0; i < number && !found; i++)
    {
        if (records[i] == current_record)
        {
            ui->browse_records->setCurrentRow(i);
            found = true;
        }
    }
    update_browser();
}



void MainWindow::deleteRecord()
{
    int row = ui->browse_records->currentRow();
    if (row < 0 || row >= number) return;

    delete records[row];

    for (int item = row; item < number - 1; item++)
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



void MainWindow::insert10()
{
    if (number + 10 <= 100)
    {
        for (int i = 0; i < 10; i++)
        {
            Car *current_record = new Car();
            addToBase(records, current_record, &number);
            current_record->setBrandName("ExampleCar");
            update_browser();
            ui->browse_records->setCurrentRow(number - 1);
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Недостаточно места для добавления 10 записей!");
    }
}



MainWindow::~MainWindow()
{
    for (int i = 0; i < 100; ++i)
    {
        delete records[i];
        records[i] = nullptr;
    }
    delete ui;
}
