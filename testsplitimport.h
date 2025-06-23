/*!
 * \file testsplitimport.h
 * \brief Заголовочный файл класса testsplitimport
 * \file testsplitimport.cpp
 * \brief Реализация тестов для функции splitImport
 */

#ifndef TESTSPLITIMPORT_H
#define TESTSPLITIMPORT_H

#include <QObject>
#include <QTest>
#include <main.h>

/*!
 * \class testsplitimport
 * \ingroup TestClasses
 * \brief Класс для тестирования разбиения(сборки) import-выражений
 */
class testsplitimport : public QObject
{
    Q_OBJECT
private slots:
    /*!
     * \brief Подготавливает тестовые данные для проверки разбора import
     */
    void test_split_import_data();

    /*!
     * \brief Тестирует функцию splitImport
     */
    void test_split_import();
};

#endif // TESTSPLITIMPORT_H
