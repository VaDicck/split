/*!
 * \file field.h
 * \brief Заголовочный файл класса field
 *
 * Содержит объявление класса для хранения информации о поле класса:
 * - Имя и тип поля
 * - Модификаторы доступа (Public/Protected/Private/default)
 * - Флаг статичности
 *\file field.cpp
 *\brief Реализация методов класса field
 */

#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QHash>
#include <QMap>

/**
 * \class field
 * \brief Класс для хранения метаинформации о поле класса
 *
 * Обеспечивает хранение и доступ к:
 * - Основным характеристикам поля (имя, тип)
 * - Модификаторам доступа (Public/Protected/Private/default)
 * - Флагу статичности
 */
class field {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает объект с:
     *  - Пустыми значениями nameField, type и mod
     *  - Флагом isStatic = false
     */
    field();

    /**
     * \brief Конструктор с параметрами
     * \param[in] name Имя поля
     * \param[in] type Тип поля
     * \param[in] mod Модификатор доступа (по умолчанию "default") (Public/Protected/Private/default)
     * \param[in] isStatic Флаг статичности (по умолчанию false)
     */
    field(const QString& name, const QString& type,
          const QString& mod = "default", bool isStatic = false);
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить имя поля
     * \return Имя поля как QString
     */
    QString getNameField() const;

    /**
     * \brief Получить тип поля
     * \return Тип поля как QString
     */
    QString getType() const;

    /**
     * \brief Получить модификатор доступа
     * \return Модификатор доступа как QString
     */
    QString getMod() const;

    /**
     * \brief Проверить статичность поля
     * \return true если поле статическое
     */
    bool getIsStatic() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить имя поля
     * \param[in] name Новое имя поля
     */
    void setNameField(const QString &name);

    /**
     * \brief Установить тип поля
     * \param[in] type Новый тип поля
     */
    void setType(const QString &type);

    /**
     * \brief Установить модификатор доступа
     * \param[in] mod Новый модификатор доступа
     */
    void setMod(const QString &mod);

    /**
     * \brief Установить флаг статичности
     * \param[in] isStatic Новое значение флага статичности
     */
    void setIsStatic(bool isStatic);
    /// @}

    /// \name Операторы сравнения
    /// @{
    /**
     * \brief Оператор сравнения
     * \param[in] other Сравниваемый объект field
     * \return true если все поля идентичны
     */
    bool operator==(const field& other) const;

    /**
     * \brief Оператор неравенства
     * \param[in] other Сравниваемый объект field
     * \return true если есть различия в полях
     */
    bool operator!=(const field& other) const;
    /// @}

private:
    QString nameField;  ///< Имя поля
    QString type;       ///< Тип поля
    QString mod;        ///< Модификатор доступа (Public/Protected/Private/default)
    bool isStatic;      ///< Флаг статического поля
};

#endif // FIELD_H
