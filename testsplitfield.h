/*!
 * \file testsplitfield.h
 * \brief Заголовочный файл для класса testSplitField
 * \file testsplitfield.cpp
 * \brief Реализация тестов для функции splitField
 */

#ifndef TESTSPLITFIELD_H
#define TESTSPLITFIELD_H
#include <QObject>
#include <QTest>
#include "field.h"
#include "testsplitbase.h"

Q_DECLARE_METATYPE(field)
typedef QMap<QString, field> fieldMap;
Q_DECLARE_METATYPE(fieldMap)

/*!
 * \class testSplitField
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки функции splitField
 *
 * Этот класс предоставляет набор тестов для проверки корректности разбора объявлений полей класса,
 * включая обработку различных модификаторов доступа, статических полей, инициализации и сложных типов.
 */
class testSplitField : public testSplitBase
{
    Q_OBJECT
private slots:
    /*!
     * \brief test_field_data - заполнение данными тестовых ситуаций
     * Создает таблицу тестовых данных с различными вариантами объявлений полей:
     * - Поля с различными модификаторами доступа (public, private, protected)
     * - Статические поля
     * - Поля с инициализацией
     * - Множественные объявления полей
     * - Поля с контейнерными типами и массивами
     */
    void test_field_data();

    /*!
     * \brief test_field - выполняет запуск тестовых ситуаций с использованием предоставленных данных.
     * Выполняет тестирование функции splitField.
     */
    void test_field();
};
#endif // TESTSPLITFIELD_H
