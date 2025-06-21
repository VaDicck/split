#include "testskipconstant.h"
#include "main.h"

void testSkipConstant::test_skip_const_data(){
    QTest::addColumn<QString>("str");
    QTest::addColumn<int>("indexStart");
    QTest::addColumn<char>("simbol");
    QTest::addColumn<bool>("exResult");
    QTest::addColumn<int>("exIndex");


    // Тест 1. Пропустить символьную константу без экранирования
    QTest::newRow("symbolConstat") << QString("char brac = '{' ;") << 13 << '\'' << true << 15;

    // Тест 2. Пропустить символьную константу с экранированием
    QTest::newRow("symbolConstantaShielding") << QString("char brac = '\\'' ;") << 13 << '\'' << true << 16;

    // Тест 3. Пропустить символьную константу с экранированием экранирования
    QTest::newRow("symbolConstantaShieldingOfShielding") << QString("char brac = '\\\\' ;") << 13 << '\'' << true << 16;

    // Тест 4. Пропустить строковую константу без экранирования
    QTest::newRow("stringConstant") << QString("String a= \"Hi, tun\";") << 11 << '"' << true << 19;

    // Тест 5. Пропустить строковую константу с двумя экранированиями
    QTest::newRow("stringConstantTwoShields") << QString("String a= \"Hi\\\"t\\\"\";") << 11 << '"' << true << 19;

    // Тест 6. Пропустить строковую константу с экранированием экранирования
    QTest::newRow("stringConstantShieldingOfShielding") << QString("String a= \"Hi, \\\\\";") << 11 << '"' << true << 18;

    // Тест 7. Не завершена символьная константа
    QTest::newRow("notCompletedSymbolConstant") << QString("char brac = 'a ;") << 13 << '\'' << false << 16;

    // Тест 8. Не завершена строковая константа
    QTest::newRow("notCompletedStringConstant") << QString("String a= \"Hi, tun ;") << 11 << '"' << false << 20;

    // Тест 9. Множественное экранирование
    QTest::newRow("multipleShielding") << QString("String a= \"\\\\\\\\\\\\\" ;") << 11 << '"' << true << 18;

    // Тест 10. Символьная константа в строковой
    QTest::newRow("symbolConstantIncludesStringConstant") << QString("String a= \"Hi, 'u'\";") << 11 << '"' << true << 19;

    // Тест 11. Строковая константа в символьной
    QTest::newRow("stringConstantIncludesSimbolConstant") << QString("char brac = '\"' ;") << 13 << '\'' << true << 15;
}

void testSkipConstant::test_skip_const(){
    QFETCH(QString, str);
    QFETCH(int, indexStart);
    QFETCH(char, simbol);
    QFETCH(bool, exResult);
    QFETCH(int, exIndex);

    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}

