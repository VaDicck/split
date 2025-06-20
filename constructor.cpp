#include "constructor.h"

// Конструктор по умолчанию
constructor::constructor()
    : mod(""), filename(""), code(), arguments() {}

// Конструктор с параметрами
constructor::constructor(const QString& mod,
                         const QString& filename,
                         const QStringList& code,
                         const QVector<argument>& arguments)
    : mod(mod), filename(filename), code(code), arguments(arguments) {}


// Геттеры
QString constructor::getMod() const {
    return mod;
}

QString constructor::getFilename() const {
    return filename;
}

QStringList constructor::getCode() const {
    return code;
}

QVector<argument> constructor::getArguments() const {
    return arguments;
}

// Сеттеры
void constructor::setMod(const QString& mod) {
    this->mod = mod;
}

void constructor::setFilename(const QString& filename) {
    this->filename = filename;
}

void constructor::setCode(const QStringList& code) {
    this->code = code;
}

void constructor::setArguments(const QVector<argument>& arguments) {
    this->arguments = arguments;
}

// Перегрузка оператора ==
bool constructor::operator==(const constructor& other) const {
    return mod == other.mod &&
           filename == other.filename &&
           code == other.code &&
           arguments == other.arguments;
}

// Перегрузка оператора !=
bool constructor::operator!=(const constructor& other) const {
    return mod != other.mod &&
           filename != other.filename &&
           code != other.code &&
           arguments != other.arguments;
}
