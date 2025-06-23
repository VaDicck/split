/*!
 * \file testsplitmethod.h
 * \brief Заголовочный файл класса testsplitmethod
 * \file testsplitmethod.cpp
 * \brief Реализация тестов для testsplitmethod
 */

#ifndef TESTSPLITMETHOD_H
#define TESTSPLITMETHOD_H

#include <QObject>
#include <QTest>
#include <QSet>
#include "method.h"
#include "main.h"
#include "error.h"

/*!
 * \class testsplitmethod
 * \ingroup TestClasses
 * \brief Класс для тестирования разбора методов
 */
class testsplitmethod : public testSplitBase
{
    Q_OBJECT
private slots:
    /*!
     * \brief Подготавливает тестовые данные для проверки разбора методов
     */
    void test_method_data();

    /*!
     * \brief Тестирует функцию splitMethod
     */
    void test_method();
};

#endif // TESTSPLITMETHOD_H
