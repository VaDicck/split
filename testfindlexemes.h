/*!
 *\file testFindLexemes.h
 *\brief Заголовочный файл для класса testFindLexemes
 *\file testFindLexemes.cpp
 *\brief Реализация тестов для поиска лексем
*/

#ifndef TESTFINDLEXEMES_H
#define TESTFINDLEXEMES_H

#include <QObject>
#include <QTest>
#include "testSplitBase.h"

typedef QPair<QString, QStringList> StringPair;
Q_DECLARE_METATYPE(StringPair)

/*!
 * \class testFindLexemes
 * \ingroup TestClasses
 * \brief Тестовый класс для проверки поиска лексем в коде
 *
 * Этот класс предоставляет набор тестов для проверки корректности используя базовый класс testSplitBase:
 * - Поиска и выделения лексем в исходном коде
 * - Обработки нужных лексем и завершающих
 * - Работы с позицией поиска в многострочном коде
 * - Обработки комментариев и строковых констант
 * - Нахождении ошибок
 */
class testFindLexemes : public testSplitBase{
    Q_OBJECT // Обязательный макрос
private slots:
    /*!
     * \brief test_find_lexemes_data - подготовка тестовых данных
     * Заполняет таблицу тестовых данных различными вариантами:
     * - Простые и сложные выражения
     * - Код с разными типами лексем (ключевые слова, идентификаторы)
     * - Специальные символы и операторы
     * - Комментарии и строковые константы
     * - Граничные случаи (пустые строки, пробелы)
     */
    void test_find_lexemes_data();

    /*!
     * \brief test_find_lexemes - выполнение тестов поиска лексем
     * Проверяет корректность работы алгоритма поиска:
     * - Полноту найденных лексем
     * - Правильность их порядка и состава
     * - Корректность обработки позиции поиска
     */
    void test_find_lexemes();
};

#endif // TESTFINDLEXEMES_H
