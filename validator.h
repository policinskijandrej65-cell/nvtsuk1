#ifndef EXAMPLEVALIDATOR_H
#define EXAMPLEVALIDATOR_H

#include <QValidator>

class Validator : public QValidator
{
    Q_OBJECT
public:
    Validator(QObject *parent);
    ~Validator();

    QValidator::State validate(QString & string, int & pos) const;
};

#endif // EXAMPLEVALIDATOR_H
