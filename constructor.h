/*!
 * \file constructor.h
 * \brief Заголовочный файл класса constructor
 *
 * Содержит объявление класса для хранения информации о конструкторе
 *\file constructor.cpp
 *\brief Реализация методов класса constructor
 */

#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include <QString>
#include <QStringList>
#include <QVector>
#include "argument.h"

/**
 * \class constructor
 * \brief Класс для хранения данных о конструкторе
 *
 * Обеспечивает хранение и доступ к:
 * - Модификаторам доступа
 * - Имя файлу с кодом, где будет находится код конструктора
 * - Код конструктора
 * - Списку аргументов
 */
class constructor {
public:
    /// \name Конструкторы
    /// @{
    /**
     * \brief Конструктор по умолчанию
     * \details Создает пустой объект с:
     *  - Пустыми значениями mod и filename
     *  - Пустыми списком code и пустым вектором arguments
     */
    constructor();

    /**
     * \brief Конструктор с параметрами
     * \param[in] mod Модификатор доступа (Public/Protected/Private/default)
     * \param[in] filename Имя файла с кодом конструктора
     * \param[in] code Строки кода тела конструктора
     * \param[in] arguments Вектор аргументов конструктора
     */
    constructor(const QString& mod,
                const QString& filename,
                const QStringList& code,
                const QVector<argument>& arguments);
    /// @}

    /// \name Геттеры
    /// @{
    /**
     * \brief Получить модификатор доступа
     * \return Модификатор как QString (Public/Protected/Private/default)
     */
    QString getMod() const;

    /**
     * \brief Получить имя файла
     * \return Имя файла как QString
     */
    QString getFilename() const;

    /**
     * \brief Получить код конструктора
     * \return QStringList строк кода
     */
    QStringList getCode() const;

    /**
     * \brief Получить аргументы конструктора
     * \return QVector<argument> аргументов
     */
    QVector<argument> getArguments() const;
    /// @}

    /// \name Сеттеры
    /// @{
    /**
     * \brief Установить модификатор доступа
     * \param[in] mod Новый модификатор (Public/Protected/Private/default)
     */
    void setMod(const QString& mod);

    /**
     * \brief Установить имя файла
     * \param[in] filename Новое имя файла
     */
    void setFilename(const QString& filename);

    /**
     * \brief Установить код конструктора
     * \param[in] code Новый список строк кода
     */
    void setCode(const QStringList& code);

    /**
     * \brief Установить аргументы конструктора
     * \param[in] arguments Новый список аргументов
     */
    void setArguments(const QVector<argument>& arguments);
    /// @}

    /// \name Перегрузка операторов
    /// @{
    /**
     * \brief Оператор сравнения
     * \param[in] other Сравниваемый объект
     * \return true если все поля идентичны
     */
    bool operator==(const constructor& other) const;

    /**
     * \brief Оператор неравенства
     * \param[in] other Сравниваемый объект constructor
     * \return true если есть различия в полях
     */
    bool operator!=(const constructor& other) const;
    /// @}

private:
    QString mod;            ///< Модификатор доступа
    QString filename;       ///< Исходный файл
    QStringList code;       ///< Тело конструктора (строки кода)
    QVector<argument> arguments; ///< Список параметров
};

/**
 * \brief Хеш-функция для класса constructor
 * \param[in] key Объект для хеширования
 * \param[in] seed Начальное значение хеша
 * \return Уникальный хеш-код
 */
inline uint qHash(const constructor& key, uint seed = 0) noexcept
{
    uint hash = qHash(key.getMod(), seed);
    hash ^= qHash(key.getFilename(), seed + 1);
    hash ^= qHash(key.getCode(), seed + 2);
    hash ^= qHash(key.getArguments(), seed + 3);
    return hash;
}

#endif // CONSTRUCTOR_H
