/*!
 * \file argument.h
 * \brief Заголовочный файл для класса argument
 *\file argument.cpp
 *\brief Реализация методов класса argument
 */
#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QString>
#include <QHash>

/**
 * \class argument
 * \brief Класс для представления аргумента с его именем и типом
 *
 * Класс предоставляет данные и методы для работы с аргументами, включая их хранение,
 * сравнение и использование в хеш-структурах данных.
 */
class argument
{
private:
    QString nameArgument;  ///< Имя аргумента
    QString type;         ///< Тип аргумента

public:
    /**
     * \brief Получить имя аргумента
     * \return Константная строка с именем аргумента
     */
    QString getName() const;

    /**
     * \brief Получить тип аргумента
     * \return Константная строка с типом аргумента
     */
    QString getType() const;

    /**
     * \brief Установить имя аргумента
     * \param[in] name Новое имя аргумента
     */
    void setName(const QString& name);

    /**
     * \brief Установить тип аргумента
     * \param[in] type Новый тип аргумента
     */
    void setType(const QString& type);

    /**
     * \brief Конструктор по умолчанию
     * \details Создает аргумент с пустыми именем и типом
     */
    argument();

    /**
     * \brief Параметризованный конструктор
     * \details Создает аргумент с пустыми именем и типом
     * \param[in] name Имя аргумента
     * \param[in] type Тип аргумента
     */
    argument(const QString& name, const QString& type);

    /**
     * \brief Оператор сравнения аргументов
     * \param[in] other Аргумент для сравнения
     * \return true если аргументы идентичны, иначе false
     */
    bool operator==(const argument& other) const;
};

/**
 * \brief Хеш-функция для класса argument, необходимая для использования argument в QSet
 * \param[in] arg Аргумент для хеширования
 * \param[in] seed Начальное значение хеша
 * \return Хеш-значение аргумента
 */
inline uint qHash(const argument &arg, uint seed = 0) {
    return qHash(arg.getName(), seed) ^ qHash(arg.getType());
}

/**
 * \brief Хеш-функция для вектора аргументов, необходимая для использования QVector<argument> в QSet
 * \param[in] vec Вектор аргументов для хеширования
 * \param[in] seed Начальное значение хеша
 * \return Хеш-значение вектора аргументов
 */
inline uint qHash(const QVector<argument> &vec, uint seed = 0) {
    uint hash = seed;
    for (const argument &arg : vec) {
        hash ^= qHash(arg, seed);
    }
    return hash;
}

#endif // ARGUMENT_H
