#include "testSkipConstant.h"
#include "main.h"

void testSkipConstant::test_skip_const_data()
{
    // колонки параметры + ожидаемый результат
    QTest::addColumn<QString>("str");         ///< Исходная строка для анализа
    QTest::addColumn<int>("indexStart");      ///< Начальный индекс поиска
    QTest::addColumn<char>("simbol");         ///< Символ начала константы (' или ")
    QTest::addColumn<bool>("exResult");       ///< Ожидаемый результат (true - константа пропущена)
    QTest::addColumn<int>("exIndex");         ///< Ожидаемый индекс после пропуска

    // Тест 1. Пропустить символьную константу без экранирования
    /*!
     * \test Тест 1: Простая символьная константа
     * Проверяет обработку обычной символьной константы
     */
    QTest::newRow("symbolConstat") << QString("char brac = '{' ;") << 13 << '\'' << true << 15;

    // Тест 2. Пропустить символьную константу с экранированием
    /*!
     * \test Тест 2: Экранированная символьная константа
     * Проверяет обработку экранированного символа в константе
     */
    QTest::newRow("symbolConstantaShielding") << QString("char brac = '\\'' ;") << 13 << '\'' << true << 16;

    // Тест 3. Пропустить символьную константу с экранированием экранирования
    /*!
     * \test Тест 3: Двойное экранирование
     * Проверяет обработку экранированного обратного слеша
     */
    QTest::newRow("symbolConstantaShieldingOfShielding") << QString("char brac = '\\\\' ;") << 13 << '\'' << true << 16;

    // Тест 4. Пропустить строковую константу без экранирования
    /*!
     * \test Тест 4: Простая строковая константа
     * Проверяет обработку обычной строковой константы
     */
    QTest::newRow("stringConstant") << QString("String a= \"Hi, tun\";") << 11 << '"' << true << 19;

    // Тест 5. Пропустить строковую константу с двумя экранированиями
    /*!
     * \test Тест 5: Экранированные кавычки в строке
     * Проверяет обработку экранированных кавычек внутри строки
     */
    QTest::newRow("stringConstantTwoShields") << QString("String a= \"Hi\\\"t\\\"\";") << 11 << '"' << true << 19;

    // Тест 6. Пропустить строковую константу с экранированием экранирования
    /*!
     * \test Тест 6: Экранированный обратный слеш
     * Проверяет обработку экранированного обратного слеша в строке
     */
    QTest::newRow("stringConstantShieldingOfShielding") << QString("String a= \"Hi, \\\\\";") << 11 << '"' << true << 18;

    // Тест 7. Не завершена символьная константа
    /*!
     * \test Тест 7: Незакрытая символьная константа
     * Проверяет обработку незавершенной символьной константы
     */
    QTest::newRow("notCompletedSymbolConstant") << QString("char brac = 'a ;") << 13 << '\'' << false << 16;

    // Тест 8. Не завершена строковая константа
    /*!
     * \test Тест 8: Незакрытая строковая константа
     * Проверяет обработку незавершенной строковой константы
     */
    QTest::newRow("notCompletedStringConstant") << QString("String a= \"Hi, tun ;") << 11 << '"' << false << 20;

    // Тест 9. Множественное экранирование
    /*!
     * \test Тест 9: Множественные экранирования
     * Проверяет обработку нескольких экранированных символов подряд
     */
    QTest::newRow("multipleShielding") << QString("String a= \"\\\\\\\\\\\\\" ;") << 11 << '"' << true << 18;

    // Тест 10. Символьная константа в строковой
    /*!
     * \test Тест 10: Вложенные константы
     * Проверяет обработку символьной константы внутри строковой
     */
    QTest::newRow("symbolConstantIncludesStringConstant") << QString("String a= \"Hi, 'u'\";") << 11 << '"' << true << 19;

    // Тест 11. Строковая константа в символьной
    /*!
     * \test Тест 11: Кавычки в символьной константе
     * Проверяет обработку кавычек внутри символьной константы
     */
    QTest::newRow("stringConstantIncludesSimbolConstant") << QString("char brac = '\"' ;") << 13 << '\'' << true << 15;
}

void testSkipConstant::test_skip_const()
{
    QFETCH(QString, str);
    QFETCH(int, indexStart);
    QFETCH(char, simbol);
    QFETCH(bool, exResult);
    QFETCH(int, exIndex);

    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
