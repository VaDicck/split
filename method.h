/*!
 * \file method.h
 * \brief Заголовочный файл класса method
 *
 * Содержит объявление класса для хранения информации о методе класса:
 * - Имя и возвращаемый тип
 * - Модификаторы (abstract, static)
 * - Тело метода и аргументы
 * - Наследование от constructor
 *\file method.cpp
 *\brief Реализация методов класса method
 */

#ifndef METHOD_H
#define METHOD_H

#include "constructor.h"
#include <QString>
#include <QStringList>

/**
 * \class method
 * \brief Класс для хранения данных о методе класса
 *
 * Наследует функциональность constructor и добавляет:
 * - Информацию о возвращаемом типе
 * - Флаги abstract и static
 * - Имя метода
 */
class method : public constructor {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает пустой объект с:
     *  - Пустыми значениями nameMethod и returnType
     *  - Флагами isAbstract и isStatic = false
     *  - Наследуемыми полями constructor инициализированными по умолчанию
     */
    method();

    /**
     * \brief Конструктор с параметрами
     * \param[in] nameMethod Имя метода
     * \param[in] returnType Возвращаемый тип
     * \param[in] isAbstract Флаг абстрактности
     * \param[in] isStatic Флаг статичности
     * \param[in] mod Модификатор доступа
     * \param[in] filename Имя файла с кодом метода
     * \param[in] code Тело метода (строки кода)
     * \param[in] arguments Вектор аргументов
     */
    method(const QString& nameMethod,
           const QString& returnType,
           bool isAbstract,
           bool isStatic,
           const QString& mod,
           const QString& filename,
           const QStringList& code,
           const QVector<argument>& arguments);

    /**
     * \brief Конструктор для создания метода-конструктора
     * \param[in] mod Модификатор доступа
     * \param[in] filename Имя файла с кодом метода
     * \param[in] code Тело метода (строки кода)
     * \param[in] arguments Вектор аргументов
     */
    method(const QString& mod,
           const QString& filename,
           const QStringList& code,
           const QVector<argument>& arguments);
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить имя метода
     * \return Имя метода как QString
     */
    QString getNameMethod() const;

    /**
     * \brief Получить возвращаемый тип
     * \return Возвращаемый тип как QString
     */
    QString getReturnType() const;

    /**
     * \brief Проверить абстрактность метода
     * \return true если метод абстрактный
     */
    bool getIsAbstract() const;

    /**
     * \brief Проверить статичность метода
     * \return true если метод статический
     */
    bool getIsStatic() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить имя метода
     * \param[in] name Новое имя метода
     */
    void setNameMethod(const QString& name);

    /**
     * \brief Установить возвращаемый тип
     * \param[in] returnType Новый возвращаемый тип
     */
    void setReturnType(const QString& returnType);

    /**
     * \brief Установить флаг абстрактности
     * \param[in] isAbstract Новое значение флага
     */
    void setIsAbstract(bool isAbstract);

    /**
     * \brief Установить флаг статичности
     * \param[in] isStatic Новое значение флага
     */
    void setIsStatic(bool isStatic);
    /// @}

    /// \name Операторы сравнения
    /// @{
    /**
     * \brief Оператор сравнения
     * \param[in] other Сравниваемый метод
     * \return true если все поля идентичны
     */
    bool operator==(const method& other) const;

    /**
     * \brief Оператор неравенства
     * \param[in] other Сравниваемый метод
     * \return true если есть различия в полях
     */
    bool operator!=(const method& other) const;
    /// @}

private:
    QString nameMethod;    ///< Имя метода
    QString returnType;    ///< Возвращаемый тип
    bool isAbstract;       ///< Флаг абстрактного метода
    bool isStatic;         ///< Флаг статического метода
};

/**
 * \brief Хеш-функция для класса method, необходимая для использования method в QSet
 * \param[in] m Объект для хеширования
 * \param[in] seed Начальное значение хеша
 * \return Уникальный хеш-код
 */
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
