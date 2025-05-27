#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QMap>
#include "constructor.h"
#include "field.h"
#include "method.h"
class interface_info;

class class_info {
public:
    // Конструкторы
    class_info();
    class_info(const QString& nameClass,
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
               bool isStatic);

    // Геттеры
    QString getNameClass() const;
    QString getMod() const;
    QString getExtend() const;
    QStringList getImplements() const;
    QList<constructor> getConstructors() const;
    QMap<QString, field> getFields() const;
    QMap<QString, method> getMethods() const;
    QMap<QString, class_info> getIncludesClasses() const;
    QMap<QString, interface_info> getIncludeInterface() const;
    QStringList getImport() const;
    bool getIsAbstract() const;
    bool getIsStatic() const;

    // Сеттеры
    void setNameClass(const QString& name);
    void setMod(const QString& mod);
    void setExtend(const QString& extend);
    void setImplements(const QStringList& implements);
    void setConstructors(const QList<constructor>& constructors);
    void setFields(const QMap<QString, field>& fields);
    void setMethods(const QMap<QString, method>& methods);
    void setIncludesClasses(const QMap<QString, class_info>& includesClasses);
    void setIncludeInterface(const QMap<QString, interface_info>& includeInterface);
    void setImport(const QStringList& import);
    void setIsAbstract(bool isAbstract);
    void setIsStatic(bool isStatic);

    // Перегрузка оператора ==
    bool operator==(const class_info& other) const;

private:
    QString nameClass;
    QString mod;
    QString extend;
    QStringList implements;
    QList<constructor> constructors;
    QMap<QString, field> fields;
    QMap<QString, method> methods;
    QMap<QString, class_info> includesClasses;
    QMap<QString, interface_info> includeInterface;
    QStringList import;
    bool isAbstract;
    bool isStatic;
};


#endif // CLASS_INFO_H
