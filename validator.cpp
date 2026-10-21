#include "validator.h"

//Полное имя файла (путь, имя, расширение)
//Пример: c:\myfile.txt

Validator::Validator(QObject* parent)
    : QValidator (parent)
{

}

Validator::~Validator()
{

}

QValidator::State Validator::validate(QString &string, int &pos) const
{
    //1
    int strLength = string.length();
    for (int i = 0; i < strLength; i++)
    {
        QChar item = string[i];
        if (item.isLetterOrNumber() == false || strLength == 30)
            return QValidator::Invalid;
    }



    bool inaccurate = false;

    //inaccurate |= lastSlash > lastDot;


    if (inaccurate) return QValidator::Intermediate;



    return QValidator::Acceptable;

}


/*
     1. Проверка символов на стадии ввода (недопустимый -> invalid str)
    2. Проверка на количество двоеточий, точек и слэшей (=1, >=1, >=1)
   Если удовлетворяет, то intermediate, если нет invalid
    3. Проверка позиций двоеточия, первого слэша и последней точки
   (порядок = двоеточие->первый слэш->последняя точка)
   если корректен, flag = true, если нет flag = false
    4. Проверка состояния флага
   если true, то acceptable*/




