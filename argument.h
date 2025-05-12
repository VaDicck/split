#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <QString>

class argument
{
private:
    QString nameArgument;  // Имя аргумента
    QString type;          // Тип аргумента
public:
    void setName(const QString& name); //Сеттер для имени
    void setType(const QString& type); //Сеттер для типа
    QString getName(); //Геттер для имени
    QString getType(); //Геттер для типа
};

#endif // ARGUMENT_H
