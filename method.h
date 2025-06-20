#ifndef METHOD_H
#define METHOD_H

#include "constructor.h"
#include <QString>
#include <QStringList>

class method : public constructor {
public:
    // Конструкторы
    method();
    method(const QString& nameMethod,
           const QString& returnType,
           bool isAbstract,
           bool isStatic,
           const QString& mod,
           const QString& filename,
           const QStringList& code,
           const QVector<argument>& arguments);
    method(const QString& mod,
            const QString& filename,
            const QStringList& code,
            const QVector<argument>& arguments);


    // Геттеры
    QString getNameMethod() const;
    QString getReturnType() const;
    bool getIsAbstract() const;
    bool getIsStatic() const;

    // Сеттеры
    void setNameMethod(const QString& name);
    void setReturnType(const QString& returnType);
    void setIsAbstract(bool isAbstract);
    void setIsStatic(bool isStatic);

    // Перегрузка оператора ==
    bool operator==(const method& other) const;

    // Перегрузка оператора !=
    bool operator!=(const method& other) const;

private:
    QString nameMethod;
    QString returnType;
    bool isAbstract;
    bool isStatic;
};


// Хеш-функция
inline uint qHash(const method &m, uint seed = 0) {
    // Хеш родительского класса (constructor)
    uint hash = qHash(static_cast<const constructor&>(m), seed);

    // Добавляем хеши полей method
    hash ^= qHash(m.getNameMethod(), seed)
            ^ qHash(m.getReturnType())
            ^ qHash(m.getIsAbstract())
            ^ qHash(m.getIsStatic());

    return hash;
}
#endif // METHOD_H
