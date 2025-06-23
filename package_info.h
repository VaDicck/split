/*!
 * \file package_info.h
 * \brief Заголовочный файл класса package_info
 *
 * Содержит объявление класса для хранения информации о пакете:
 * - Иерархия вложенных пакетов
 * - Классы и интерфейсы в пакете
 * - Методы работы с элементами пакета
 *\file package_info.cpp
 *\brief Реализация методов класса package_info
 */

#ifndef PACKAGE_INFO_H
#define PACKAGE_INFO_H

#include <QString>
#include <QMap>
#include "class_info.h"
#include "interface_info.h"

/**
 * \class package_info
 * \brief Класс для хранения информации о пакете и его содержимом
 *
 * Обеспечивает хранение и доступ к:
 * - Иерархии вложенных пакетов
 * - Классам и интерфейсам, содержащимся в пакете
 * - Методам управления структурой пакета и сравнения структуры
 */
class package_info {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает пустой объект с:
     *  - Пустым именем пакета
     *  - Пустыми контейнерами для дочерних элементов
     */
    package_info();

    /**
     * \brief Конструктор с параметрами
     * \param[in] namePackage Имя пакета
     * \param[in] children Вложенные пакеты (по умолчанию пустые)
     * \param[in] includesClasses Классы в пакете (по умолчанию пустые)
     * \param[in] includesInterfaces Интерфейсы в пакете (по умолчанию пустые)
     */
    package_info(const QString& namePackage,
                 const QMap<QString, package_info>& children = QMap<QString, package_info>(),
                 const QMap<QString, class_info>& includesClasses = QMap<QString, class_info>(),
                 const QMap<QString, interface_info>& includesInterfaces = QMap<QString, interface_info>());
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить имя пакета
     * \return Имя пакета как QString
     */
    QString getNamePackage() const;

    /**
     * \brief Получить вложенные пакеты (неконстантная версия)
     * \return Ссылка на QMap дочерних пакетов
     */
    QMap<QString, package_info>& getChildren();

    /**
     * \brief Получить классы в пакете (неконстантная версия)
     * \return Ссылка на QMap классов
     */
    QMap<QString, class_info>& getIncludesClasses();

    /**
     * \brief Получить интерфейсы в пакете (неконстантная версия)
     * \return Ссылка на QMap интерфейсов
     */
    QMap<QString, interface_info>& getIncludesInterfaces();

    /**
     * \brief Получить классы в пакете (константная версия)
     * \return Константная ссылка на QMap классов
     */
    const QMap<QString, class_info>& getIncludesClasses() const;

    /**
     * \brief Получить интерфейсы в пакете (константная версия)
     * \return Константная ссылка на QMap интерфейсов
     */
    const QMap<QString, interface_info>& getIncludesInterfaces() const;

    /**
     * \brief Получить вложенные пакеты (константная версия)
     * \return Константная ссылка на QMap вложенных пакетов
     */
    const QMap<QString, package_info>& getChildren() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить имя пакета
     * \param[in] name Новое имя пакета
     */
    void setNamePackage(const QString& name);

    /**
     * \brief Установить дочерние пакеты
     * \param[in] children Новый QMap вложенных пакетов
     */
    void setChildren(const QMap<QString, package_info>& children);

    /**
     * \brief Установить классы в пакете
     * \param[in] includesClasses Новый QMap классов
     */
    void setIncludesClasses(const QMap<QString, class_info>& includesClasses);

    /**
     * \brief Установить интерфейсы в пакете
     * \param[in] includesInterfaces Новый QMap интерфейсов
     */
    void setIncludesInterfaces(const QMap<QString, interface_info>& includesInterfaces);
    /// @}

    /// \name Методы добавления элементов
    /// @{
    /**
     * \brief Добавить вложенный пакет
     * \param[in] name Имя дочернего пакета
     * \param[in] pkg Объект package_info для добавления
     */
    void addChildPackage(const QString& name, const package_info& pkg);

    /**
     * \brief Добавить класс в пакет
     * \param[in] Class Объект class_info для добавления
     */
    void addMapClass(const class_info &Class);

    /**
     * \brief Добавить интерфейс в пакет
     * \param[in] Interface Объект interface_info для добавления
     */
    void addMapInterface(const interface_info &Interface);
    /// @}

    /// \name Операторы и методы сравнения
    /// @{
    /**
     * \brief Оператор сравнения пакетов
     * \param[in] other Сравниваемый пакет
     * \return true если пакеты идентичны по всем полям
     */
    bool operator==(const package_info& other) const;

    /**
     * \brief Сравнить пути пакетов(рекурсивно)
     * \param[in] other Пакет для сравнения
     * \param[in] parentPath Родительский путь (по умолчанию "")
     * \return Различия в пути как QString
     */
    QString compare(const package_info& other, const QString& parentPath = "") const;
    /// @}

private:
    QString namePackage;                       ///< Имя пакета
    QMap<QString, package_info> children;      ///< Вложенные пакеты
    QMap<QString, class_info> includesClasses; ///< Классы в пакете
    QMap<QString, interface_info> includesInterfaces; ///< Интерфейсы в пакете
};

#endif // PACKAGE_INFO_H
