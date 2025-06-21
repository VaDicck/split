#ifndef ERROR_H
#define ERROR_H

#include "typemistakes.h"
#include <QString>
#include <QHash>

class error {
private:
    typeMistakes typeMistake;  // тип ошибки
    int fileNumber;            // номер файла
    int countStrFile;          // количество строк в файле
    int countJavaFile;         // количество Java файлов
    int countClasses;          // количество классов
    int countInterfaces;       // количество интерфейсов
    QString nameClass;         // имя класса
    QString nameInterface;     // имя интерфейса
    int countMethod;           // количество методов
    int countField;            // количество полей
    int numberStr;             // номер строки
    QString pathJavaFile;      // путь Java файла
public:
    // Конструкторы
    error();
    error(typeMistakes type, int fNum = 0, int cStr = 0, int cJava = 0, int cCls = 0, int cInt = 0, const QString& nCls = "",
    const QString& nInt = "", int cMeth = 0, int cFld = 0, int nStr = 0, QString pathJavaFile = "");

    typeMistakes getTypeMistake() const;
    int getFileNumber() const;
    int getCountStrFile() const;
    int getCountJavaFile() const;
    int getCountClasses() const;
    int getCountInterfaces() const;
    QString getNameClass() const;
    QString getNameInterface() const;
    int getCountMethod() const;
    int getCountField() const;
    int getNumberStr() const;
    QString getPathJavaFile() const;

    // Сеттеры
    void setTypeMistake(typeMistakes type);
    void setFileNumber(int fNum);
    void setCountStrFile(int cStr);
    void setCountJavaFile(int cJava);
    void setCountClasses(int cCls);
    void setCountInterfaces(int cInt);
    void setNameClass(const QString& nCls);
    void setNameInterface(const QString& nInt);
    void setCountMethod(int cMeth);
    void setCountField(int cFld);
    void setNumberStr(int nStr);
    void setPathJavaFile(const QString& path);

    // Операторы сравнения
    bool operator==(const error& other) const;
    bool operator!=(const error& other) const;
};

// Хеш-функция
inline uint qHash(const error& key, uint seed = 0) noexcept
{
    uint hash = qHash(static_cast<int>(key.getTypeMistake()), seed);
    hash ^= qHash(key.getFileNumber(), seed + 1);
    hash ^= qHash(key.getCountStrFile(), seed + 2);
    hash ^= qHash(key.getCountJavaFile(), seed + 3);
    hash ^= qHash(key.getCountClasses(), seed + 4);
    hash ^= qHash(key.getCountInterfaces(), seed + 5);
    hash ^= qHash(key.getNameClass(), seed + 6);
    hash ^= qHash(key.getNameInterface(), seed + 7);
    hash ^= qHash(key.getCountMethod(), seed + 8);
    hash ^= qHash(key.getCountField(), seed + 9);
    hash ^= qHash(key.getNumberStr(), seed + 10);
    hash ^= qHash(key.getPathJavaFile(), seed + 11);

    return hash;
}


#endif // ERROR_H
