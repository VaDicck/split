#include "interface_info.h"
#include "class_info.h"

interface_info::interface_info(const QString& nameInterface,
                               const QString& mod,
                               const QStringList& extends,
                               const QMap<QString, field>& fields,
                               const QMap<QString, method>& methods,
                               const QMap<QString, interface_info>& includeInterface,
                               const QMap<QString, class_info>& includeClass,
                               const QStringList& import)
    : nameInterface(nameInterface),
    mod(mod),
    extends(extends),
    fields(fields),
    methods(methods),
    includeInterface(includeInterface),
    includeClass(includeClass),
    import(import) {}

// Геттеры
QString interface_info::getNameInterface() const {
    return nameInterface;
}

QString interface_info::getMod() const {
    return mod;
}

QStringList interface_info::getExtends() const {
    return extends;
}

QMap<QString, field> interface_info::getFields() const {
    return fields;
}

QMap<QString, method> interface_info::getMethods() const {
    return methods;
}

QMap<QString, interface_info> interface_info::getIncludeInterface() const {
    return includeInterface;
}

QMap<QString, class_info> interface_info::getIncludeClass() const {
    return includeClass;
}

QStringList interface_info::getImport() const {
    return import;
}

// Сеттеры
void interface_info::setNameInterface(const QString& name) {
    nameInterface = name;
}

void interface_info::setMod(const QString& mod) {
    this->mod = mod;
}

void interface_info::setExtends(const QStringList& extends) {
    this->extends = extends;
}

void interface_info::setFields(const QMap<QString, field>& fields) {
    this->fields = fields;
}

void interface_info::setMethods(const QMap<QString, method>& methods) {
    this->methods = methods;
}

void interface_info::setIncludeInterface(const QMap<QString, interface_info>& includeInterface) {
    this->includeInterface = includeInterface;
}

void interface_info::setIncludeClass(const QMap<QString, class_info>& includeClass) {
    this->includeClass = includeClass;
}

void interface_info::setImport(const QStringList& import) {
    this->import = import;
}

// Перегрузка оператора ==
bool interface_info::operator==(const interface_info& other) const {
    return nameInterface == other.nameInterface &&
           mod == other.mod &&
           extends == other.extends &&
           fields == other.fields &&
           methods == other.methods &&
           includeInterface == other.includeInterface &&
           includeClass == other.includeClass &&
           import == other.import;
}
