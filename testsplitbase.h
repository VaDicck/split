/*!
 * \file testsplitbase.h
 * \brief Заголовочный файл для класса testsplitbase
 * \file testsplitbase.cpp
 * \brief Реализация методов класса testsplitbase
 */
#ifndef TESTSPLITBASE_H
#define TESTSPLITBASE_H

#include <QObject>
#include "error.h"
#include "argument.h"
#include "field.h"
#include "class_info.h"
#include "interface_info.h"
#include "method.h"
#include "package_info.h"

/*!
 * \class testSplitBase
 * \ingroup TestClasses
 * \brief Базовый класс для тестирования разбиения Java-кода
 * Класс содержит вспомогательные методы для сравнения структур данных,
 * полученных в результате разбора Java-кода, с ожидаемыми значениями.
 */
class testSplitBase : public QObject
{
    Q_OBJECT
protected:
    /*!
     * \brief Сравнивает две карты полей
     * \param[in] actual - фактическая карта полей
     * \param[in] expected - ожидаемая карта полей
     * \return Сообщение о различиях или пустую строку, если карты идентичны
     */
    QString verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected);

    /*!
     * \brief Сравнивает два набора ошибок. Печатает сразу на экран
     * \param[in] actual - фактический набор ошибок
     * \param[in] expected - ожидаемый набор ошибок
     */
    void verifyErrors(const QSet<error>& actual, const QSet<error>& expected);

    /*!
     * \brief Сравнивает два конструктора
     * \param[in] actual - фактический конструктор
     * \param[in] expected - ожидаемый конструктор
     * \return Сообщение о различиях или пустую строку, если конструкторы идентичны
     */
    QString verifyConstructor(const constructor& actual,const constructor& expected);

    /*!
     * \brief Сравнивает два метода
     * \param[in] actual - фактический метод
     * \param[in] expected - ожидаемый метод
     * \return Сообщение о различиях или пустую строку, если методы идентичны
     */
    QString verifyMethod(const method& actual,const method& expected);

    /*!
     * \brief Сравнивает два класса
     * \param[in] actual - фактический класс
     * \param[in] expected - ожидаемый класс
     * \return Сообщение о различиях или пустую строку, если классы идентичны
     */
    QString verifyClass(const class_info& actual,const class_info& expected);

    /*!
     * \brief Сравнивает два интерфейса
     * \param[in] actual - фактический интерфейс
     * \param[in] expected - ожидаемый интерфейс
     * \return Сообщение о различиях или пустую строку, если интерфейсы идентичны
     */
    QString verifyInterface(const interface_info& actual,const interface_info& expected);

    /*!
     * \brief Сравнивает два пакета
     * \param[in] actual - фактический пакет
     * \param[in] expected - ожидаемый пакет
     * \param[in] pathPack - путь к пакету (для информационных сообщений)
     * \return Сообщение о различиях или пустую строку, если пакеты идентичны
     */
    QString verifyPack(const package_info& actual,const package_info& expected, QString pathPack);
};

#endif // TESTSPLITBASE_H
