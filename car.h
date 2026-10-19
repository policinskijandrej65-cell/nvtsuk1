#include <QDate>
#include <QString>
#ifndef CAR
#define CAR
//машинки врум
class Car
{
public:
    Car();
    QString types[4] = {"truck", "passenger", "bus", "trailer"};
    QString car_type;

private:
    struct MainProperties
    {
        QString brand_name;
        float engine_V;
        int human_capacity;
        int weight_capacity;
        int max_speed;
        float from_1_to_100;
        bool climate_control;
    } props;

    int amount;
    int price;
    QDate date_last_delivery;

public:
    bool validate(QString user_string);
    bool setBrandName(QString user_string);
    bool setType(QString user_type);
    bool setEngineV(float user_value);
    bool setHumanCapacity(int user_value);
    bool setWeightCapacity(int user_value);
    bool setMaxSpeed(int user_value);
    bool setFrom_1To_100(float user_value);
    bool setClimateControl(bool user_value);
    bool setAmount(int user_value);
    bool setPrice(int user_value);
    bool setDateLastDelivery(QDate user_date);
};

#endif // CAR