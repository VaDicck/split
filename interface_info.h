#ifndef INTERFACE_INFO_H
#define INTERFACE_INFO_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QSet>
#include "field.h"
#include "method.h"

class class_info;

class interface_info {
public:
    // Конструктор
    interface_info(const QString& nameInterface = "",
                   const QString& mod = "",
                   const QStringList& extends = QStringList(),
                   const QMap<QString, field>& fields = QMap<QString, field>(),
                   const QSet<method>& methods = QSet<method>(),
                   const QMap<QString, interface_info>& includeInterface = QMap<QString, interface_info>(),
                   const QMap<QString, class_info>& includeClass = QMap<QString, class_info>(),
                   const QStringList& import = QStringList());

    // Геттеры
    QString getNameInterface() const;
    QString getMod() const;
    QStringList getExtends() const;
    QMap<QString, field> getFields() const;
    QSet<method> getMethods() const;
    QMap<QString, interface_info> getIncludeInterface() const;
    QMap<QString, class_info> getIncludeClass() const;
    QStringList getImport() const;

    // Сеттеры
    void setNameInterface(const QString& name);
    void setMod(const QString& mod);
    void setExtends(const QStringList& extends);
    void setFields(const QMap<QString, field>& fields);
    void setMethods(const QSet<method>& methods);
    void setIncludeInterface(const QMap<QString, interface_info>& includeInterface);
    void setIncludeClass(const QMap<QString, class_info>& includeClass);
    void setImport(const QStringList& import);

    // Добавление родительского
    void addExtend(const QString newExtend);

    // Перегрузка оператора ==
    bool operator==(const interface_info& other) const;
    // Перегрузка оператора !=
    bool operator!=(const interface_info& other) const;

private:
    QString nameInterface;
    QString mod;
    QStringList extends;
    QMap<QString, field> fields;
    QSet<method> methods;
    QMap<QString, interface_info> includeInterface;
    QMap<QString, class_info> includeClass;
    QStringList import;
};


#endif // INTERFACE_INFO_H
