/*!
 * \file error.h
 * \brief Заголовочный файл класса error
 *
 * Содержит объявление класса для хранения информации об ошибках:
 * - Тип ошибки (из typemistakes.h)
 * - Данные об ошибке
 *\file error.cpp
 *\brief Реализация методов класса error
 */

#ifndef ERROR_H
#define ERROR_H

#include "typemistakes.h"
#include <QString>
#include <QHash>

/**
 * \class error
 * \brief Класс для хранения информации об ошибке
 */
class error {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает пустой объект с:
     *  - Нулевыми значениями числовых полей
     *  - Пустыми строковыми полями
     */
    error();

    /**
     * \brief Конструктор с полной параметризацией
     * \param[in] type Тип ошибки (из перечисления typeMistakes)
     * \param[in] fNum Номер файла (по умолчанию 0)
     * \param[in] cStr Количество строк в файле (по умолчанию 0)
     * \param[in] cJava Количество Java-файлов (по умолчанию 0)
     * \param[in] cCls Количество классов (по умолчанию 0)
     * \param[in] cInt Количество интерфейсов (по умолчанию 0)
     * \param[in] nCls Имя класса (по умолчанию "")
     * \param[in] nInt Имя интерфейса (по умолчанию "")
     * \param[in] cMeth Количество методов (по умолчанию 0)
     * \param[in] cFld Количество полей (по умолчанию 0)
     * \param[in] nStr Номер строки с ошибкой (по умолчанию 0)
     * \param[in] path Путь к Java-файлу (по умолчанию "")
     */
    error(typeMistakes type, int fNum = 0, int cStr = 0, int cJava = 0,
          int cCls = 0, int cInt = 0, const QString& nCls = "",
          const QString& nInt = "", int cMeth = 0, int cFld = 0,
          int nStr = 0, QString path = "");
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить тип ошибки
     * \return Тип ошибки как typeMistakes
     */
    typeMistakes getTypeMistake() const;

    /**
     * \brief Получить номер файла
     * \return Номер файла как int
     */
    int getFileNumber() const;

    /**
     * \brief Получить количество строк в файле
     * \return Количество строк как int
     */
    int getCountStrFile() const;

    /**
     * \brief Получить количество Java-файлов
     * \return Количество файлов как int
     */
    int getCountJavaFile() const;

    /**
     * \brief Получить количество классов
     * \return Количество классов как int
     */
    int getCountClasses() const;

    /**
     * \brief Получить количество интерфейсов
     * \return Количество интерфейсов как int
     */
    int getCountInterfaces() const;

    /**
     * \brief Получить имя класса
     * \return Имя класса как QString
     */
    QString getNameClass() const;

    /**
     * \brief Получить имя интерфейса
     * \return Имя интерфейса как QString
     */
    QString getNameInterface() const;

    /**
     * \brief Получить количество методов
     * \return Количество методов как int
     */
    int getCountMethod() const;

    /**
     * \brief Получить количество полей
     * \return Количество полей как int
     */
    int getCountField() const;

    /**
     * \brief Получить номер строки с ошибкой
     * \return Номер строки как int
     */
    int getNumberStr() const;

    /**
     * \brief Получить путь к Java-файлу
     * \return Путь к файлу как QString
     */
    QString getPathJavaFile() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить тип ошибки
     * \param[in] type Новый тип ошибки
     */
    void setTypeMistake(typeMistakes type);

    /**
     * \brief Установить номер файла
     * \param[in] fNum Новый номер файла
     */
    void setFileNumber(int fNum);

    /**
     * \brief Установить количество строк в файле
     * \param[in] cStr Новое количество строк
     */
    void setCountStrFile(int cStr);

    /**
     * \brief Установить количество Java-файлов
     * \param[in] cJava Новое количество файлов
     */
    void setCountJavaFile(int cJava);

    /**
     * \brief Установить количество классов
     * \param[in] cCls Новое количество классов
     */
    void setCountClasses(int cCls);

    /**
     * \brief Установить количество интерфейсов
     * \param[in] cInt Новое количество интерфейсов
     */
    void setCountInterfaces(int cInt);

    /**
     * \brief Установить имя класса
     * \param[in] nCls Новое имя класса
     */
    void setNameClass(const QString& nCls);

    /**
     * \brief Установить имя интерфейса
     * \param[in] nInt Новое имя интерфейса
     */
    void setNameInterface(const QString& nInt);

    /**
     * \brief Установить количество методов
     * \param[in] cMeth Новое количество методов
     */
    void setCountMethod(int cMeth);

    /**
     * \brief Установить количество полей
     * \param[in] cFld Новое количество полей
     */
    void setCountField(int cFld);

    /**
     * \brief Установить номер строки с ошибкой
     * \param[in] nStr Новый номер строки
     */
    void setNumberStr(int nStr);

    /**
     * \brief Установить путь к Java-файлу
     * \param[in] path Новый путь к файлу
     */
    void setPathJavaFile(const QString& path);
    /// @}

    /// \name Операторы
    /// @{
    /**
     * \brief Оператор сравнения
     * \param[in] other Сравниваемый объект error
     * \return true если все поля идентичны
     */
    bool operator==(const error& other) const;

    /**
     * \brief Оператор неравенства
     * \param[in] other Сравниваемый объект error
     * \return true если есть различия в полях
     */
    bool operator!=(const error& other) const;
    /// @}

private:
    typeMistakes typeMistake;  ///< Тип ошибки (из typemistakes.h)
    int fileNumber;            ///< Номер файла в проекте
    int countStrFile;          ///< Общее количество строк в файле
    int countJavaFile;         ///< Количество Java-файлов в проекте
    int countClasses;          ///< Количество классов в файле
    int countInterfaces;       ///< Количество интерфейсов в файле
    QString nameClass;         ///< Имя класса, где найдена ошибка
    QString nameInterface;     ///< Имя интерфейса, где найдена ошибка
    int countMethod;           ///< Количество методов в классе/интерфейсе
    int countField;            ///< Количество полей в классе
    int numberStr;             ///< Номер строки с ошибкой
    QString pathJavaFile;      ///< Путь к файлу с ошибкой
};

/**
 * \brief Хеш-функция для класса error
 * \param[in] key Объект для хеширования
 * \param[in] seed Начальное значение хеша
 * \return Уникальный хеш-код
 */
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
