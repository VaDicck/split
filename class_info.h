/*!
 * \file class_info.h
 * \brief Заголовочный файл класса class_info
 *
 * Содержит объявление класса для хранения информации о классе:
 * - Модификаторы, наследование, интерфейсы
 * - Конструкторы, поля, методы
 * - Вложенные классы и зависимости
 */

#ifndef CLASS_INFO_H
#define CLASS_INFO_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QSet>
#include "constructor.h"
#include "field.h"
#include "method.h"

class interface_info;

/**
 * \class class_info
 * \brief Класс для хранения полной информации о структуре класса
 *
 * Обеспечивает хранение и доступ к:
 * - Основным характеристикам класса (имя, модификаторы)
 * - Иерархии наследования
 * - Спискам конструкторов, полей и методов
 * - Зависимостям от других классов и интерфейсов
 */
class class_info {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает пустой объект с:
     *  Пустыми значениями и ложными статичными и абстрактными флагами
     */
    class_info();

    /**
     * \brief Конструктор с параметрами
     * \param[in] nameClass Имя класса
     * \param[in] mod Модификатор доступа (Public/Protected/Private/default)
     * \param[in] extend Имя родительского класса
     * \param[in] implements Список реализуемых интерфейсов
     * \param[in] constructors Множество конструкторов
     * \param[in] fields Поля класса (ключ - имя поля)
     * \param[in] methods Методы класса
     * \param[in] includesClasses Вложенные классы (ключ - имя класса)
     * \param[in] includeInterface Реализуемые интерфейсы (ключ - имя интерфейса)
     * \param[in] import Список импортов
     * \param[in] isAbstract Флаг абстрактности
     * \param[in] isStatic Флаг статичности
     */
    class_info(const QString& nameClass,
               const QString& mod,
               const QString& extend,
               const QStringList& implements,
               const QSet<constructor>& constructors,
               const QMap<QString, field>& fields,
               const QSet<method>& methods,
               const QMap<QString, class_info>& includesClasses,
               const QMap<QString, interface_info>& includeInterface,
               const QStringList& import,
               bool isAbstract,
               bool isStatic);
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить имя класса
     * \return Имя класса как QString
     */
    QString getNameClass() const;

    /**
     * \brief Получить модификатор доступа
     * \return Модификатор (Public/Protected/Private/default)
     */
    QString getMod() const;

    /**
     * \brief Получить родительский класс
     * \return Имя родительского класса
     */
    QString getExtend() const;

    /**
     * \brief Получить список интерфейсов
     * \return QStringList реализуемых интерфейсов
     */
    QStringList getImplements() const;

    /**
     * \brief Получить конструкторы класса
     * \return QSet конструкторов
     */
    QSet<constructor> getConstructors() const;

    /**
     * \brief Получить поля класса
     * \return QMap полей (ключ - имя поля)
     */
    QMap<QString, field> getFields() const;

    /**
     * \brief Получить методы класса
     * \return QSet методов
     */
    QSet<method> getMethods() const;

    /**
     * \brief Получить вложенные классы
     * \return QMap вложенных классов (ключ - имя класса)
     */
    QMap<QString, class_info> getIncludesClasses() const;

    /**
     * \brief Получить вложенные интерфейсы
     * \return QMap интерфейсов (ключ - имя интерфейса)
     */
    QMap<QString, interface_info> getIncludeInterface() const;

    /**
     * \brief Получить список импортов
     * \return QStringList Список импортируемых пакетов
     */
    QStringList getImport() const;

    /**
     * \brief Проверить абстрактность класса
     * \return true если класс абстрактный
     */
    bool getIsAbstract() const;

    /**
     * \brief Проверить статичность класса
     * \return true если класс статический
     */
    bool getIsStatic() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить имя класса
     * \param[in] name Новое имя класса
     */
    void setNameClass(const QString& name);

    /**
     * \brief Установить модификатор доступа
     * \param[in] mod Новый модификатор (Public/Protected/Private/default)
     */
    void setMod(const QString& mod);

    /**
     * \brief Установить родительский класс
     * \param[in] extend Имя родительского класса
     */
    void setExtend(const QString& extend);

    /**
     * \brief Установить список интерфейсов
     * \param[in] implements Список реализуемых интерфейсов
     */
    void setImplements(const QStringList& implements);

    /**
     * \brief Установить конструкторы класса
     * \param[in] constructors QSet конструкторов
     */
    void setConstructors(const QSet<constructor>& constructors);

    /**
     * \brief Установить поля класса
     * \param[in] fields QMap полей (ключ - имя поля)
     */
    void setFields(const QMap<QString, field>& fields);

    /**
     * \brief Установить методы класса
     * \param[in] methods QSet методов
     */
    void setMethods(const QSet<method>& methods);

    /**
     * \brief Установить вложенные классы
     * \param[in] includesClasses QMap вложенных классов (ключ - имя класса)
     */
    void setIncludesClasses(const QMap<QString, class_info>& includesClasses);

    /**
     * \brief Установить вложенные интерфейсы
     * \param[in] includeInterface QMap вложенных интерфейсов (ключ - имя интерфейса)
     */
    void setIncludeInterface(const QMap<QString, interface_info>& includeInterface);

    /**
     * \brief Установить список импортов
     * \param[in] import Список импортируемых пакетов
     */
    void setImport(const QStringList& import);

    /**
     * \brief Установить флаг абстрактности
     * \param[in] isAbstract true для абстрактного класса
     */
    void setIsAbstract(bool isAbstract);

    /**
     * \brief Установить флаг статичности
     * \param[in] isStatic true для статического класса
     */
    void setIsStatic(bool isStatic);
    /// @}

    /**
     * \brief Оператор сравнения классов
     * \details Сравнивает все поля классов
     * \param[in] other Сравниваемый класс
     * \return true если классы идентичны по всем полям
     */
    bool operator==(const class_info& other) const;

private:
    QString nameClass;      ///< Имя класса
    QString mod;           ///< Модификатор доступа (Public/Protected/Private/default)
    QString extend;        ///< Родительский класс
    QStringList implements; ///< Список реализуемых интерфейсов
    QSet<constructor> constructors; ///< Конструкторы класса
    QMap<QString, field> fields;   ///< Поля класса (ключ - имя поля)
    QSet<method> methods;          ///< Методы класса
    QMap<QString, class_info> includesClasses; ///< Вложенные классы (ключ - имя класса)
    QMap<QString, interface_info> includeInterface; ///< Используемые интерфейсы (ключ - имя интерфейса)
    QStringList import;    ///< Список импортов (include/using)
    bool isAbstract;       ///< Флаг абстрактного класса
    bool isStatic;         ///< Флаг статического класса
};

#endif // CLASS_INFO_H
