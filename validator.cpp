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
    int strLength = string.length();
    if (string.isEmpty())
    {
        return QValidator::Intermediate;
    }
    if (string.length() > 30)
    {
        return QValidator::Invalid;
    }
    QString proper_values = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < strLength; i++)
    {
        QChar item = string[i];
        if (!proper_values.contains(item.toUpper()))
        {
            return QValidator::Invalid;
        }
    }



    bool inaccurate = false;


    if (!string[0].isLetter())
    {
        return QValidator::Intermediate;
    }

    return QValidator::Acceptable;
}



