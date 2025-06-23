/*!
 * \file testsplitproject.h
 * \brief Заголовочный файл класса testsplitproject
 * \file testsplitproject.cpp
 * \brief Реализация тестов для splitProject
 */

#ifndef TESTSPLITPROJECT_H
#define TESTSPLITPROJECT_H

#include <QObject>
#include <QTest>
#include <main.h>
#include <package_info.h>
#include "method.h"
#include "class_info.h"
#include "interface_info.h"

/*!
 * \class testsplitproject
 * \ingroup TestClasses
 * \brief Класс для тестирования разбора проектов
 *
 * Класс содержит тесты для проверки корректности работы функции splitProject,
 * которая обрабатывает весь проект, включая пакеты, классы и интерфейсы
 */
class testsplitproject : public testSplitBase
{
    Q_OBJECT
private slots:
    /*!
     * \brief Подготавливает тестовые данные для проверки разбора проектов
     */
    void test_pack_data();

    /*!
     * \brief Тестирует функцию splitProject
     */
    void test_pack();
};
#endif // TESTSPLITPROJECT_H
