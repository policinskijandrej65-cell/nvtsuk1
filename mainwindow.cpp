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

    connect(ui->choose, SIGNAL(clicked()), this, SLOT(only_type()));

    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    ui->type_selector->addItems(CAR_TYPES);
    ui->only_type->addItems(CAR_TYPES);
    ui->firm_selector_2->addItems((FIRMS));
    ui->brand_name->setValidator(new Validator(this));
    QFont mono("Courier New", 10);
    mono.setStyleHint(QFont::Monospace);
    ui->browse_records->setFont(mono);
}


void MainWindow::addToBase(Car *current_record, int *number)
{

    records[*number] = current_record;
    sorted[*number] = current_record;
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

void MainWindow::update_browser(Car* selectedCar)
{
    if (number <= 0)
    {
        ui->browse_records->clear();
        return;
    }


    //если запись не передана, сохраняем текущую выбранную запись
    if (selectedCar == nullptr)
    {
        int row = ui->browse_records->currentRow();

        if (row >= 0 && row < number)
        {
            selectedCar = records[row];
        }
    }

    // Ищем selectedCar, удаляем его с текущей позиции и закрываем место удаления
    int old_pos = 0;
    for (old_pos; old_pos < number && records[old_pos] != selectedCar; old_pos++);


    //перемещаем запись, когда она найдена
    if (old_pos < number)
    {
        for (int new_pos = old_pos; new_pos < number - 1; new_pos++)
        {
            records[new_pos] = records[new_pos + 1];
        }

        number--;

        // Находим место вставки
        int pos = 0;
        for (pos; pos < number && *records[pos] < *selectedCar; pos++);

        // Сдвигаем элементы вправо и вставляем запись
        for (int move = number; move > pos; move--)
        {
            records[move] = records[move - 1];
        }

        records[pos] = selectedCar;
        number++;
    }

    ui->browse_records->clear();

    //запоминаем позицию нужной записи
    int selectedRow = -1;

    for (int item = 0; item < number; item++)
    {
        records[item]->number_record = item;
        QString info = (records[item]->getBrandName());
        int space = info.length();
        while (space < 35)
        {
            info += " ";
            space++;
        }
        space += QString::number(records[item]->getAmount()).length();
        info += QString::number(records[item]->getAmount());
        while (space < 42)
        {
            info += " ";
            space++;
        }
        info += QString::number(records[item]->getPrice());
        // QString info = (records[item]->getBrandName()) + "                " +
        // (QString::number(records[item]->getAmount())) + "                         " +
        // (QString::number(records[item]->getPrice())) + "          ";

        ui->browse_records->insertItem(number, info);

        //определяем новое положение записи
        if (records[item] == selectedCar)
        {
            selectedRow = item;
        }
    }

    // выделяем запись
    if (selectedRow >= 0)
    {
        ui->browse_records->setCurrentRow(selectedRow);
    }
    qDebug() << "Выделена строка:" << selectedRow;
    qDebug() << "Адрес записи:" << selectedCar;
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

    if ( ui->date_last_delivery->date() > QDate::currentDate())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Дата введена неверно\n"
                             "Она должна быть не более текущей даты.");
        return;
    }

    Car *current_record = new Car();

    addToBase(current_record, &number);

    // передаём указатель на новую запись (чтобы в браузере выделить)
    update_browser(current_record);
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

    // проверяем, остались ли записи
    if (number == 0)
    {
        ui->browse_records->clear();
        return;
    }


    // Если есть следующий элемент, выбираем его если удалили последний, выбираем предыдущий
    int newRow = (row < number) ? row : number - 1;

    update_browser(records[newRow]);


    qDebug() << "Удаляем строку:" << row;
    qDebug() << "Количество записей:" << number;
    qDebug() << "Выбираем строку:" << newRow;
    qDebug() << "Название:" << records[newRow]->getBrandName();
    qDebug() << "Адрес:" << records[newRow];
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
    records[row]->number_record = number;

    update_browser(records[row]);
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
        Car* last_record = nullptr;

        for (int i = 0; i < 10; i++)
        {
            Car *current_record = new Car();

            addToBase(current_record, &number);
            current_record->setBrandName("exampleCar"+QString::number(number));
            current_record->setAmount(i);
            current_record->setEngineV(0.5 * i + i / 10);
            current_record->setPrice(20+i);
            update_browser(current_record);
            last_record = current_record;
        }
        update_browser(last_record);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Недостаточно места для добавления 10 записей!");
    }
}

void MainWindow::only_type()
{
    ui->browse_records->clear();
    for (int i = 0; i < number; i++)
    {
        records[i] = sorted[i];
    }

    int count = 0;
    for (int item = 0; item < number; item++)
    {
        if (records[item]->car_type == ui->only_type->currentText() &&
            records[item]->getHumanCapacity() == ui->only_capacity->value())
        {
            records[count] = records[item];
            QString info = (records[item]->getBrandName());
            int space = info.length();
            while (space < 35)
            {
                info += " ";
                space++;
            }
            space += QString::number(records[item]->getAmount()).length();
            info += QString::number(records[item]->getAmount());
            while (space < 42)
            {
                info += " ";
                space++;
            }
            info += QString::number(records[item]->getPrice());
            ui->browse_records->insertItem(count, info);
            count++;
        }
    }
    ui->amount->setDisabled(true);
    ui->human_capacity->setDisabled(true);
    ui->weight_capacity->setDisabled(true);
    ui->type_selector->setDisabled(true);
    ui->firm_selector_2->setDisabled(true);
    ui->brand_name->setDisabled(true);
    ui->price->setDisabled(true);
    ui->date_last_delivery->setDisabled(true);
    ui->engine_v->setDisabled(true);
    ui->max_speed->setDisabled(true);
    ui->from_1_to_100->setDisabled(true);
    ui->climate_control->setDisabled(true);
}

void MainWindow::cancel()
{
    for (int i = 0; i < number; i++)
    {
        records[i] = sorted[i];
    }
    update_browser();
    ui->amount->setDisabled(false);
    ui->human_capacity->setDisabled(false);
    ui->weight_capacity->setDisabled(false);
    ui->type_selector->setDisabled(false);
    ui->firm_selector_2->setDisabled(false);
    ui->brand_name->setDisabled(false);
    ui->price->setDisabled(false);
    ui->date_last_delivery->setDisabled(false);
    ui->engine_v->setDisabled(false);
    ui->max_speed->setDisabled(false);
    ui->from_1_to_100->setDisabled(false);
    ui->climate_control->setDisabled(false);

    //onTypeChanged(ui->type_selector->currentText());
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
