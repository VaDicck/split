#include "package_info.h"

// Конструктор по умолчанию
package_info::package_info()
    : namePackage(""),
    children(),
    includesClasses(),
    includesInterfaces() {}

// Конструктор со всеми параметрами
package_info::package_info(const QString& namePackage,
                           const QMap<QString, package_info>& children,
                           const QMap<QString, class_info>& includesClasses,
                           const QMap<QString, interface_info>& includesInterfaces)
    : namePackage(namePackage),
    children(children),
    includesClasses(includesClasses),
    includesInterfaces(includesInterfaces) {}

// Геттеры
QString package_info::getNamePackage() const {
    return namePackage;
}

QMap<QString, package_info>& package_info::getChildren(){
    return children;
}

QMap<QString, class_info>& package_info::getIncludesClasses(){
    return includesClasses;
}

QMap<QString, interface_info>& package_info::getIncludesInterfaces(){
    return includesInterfaces;
}
const QMap<QString, class_info>& package_info::getIncludesClasses() const {
    return includesClasses;
}

const QMap<QString, interface_info>& package_info::getIncludesInterfaces() const {
    return includesInterfaces;
}

const QMap<QString, package_info>& package_info::getChildren() const {
    return children;
}
// Сеттеры
void package_info::setNamePackage(const QString& name) {
    namePackage = name;
}

void package_info::setChildren(const QMap<QString, package_info>& children) {
    this->children = children;
}

void package_info::setIncludesClasses(const QMap<QString, class_info>& includesClasses) {
    this->includesClasses = includesClasses;
}

void package_info::setIncludesInterfaces(const QMap<QString, interface_info>& includesInterfaces) {
    this->includesInterfaces = includesInterfaces;
}

// Метод для добавления дочернего пакета
void package_info::addChildPackage(const QString& name, const package_info& pkg) {
    children.insert(name, pkg);
}

// Методы для добавления контенеров
void package_info::addMapClass(const class_info &Class){
    includesClasses.insert(Class.getNameClass(), Class);
}
void package_info::addMapInterface(const interface_info &Interface){
    includesInterfaces.insert(Interface.getNameInterface(), Interface);
}

// Перегрузка оператора ==
bool package_info::operator==(const package_info& other) const {
    return namePackage == other.namePackage &&
           children == other.children &&
           includesClasses == other.includesClasses &&
           includesInterfaces == other.includesInterfaces;
}


// Метод сравнения путей к пакетам
QString package_info::compare(const package_info& other, const QString& parentPath) const {
    QString differences;
    const QString currentPath = parentPath.isEmpty() ? namePackage : parentPath + "." + namePackage;

    if (namePackage != other.namePackage) {
        differences += QString("Неверное имя пакета в позиции '%1': ожидалось '%2', получено '%3'\n").arg(parentPath).arg(other.namePackage).arg(namePackage);
    }

    // Проверяем дочерние пакеты
    for (QMap<QString, package_info>::const_iterator it = children.constBegin(); it != children.constEnd(); ++it) {
        const QString& childName = it.key();
        if (other.children.constFind(childName) == other.children.constEnd()) {
            differences += QString("Найденный пакет '%1' в пути '%2'\n").arg(childName).arg(currentPath);
        } else {
            differences += it.value().compare(other.children.value(childName), currentPath);
        }
    }

    // Проверяем лишние пакеты в other
    for (QMap<QString, package_info>::const_iterator it = other.children.constBegin(); it != other.children.constEnd(); ++it) {
        const QString& childName = it.key();
        if (children.constFind(childName) == children.constEnd()) {
            differences += QString("Ожидаемый пакет '%1' в пути '%2'\n").arg(childName).arg(currentPath);
        }
    }

    return differences;
}
