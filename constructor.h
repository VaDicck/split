#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include <QString>
#include <QStringList>
#include <QVector>
#include "argument.h"

class constructor {
public:
    // Конструкторы
    constructor();
    constructor(const QString& mod,
                const QString& filename,
                const QStringList& code,
                const QVector<argument>& arguments);

    // Геттеры
    QString getMod() const;
    QString getFilename() const;
    QStringList getCode() const;
    QVector<argument> getArguments() const;

    // Сеттеры
    void setMod(const QString& mod);
    void setFilename(const QString& filename);
    void setCode(const QStringList& code);
    void setArguments(const QVector<argument>& arguments);

    // Перегрузка операторов
    bool operator==(const constructor& other) const;
    bool operator!=(const constructor& other) const;
private:
    QString mod; // Модификатор доступа
    QString filename; // Имя файла
    QStringList code; // Код
    QVector<argument> arguments; // Аргументы
};


// Хеш-функция
inline uint qHash(const constructor& key, uint seed = 0) noexcept
{
    uint hash = qHash(key.getMod(), seed);
    hash ^= qHash(key.getFilename(), seed + 1);
    hash ^= qHash(key.getCode(), seed + 2);
    hash ^= qHash(key.getArguments(), seed + 3);

    return hash;
}
#endif // CONSTRUCTOR_H
