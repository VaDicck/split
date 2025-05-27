#include "testskipconstant.h"
#include "main.h"

void testSkipConstant::add_data(){
    QTest::addColumn<QString>("str");
    QTest::addColumn<int>("indexStart");
    QTest::addColumn<char>("simbol");
    QTest::addColumn<bool>("exResult");
    QTest::addColumn<int>("exIndex");

    QTest::newRow("symbolConstat")
        << QString("char brac = '{' ;") << 13 << '\'' << true << 15;

    QTest::newRow("symbolConstantaShielding")
        << QString("char brac = '\\'' ;") << 13 << '\'' << true << 16;

    QTest::newRow("symbolConstantaShieldingOfShielding")
        << QString("char brac = '\\\\' ;") << 13 << '\'' << true << 16;

    QTest::newRow("stringConstant")
        << QString("String a= \"Hi, tun\";") << 11 << '"' << true << 19;

    QTest::newRow("stringConstantTwoShields")
        << QString("String a= \"Hi\\\"t\\\"\";") << 11 << '"' << true << 19;

    QTest::newRow("stringConstantShieldingOfShielding")
        << QString("String a= \"Hi, \\\\\";") << 11 << '"' << true << 18;

    QTest::newRow("notCompletedSymbolConstant")
        << QString("char brac = 'a ;") << 13 << '\'' << false << 13;

    QTest::newRow("notCompletedStringConstant")
        << QString("String a= \"Hi, tun ;") << 11 << '"' << false << 11;

    QTest::newRow("multipleShielding")
        << QString("String a= \"\\\\\\\\\\\" ;") << 11 << '"' << false << 11;

    QTest::newRow("symbolConstantIncludesStringConstant")
        << QString("String a= \"Hi, 'u'\";") << 11 << '"' << true << 19;

    QTest::newRow("stringConstantIncludesSimbolConstant")
        << QString("char brac = '\"' ;") << 13 << '\'' << true << 15;
}

void testSkipConstant::add(){
    QFETCH(QString, str);
    QFETCH(int, indexStart);
    QFETCH(char, simbol);
    QFETCH(bool, exResult);
    QFETCH(int, exIndex);

    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}

