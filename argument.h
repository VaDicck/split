#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <QString>
#include <QHash>
class argument
{
private:
    QString nameArgument;  // Имя аргумента
    QString type;          // Тип аргумента
public:
    // Геттеры
    QString getName() const;
    QString getType() const;

    // Сеттеры
    void setName(const QString& name);
    void setType(const QString& type);

    // Конструкторы
    argument();
    argument(const QString& name, const QString& type);

    // Перегрузка оператора сравнения
    bool operator==(const argument& other) const;
};

// Хеш-функция
inline uint qHash(const argument &arg, uint seed = 0) {
    return qHash(arg.getName(), seed) ^ qHash(arg.getType());
}

// QVector<argument>
inline uint qHash(const QVector<argument> &vec, uint seed = 0) {
    uint hash = seed;
    for (const argument &arg : vec) {
        hash ^= qHash(arg, seed);
    }
    return hash;
}
#endif // ARGUMENT_H
