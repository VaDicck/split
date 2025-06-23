/*!
 *\file testSkipConstant.h
 *\brief Заголовочный файл для класса testSkipConstant
 *\file testSkipConstant.cpp
 *\brief Реализация тестов для пропуска констант
*/

#ifndef TESTSKIPCONSTANT_H
#define TESTSKIPCONSTANT_H

#include <QObject>
#include <QTest>

/*!
 * \class testSkipConstant
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки пропуска символьных и строковых констант
 *
 * Этот класс предоставляет набор тестов для проверки корректности:
 * - Пропуск символьных констант, которые задаются
 * - Обработки экранированных символов
 * - Определения незакрытых констант
 */
class testSkipConstant : public QObject
{
    Q_OBJECT // Обязательный макрос Qt
private slots:
    /*!
     * \brief test_skip_const_data - подготовка тестовых данных
     * Заполняет таблицу тестовых данных различными вариантами:
     * - Простые символьные и строковые константы
     * - Константы с экранированными символами
     * - Незакрытые константы
     * - Вложенные константы
     */
    void test_skip_const_data();

    /*!
     * \brief test_skip_const - выполнение тестов пропуска констант
     * Проверяет корректность работы алгоритма пропуска:
     * - Правильность определения конца константы
     */
    void test_skip_const();
};

#endif // TESTSKIPCONSTANT_H
