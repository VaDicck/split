#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <QString>

class argument
{
private:
    QString nameArgument;  // Имя аргумента
    QString type;          // Тип аргумента
public:
    // Геттеры
    QString getName();
    QString getType();

    // Сеттеры
    void setName(const QString& name);
    void setType(const QString& type);

    // Конструкторы
    argument();
    argument(const QString& name, const QString& type);

    // Перегрузка оператора сравнения
    bool operator==(const argument& other) const;
};

#endif // ARGUMENT_H
