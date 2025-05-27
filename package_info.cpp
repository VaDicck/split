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

QMap<QString, package_info> package_info::getChildren() const {
    return children;
}

QMap<QString, class_info> package_info::getIncludesClasses() const {
    return includesClasses;
}

QMap<QString, interface_info> package_info::getIncludesInterfaces() const {
    return includesInterfaces;
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

// Перегрузка оператора ==
bool package_info::operator==(const package_info& other) const {
    return namePackage == other.namePackage &&
           children == other.children &&
           includesClasses == other.includesClasses &&
           includesInterfaces == other.includesInterfaces;
}
