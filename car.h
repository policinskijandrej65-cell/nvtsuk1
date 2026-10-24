#include <QDate>
#include <QString>
#ifndef CAR
#define CAR
const QStringList CAR_TYPES = {"грузовой", "легковой", "автобус", "прицеп"};
const QStringList FIRMS = {"ВАЗ", "Audi", "BMW", "Daewoo", "Nissan", "Renault"};
//машинки врум
class Car
{
public:
    Car();
    QString car_type;
    QString current_session;

private:
    struct MainProperties
    {
        QString car_firm;
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
    //SETTERS
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
    bool setCarFifm(QString user_string); //добавил

    //GETTERS
    QString getBrandName() const;
    QString getType() const;
    float getEngineV() const;
    int getHumanCapacity() const;
    int getWeightCapacity() const;
    int getMaxSpeed() const;
    float getFrom_1To_100() const;
    bool getClimateControl() const;
    int getAmount() const;
    int getPrice() const;
    QDate getDateLastDelivery() const;
    QString getCarFirm() const;
};

#endif // CAR