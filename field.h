#ifndef FIELD_H
#define FIELD_H
#include <QString>

class field {
private:
    QString nameField; // имя поля
    QString type;      // тип поля
    QString mod; // модификатор доступа
    bool isStatic = false;     // статическое поле
public:
    // Геттеры
    QString getNameField() const;
    QString getType() const;
    QString getMod() const;
    bool getIsStatic() const;

    // Сеттеры
    void setNameField(const QString &name);
    void setType(const QString &type);
    void setMod(const QString &mod);
    void setIsStatic(bool isStatic);

    // Конструкторы
    field();
    field(const QString& name, const QString& type,
          const QString& mod = "", bool isStatic = false);

    // Оператор сравнения
    bool operator==(const field& other) const;
};

#endif // FIELD_H
