/*!
 * \file testsplitinterface.h
 * \brief Заголовочный файл для класса testSplitInterface
 * \file testsplitinterface.cpp
 * \brief Реализация тестов для testsplitinterface
 */

#ifndef TESTSPLITINTERFACE_H
#define TESTSPLITINTERFACE_H

#include <QObject>
#include <QTest>
#include "interface_info.h"
#include "error.h"
#include "main.h"
#include "class_info.h"

/*!
 * \class testSplitInterface
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки разбора интерфейсов
 *
 * Этот класс содержит тесты для функции splitInterface, которая анализирует:
 * - Объявления интерфейсов с различными модификаторами
 * - Наследование интерфейсов
 * - Поля и методы интерфейсов
 * - Вложенные классы и интерфейсы
 * - Особые случаи со скобками и комментариями
 */
class testsplitinterface : public testSplitBase
{
    Q_OBJECT
private slots:
    /*!
     * \brief test_split_data - подготовка тестовых данных
     *
     * Создает тестовые случаи для различных вариантов интерфейсов:
     * - Базовые объявления интерфейсов
     * - Интерфейсы с разными модификаторами доступа
     * - Наследование интерфейсов
     * - Вложенные элементы
     * - Граничные случаи со скобками и комментариями
     */
    void test_split_data();

    /*!
     * \brief test_split - выполнение тестов
     * Проверяет корректность разбора интерфейсов, включая
     */
    void test_split();
};

#endif // TESTSPLITINTERFACE_H
