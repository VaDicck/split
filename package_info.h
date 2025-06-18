#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H

#include <QString>
#include <QMap>
#include "class_info.h"
#include "interface_info.h"

class package_info {
public:
    // Конструкторы
    package_info();
    package_info(const QString& namePackage,
                 const QMap<QString, package_info>& children = QMap<QString, package_info>(),
                 const QMap<QString, class_info>& includesClasses = QMap<QString, class_info>(),
                 const QMap<QString, interface_info>& includesInterfaces = QMap<QString, interface_info>());

    // Геттеры
    QString getNamePackage() const;
    QMap<QString, package_info>& getChildren();
    QMap<QString, class_info>& getIncludesClasses();
    QMap<QString, interface_info>& getIncludesInterfaces();

    // Сеттеры
    void setNamePackage(const QString& name);
    void setChildren(const QMap<QString, package_info>& children);
    void setIncludesClasses(const QMap<QString, class_info>& includesClasses);
    void setIncludesInterfaces(const QMap<QString, interface_info>& includesInterfaces);

    // Методы для работы с дочерними пакетами
    void addChildPackage(const QString& name, const package_info& pkg);

    // Методы для добавления контенеров
    void addMapClass(const class_info &Class);
    void addMapInterface(const interface_info &Interface);

    // Перегрузка оператора ==
    bool operator==(const package_info& other) const;

    // Метод для сравнивания путей пакетов
    QString compare(const package_info& other, const QString& parentPath = "") const;

private:
    QString namePackage;
    QMap<QString, package_info> children;
    QMap<QString, class_info> includesClasses;
    QMap<QString, interface_info> includesInterfaces;
};

#endif // PACKAGE_INFO_H
