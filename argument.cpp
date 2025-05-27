#include "argument.h"

void argument::setName(const QString& name){
    this->nameArgument = name;
}

void argument::setType(const QString& type){
    this->type = type;
}

QString argument::getName(){
    return this->nameArgument;
}

QString argument::getType(){
    return this->type;
}

// Конструктор по умолчанию
argument::argument() : nameArgument(""), type("") {}

// Конструктор с параметрами
argument::argument(const QString& name, const QString& type)
    : nameArgument(name), type(type) {}


bool argument::operator==(const argument& other) const {
    return nameArgument == other.nameArgument &&
           type == other.type;
}
