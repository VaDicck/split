#include "class_info.h"
#include "interface_info.h"

// Конструктор по умолчанию
class_info::class_info()
    : nameClass(""),
    mod(""),
    extend(""),
    implements(),
    constructors(),
    fields(),
    methods(),
    includesClasses(),
    includeInterface(),
    import(),
    isAbstract(false),
    isStatic(false) {}

// Конструктор со всеми параметрами
class_info::class_info(const QString& nameClass,
                       const QString& mod,
                       const QString& extend,
                       const QStringList& implements,
                       const QList<constructor>& constructors,
                       const QMap<QString, field>& fields,
                       const QMap<QString, method>& methods,
                       const QMap<QString, class_info>& includesClasses,
                       const QMap<QString, interface_info>& includeInterface,
                       const QStringList& import,
                       bool isAbstract,
                       bool isStatic)
    : nameClass(nameClass),
    mod(mod),
    extend(extend),
    implements(implements),
    constructors(constructors),
    fields(fields),
    methods(methods),
    includesClasses(includesClasses),
    includeInterface(includeInterface),
    import(import),
    isAbstract(isAbstract),
    isStatic(isStatic) {}

// Геттеры
QString class_info::getNameClass() const {
    return nameClass;
}

QString class_info::getMod() const {
    return mod;
}

QString class_info::getExtend() const {
    return extend;
}

QStringList class_info::getImplements() const {
    return implements;
}

QList<constructor> class_info::getConstructors() const {
    return constructors;
}

QMap<QString, field> class_info::getFields() const {
    return fields;
}

QMap<QString, method> class_info::getMethods() const {
    return methods;
}

QMap<QString, class_info> class_info::getIncludesClasses() const {
    return includesClasses;
}

QMap<QString, interface_info> class_info::getIncludeInterface() const {
    return includeInterface;
}

QStringList class_info::getImport() const {
    return import;
}

bool class_info::getIsAbstract() const {
    return isAbstract;
}

bool class_info::getIsStatic() const {
    return isStatic;
}

// Сеттеры
void class_info::setNameClass(const QString& name) {
    nameClass = name;
}

void class_info::setMod(const QString& mod) {
    this->mod = mod;
}

void class_info::setExtend(const QString& extend) {
    this->extend = extend;
}

void class_info::setImplements(const QStringList& implements) {
    this->implements = implements;
}

void class_info::setConstructors(const QList<constructor>& constructors) {
    this->constructors = constructors;
}

void class_info::setFields(const QMap<QString, field>& fields) {
    this->fields = fields;
}

void class_info::setMethods(const QMap<QString, method>& methods) {
    this->methods = methods;
}

void class_info::setIncludesClasses(const QMap<QString, class_info>& includesClasses) {
    this->includesClasses = includesClasses;
}

void class_info::setIncludeInterface(const QMap<QString, interface_info>& includeInterface) {
    this->includeInterface = includeInterface;
}

void class_info::setImport(const QStringList& import) {
    this->import = import;
}

void class_info::setIsAbstract(bool isAbstract) {
    this->isAbstract = isAbstract;
}

void class_info::setIsStatic(bool isStatic) {
    this->isStatic = isStatic;
}

// Перегрузка оператора ==
bool class_info::operator==(const class_info& other) const {
    return nameClass == other.nameClass &&
           mod == other.mod &&
           extend == other.extend &&
           implements == other.implements &&
           constructors == other.constructors &&
           fields == other.fields &&
           methods == other.methods &&
           includesClasses == other.includesClasses &&
           includeInterface == other.includeInterface &&
           import == other.import &&
           isAbstract == other.isAbstract &&
           isStatic == other.isStatic;
}
