#include "car.h"

Car::Car()
{
    this->amount = 0;
    this->props.brand_name = QString("Empty");
    this->props.engine_V = 0;
    this->props.human_capacity = 0;
    this->props.weight_capacity = 0;
    this->props.max_speed = 0;
    this->props.from_1_to_100 = 0;
    this->props.climate_control = false;
    this->price = 0;
    this->date_last_delivery = QDate::currentDate();
}


//SETTERS
bool validate(QString user_string)
{
    return true;
}

bool Car::setBrandName(QString user_string)
{
    if (user_string.length() <= 30) {
        props.brand_name = user_string;
        return true;
    }
    return false;
}

bool Car::setType(QString user_type)
{
    car_type = user_type;
    return true;
}

bool Car::setEngineV(float user_value)
{
    if (user_value >= 0.5 && user_value <= 30.0) {
        props.engine_V = user_value;
        return true;
    }
    return false;
}

bool Car::setHumanCapacity(int user_value)
{
    if (user_value >= 1 && user_value <= 300) {
        props.human_capacity = user_value;
        return true;
    }
    return false;
}

bool Car::setWeightCapacity(int user_value)
{
    if (user_value >= 100 && user_value <= 5000) {
        props.weight_capacity = user_value;
        return true;
    }
    return false;
}

bool Car::setMaxSpeed(int user_value)
{
    if (user_value >= 60 && user_value <= 320) {
        props.max_speed = user_value;
        return true;
    }
    return false;
}

bool Car::setFrom_1To_100(float user_value)
{
    if (user_value >= 5.0f && user_value <= 120.0f) {
        props.from_1_to_100 = user_value;
        return true;
    }
    return false;
}

bool Car::setClimateControl(bool user_value)
{
    props.climate_control = user_value;
    return true;
}

bool Car::setAmount(int user_value)
{
    if (user_value >= 0 && user_value <= 1000) {
        amount = user_value;
        return true;
    }
    return false;
}

bool Car::setPrice(int user_value)
{
    if (user_value >= 20 && user_value <= 3000) {
        price = user_value;
        return true;
    }
    return false;
}

bool Car::setDateLastDelivery(QDate user_date)
{
    if (user_date <= QDate::currentDate()) {
        date_last_delivery = user_date;
        return true;
    }
    return false;
}

//GETTERS
QString Car::getBrandName() const
{
    return props.brand_name;
}

QString Car::getType() const
{
    return car_type; // Предполагаю, что поле называется type (добавьте props., если оно в структуре)
}

float Car::getEngineV() const
{
    return props.engine_V;
}

int Car::getHumanCapacity() const
{
    return props.human_capacity;
}

int Car::getWeightCapacity() const
{
    return props.weight_capacity;
}

int Car::getMaxSpeed() const
{
    return props.max_speed;
}

float Car::getFrom_1To_100() const
{
    return props.from_1_to_100;
}

bool Car::getClimateControl() const
{
    return props.climate_control;
}

int Car::getAmount() const
{
    return amount;
}

int Car::getPrice() const
{
    return price;
}

QDate Car::getDateLastDelivery() const
{
    return date_last_delivery;
}