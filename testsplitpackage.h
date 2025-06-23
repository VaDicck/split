/*!
 * \file testsplitpackage.h
 * \brief Заголовочный файл класса testsplitpackage
 * \file testsplitpackage.cpp
 * \brief Реализация тестов для splitpackage
 */

#ifndef TESTSPLITPACKAGE_H
#define TESTSPLITPACKAGE_H

#include <QObject>
#include <QTest>
#include "package_info.h"
#include <main.h>

/*!
 * \class testsplitpackage
 * \ingroup TestClasses
 * \brief Класс для тестирования разбора package-деклараций
 *
 * Класс содержит тесты для проверки корректности работы функции splitPackage,
 * которая обрабатывает декларации пакетов и строит соответствующую структуру
 */
class testsplitpackage : public QObject
{
    Q_OBJECT
public:
    explicit testsplitpackage(QObject *parent = nullptr);
private slots:
    /*!
     * \brief Тест1 пустого корневого пакета
     */
    void empty_root_package();

    /*!
     * \brief Тест2 отсутствия пакета среди детей корневого
     */
    void no_among_the_children_root();

    /*!
     * \brief Тест3 существующего пакета
     */
    void such_a_package_exists();

    /*!
     * \brief Тест4 большой вложенности пакета
     */
    void large_package_nesting();

    /*!
     * \brief Тест5 существующего пакета с большой вложенностью
     */
    void existing_package_heavily_nested();

    /*!
     * \brief Тест6 ссылки не на последний компонент пакета
     */
    void link_not_last_component_package();

    /*!
     * \brief Тест7 вставки в середину структуры пакетов
     */
    void insert_in_middle();
};
#endif // TESTSPLITPACKAGE_H
