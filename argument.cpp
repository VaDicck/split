#include "argument.h"

// Сеттеры
void argument::setName(const QString& name){
    this->nameArgument = name;
}

void argument::setType(const QString& type){
    this->type = type;
}

// Геттеры
QString argument::getName() const{
    return this->nameArgument;
}

QString argument::getType() const{
    return this->type;
}

// Конструктор по умолчанию
argument::argument() : nameArgument(""), type("") {}

// Конструктор с параметрами
argument::argument(const QString& name, const QString& type)
    : nameArgument(name), type(type) {}

// Перегрузка ==
bool argument::operator==(const argument& other) const {
    return nameArgument == other.nameArgument &&
           type == other.type;
}
