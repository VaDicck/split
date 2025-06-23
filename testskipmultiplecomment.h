/*!
 * \file testskipmultiplecomment.h
 * \brief Заголовочный файл для класса testSkipMultipleComment
 * \file testskipmultiplecomment.cpp
 * \brief Реализация тестов для функции пропуска многострочных комментариев
 */

#ifndef TESTSKIPMULTIPLECOMMENT_H
#define TESTSKIPMULTIPLECOMMENT_H

#include <QObject>
#include <QTest>

/*!
 * \class testSkipMultipleComment
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки функции пропуска многострочных комментариев
 *
 * Этот класс предоставляет набор тестов для проверки корректности работы функции
 * skipMultilineComment, которая пропускает многострочные комментарии в коде.
 */
class testSkipMultipleComment : public QObject
{
    Q_OBJECT
private slots:
    /*!
     * \brief test_skip_comm_data - заполнение данными тестовых ситуаций
     * Создает таблицу тестовых данных с различными вариантами комментариев:
     * - Комментарии в одной строке
     * - Комментарии в разных строках
     * - Экранированные комментарии
     * - Незавершенные комментарии
     * - Комментарии с внутренними символами
     */
    void test_skip_comm_data();

    /*!
     * \brief test_skip_comm - выполняет запуск тестовых ситуаций
     * Проверяет корректность работы функции skipMultilineComment:
     * - Возвращаемое значение (успешность пропуска)
     * - Конечную позицию в коде после пропуска
     * - Конечный индекс строки после пропуска
     */
    void test_skip_comm();
};

#endif // TESTSKIPMULTIPLECOMMENT_H
