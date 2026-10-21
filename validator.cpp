#include "examplevalidator.h"

//Полное имя файла (путь, имя, расширение)
//Пример: c:\myfile.txt

ExampleValidator::ExampleValidator(QObject* parent)
    : QValidator (parent)
{

}

ExampleValidator::~ExampleValidator()
{

}

QValidator::State ExampleValidator::validate(QString &string, int &pos) const
{
    //1
    int strLength = string.length();
    for (int i = 0; i < strLength; i++)
    {
        QChar item = string[i];
        if (!(item.isLetterOrNumber() || item == '.' || item == '\\' || item == ':'))
            return QValidator::Invalid;
    }

    //количество символов в строке
    int ddotCount = string.count(':');
    bool multiSlash = string.contains("\\\\");

    //позиции символов в строке
    int dot = string.indexOf('.');
    int lastDot = string.lastIndexOf('.');
    int ddot = string.indexOf(':');
    int slash = string.indexOf('\\');
    int lastSlash = string.lastIndexOf('\\');

    //недопустимое кол-во (>1)
    if (multiSlash) return QValidator::Invalid;
    if (ddotCount > 1) return QValidator::Invalid;

    if (slash == -1 || ddot == -1) return QValidator::Intermediate;
    else if (slash < ddot) return QValidator::Invalid;

    //if (dot == -1 || slash == -1) return QValidator::Intermediate;    //изза этого условия если ввести точку и слэш
    if (dot <= slash) return QValidator::Intermediate;                 //то нельзя будет поставить двоеточие
    //вроде пофиксил

    if (ddot == -1 || ddot == 0) return QValidator::Intermediate;
    else if (ddot != 1) return Invalid;

    //if (dotCount < 1 || ddotCount < 1 || string.count('\\') == 0) return QValidator::Intermediate;

    bool inaccurate = false;

    inaccurate |= lastSlash > lastDot;
    inaccurate |= ddot > slash;
    inaccurate |= ddot > lastDot;
    inaccurate |= !string.begin()->isLetter();
    inaccurate |= ddot != 1;
    inaccurate |= slash != ddot+1;
    inaccurate |= lastSlash + 1 == lastDot; //если между подкаталогом и расшиирением нет имени файла
    inaccurate |= lastDot == strLength - 1; //если нет расширения файла
    inaccurate |= lastSlash == strLength - 1; //если вообще нет файла в новом подкаталоге
    inaccurate |= lastDot < slash;

    if (inaccurate) return QValidator::Intermediate;



    return QValidator::Acceptable;
    //!!!!!проверить диск, с :\ и проверить расширение файла .gxg
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




