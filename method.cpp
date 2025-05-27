#include "method.h"

// Конструктор по умолчанию
method::method()
    : constructor(),
    nameMethod(""),
    returnType("void"),
    isAbstract(false),
    isStatic(false) {}

// Конструктор со всеми параметрами
method::method(const QString& nameMethod,
               const QString& returnType,
               bool isAbstract,
               bool isStatic,
               const QString& mod,
               const QString& filename,
               const QStringList& code,
               const QVector<argument>& arguments)
    : constructor(mod, filename, code, arguments),
    nameMethod(nameMethod),
    returnType(returnType),
    isAbstract(isAbstract),
    isStatic(isStatic) {}

// Геттеры
QString method::getNameMethod() const {
    return nameMethod;
}

QString method::getReturnType() const {
    return returnType;
}

bool method::getIsAbstract() const {
    return isAbstract;
}

bool method::getIsStatic() const {
    return isStatic;
}

// Сеттеры
void method::setNameMethod(const QString& name) {
    nameMethod = name;
}

void method::setReturnType(const QString& returnType) {
    this->returnType = returnType;
}

void method::setIsAbstract(bool isAbstract) {
    this->isAbstract = isAbstract;
}

void method::setIsStatic(bool isStatic) {
    this->isStatic = isStatic;
}

// Перегрузка оператора ==
bool method::operator==(const method& other) const {
    return (static_cast<const constructor&>(*this) ==
            static_cast<const constructor&>(other)) &&
           (nameMethod == other.nameMethod) &&
           (returnType == other.returnType) &&
           (isAbstract == other.isAbstract) &&
           (isStatic == other.isStatic);
}
