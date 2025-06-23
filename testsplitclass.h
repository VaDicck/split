/*!
 * \file testsplitclass.h
 * \brief Заголовочный файл для класса testsplitclass
 * \file testsplitclass.cpp
 * \brief Реализация тестов для функции testsplitclass
 */

#ifndef TESTSPLITCLASS_H
#define TESTSPLITCLASS_H

#include <QObject>
#include <QTest>
#include "class_info.h"
#include "error.h"
#include "constructor.h"
#include "main.h"

/*!
 * \class testsplitclass
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки функции разбиения классов
 *
 * Этот класс предоставляет набор тестов для проверки корректности работы функции splitClass,
 * которая анализирует определение класса в исходном коде и извлекает информацию о его структуре.
 */
class testsplitclass : public testSplitBase
{
    Q_OBJECT
private slots:
    /*!
     * \brief test_class_data - заполнение данными тестовых ситуаций
     * Создает таблицу тестовых данных с различными вариантами классов:
     * - Классы с разными модификаторами доступа
     * - Классы с наследованием и реализацией интерфейсов
     * - Классы с вложенными классами и интерфейсами
     * - Классы с конструкторами и методами
     * - Особые случаи (абстрактные, статические классы)
     * - Граничные условия и ошибочные ситуации
     */
    void test_class_data();

    /*!
     * \brief test_class - выполняет запуск тестовых ситуаций
     * Проверяет корректность работы функции splitClass:
     * - Извлеченную информацию о классе
     * - Конечную позицию в коде после обработки
     * - Обнаруженные ошибки
     */
    void test_class();
};

#endif // TESTSPLITCLASS_H
