/*!
 * \file interface_info.h
 * \brief Заголовочный файл класса interface_info
 *
 * Содержит объявление класса для хранения информации об интерфейсе:
 * - Модификаторы, наследование интерфейсов
 * - Поля и методы интерфейса
 * - Вложенные интерфейсы и классы
 * - Импорты
 *\file interface_info.cpp
 *\brief Реализация методов класса interface_info
 */

#ifndef INTERFACE_INFO_H
#define INTERFACE_INFO_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QSet>
#include "field.h"
#include "method.h"

class class_info;

/**
 * \class interface_info
 * \brief Класс для хранения полной информации о структуре интерфейса
 *
 * Обеспечивает хранение и доступ к:
 * - Основным характеристикам интерфейса (имя, модификаторы)
 * - Иерархии наследования интерфейсов
 * - Спискам полей и методов
 * - Вложенным интерфейсам и классам
 * - Списку импортов
 */
class interface_info {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор с параметрами по умолчанию
     * \param[in] nameInterface Имя интерфейса (по умолчанию "")
     * \param[in] mod Модификатор доступа (по умолчанию "default")
     * \param[in] extends Список родительских интерфейсов (по умолчанию пустой)
     * \param[in] fields Поля интерфейса (по умолчанию пустые)
     * \param[in] methods Методы интерфейса (по умолчанию пустые)
     * \param[in] includeInterface Вложенные интерфейсы (по умолчанию пустые)
     * \param[in] includeClass Вложенные классы (по умолчанию пустые)
     * \param[in] import Список импортов (по умолчанию пустой)
     */
    interface_info(const QString& nameInterface = "",
                   const QString& mod = "default",
                   const QStringList& extends = QStringList(),
                   const QMap<QString, field>& fields = QMap<QString, field>(),
                   const QSet<method>& methods = QSet<method>(),
                   const QMap<QString, interface_info>& includeInterface = QMap<QString, interface_info>(),
                   const QMap<QString, class_info>& includeClass = QMap<QString, class_info>(),
                   const QStringList& import = QStringList());
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить имя интерфейса
     * \return Имя интерфейса как QString
     */
    QString getNameInterface() const;

    /**
     * \brief Получить модификатор доступа
     * \return Модификатор доступа как QString
     */
    QString getMod() const;

    /**
     * \brief Получить список родительских интерфейсов
     * \return QStringList родительских интерфейсов
     */
    QStringList getExtends() const;

    /**
     * \brief Получить поля интерфейса
     * \return QMap полей (ключ - имя поля)
     */
    QMap<QString, field> getFields() const;

    /**
     * \brief Получить методы интерфейса
     * \return QSet методов
     */
    QSet<method> getMethods() const;

    /**
     * \brief Получить вложенные интерфейсы
     * \return QMap вложенных интерфейсов (ключ - имя интерфейса)
     */
    QMap<QString, interface_info> getIncludeInterface() const;

    /**
     * \brief Получить вложенные классы
     * \return QMap вложенных классов (ключ - имя класса)
     */
    QMap<QString, class_info> getIncludeClass() const;

    /**
     * \brief Получить список импортов
     * \return QStringList импортов
     */
    QStringList getImport() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить имя интерфейса
     * \param[in] name Новое имя интерфейса
     */
    void setNameInterface(const QString& name);

    /**
     * \brief Установить модификатор доступа
     * \param[in] mod Новый модификатор доступа
     */
    void setMod(const QString& mod);

    /**
     * \brief Установить список родительских интерфейсов
     * \param[in] extends Новый список родительских интерфейсов
     */
    void setExtends(const QStringList& extends);

    /**
     * \brief Установить поля интерфейса
     * \param[in] fields Новый QMap полей
     */
    void setFields(const QMap<QString, field>& fields);

    /**
     * \brief Установить методы интерфейса
     * \param[in] methods Новый QSet методов
     */
    void setMethods(const QSet<method>& methods);

    /**
     * \brief Установить вложенные интерфейсы
     * \param[in] includeInterface Новый QMap вложенных интерфейсов
     */
    void setIncludeInterface(const QMap<QString, interface_info>& includeInterface);

    /**
     * \brief Установить вложенные классы
     * \param[in] includeClass Новый QMap вложенных классов
     */
    void setIncludeClass(const QMap<QString, class_info>& includeClass);

    /**
     * \brief Установить список импортов
     * \param[in] import Новый список импортов
     */
    void setImport(const QStringList& import);
    /// @}

    /// \name Методы добавления
    /// @{
    /**
     * \brief Добавить родительский интерфейс
     * \param[in] newExtend Имя нового родительского интерфейса
     */
    void addExtend(const QString newExtend);
    /// @}

    /// \name Операторы сравнения
    /// @{
    /**
     * \brief Оператор сравнения
     * \param[in] other Сравниваемый интерфейс
     * \return true если интерфейсы идентичны по всем полям
     */
    bool operator==(const interface_info& other) const;

    /**
     * \brief Оператор неравенства
     * \param[in] other Сравниваемый интерфейс
     * \return true если есть различия в полях
     */
    bool operator!=(const interface_info& other) const;
    /// @}

private:
    QString nameInterface;      ///< Имя интерфейса
    QString mod;               ///< Модификатор доступа  (Public/Protected/Private/default)
    QStringList extends;       ///< Список родительских интерфейсов
    QMap<QString, field> fields; ///< Поля интерфейса
    QSet<method> methods;      ///< Методы интерфейса
    QMap<QString, interface_info> includeInterface; ///< Вложенные интерфейсы
    QMap<QString, class_info> includeClass; ///< Вложенные классы
    QStringList import;        ///< Список импортов
};

#endif // INTERFACE_INFO_H
