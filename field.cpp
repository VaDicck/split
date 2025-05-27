#include "field.h"
// Геттеры
QString field::getNameField() const {
    return nameField;
}

QString field::getType() const {
    return type;
}

QString field::getMod() const {
    return mod;
}

bool field::getIsStatic() const {
    return isStatic;
}

// Сеттеры
void field::setNameField(const QString &name) {
    nameField = name;
}

void field::setType(const QString &type) {
    this->type = type;
}

void field::setMod(const QString &mod) {
    this->mod = mod;
}

void field::setIsStatic(bool isStatic) {
    this->isStatic = isStatic;
}

// Конструктор по умолчанию
field::field()
    : nameField(""), type(""), mod(""), isStatic(false) {}

// Конструктор с параметрами
field::field(const QString& name, const QString& type,
             const QString& mod, bool isStatic)
    : nameField(name), type(type), mod(mod), isStatic(isStatic) {}

// Оператор сравнения
bool field::operator==(const field& other) const {
    return nameField == other.nameField &&
           type == other.type &&
           mod == other.mod &&
           isStatic == other.isStatic;
}
