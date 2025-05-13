#include "testskipconstant.h"
#include "main.h"

void testSkipConstant::symbolConstat(){
    QString str = "char brac = '{' ;";
    int indexStart = 13;
    char simbol = '\'';
    bool exResult = true;
    int exIndex = 15;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::symbolConstantaShielding(){
    QString str = "char brac = '\\'' ;";
    int indexStart = 13;
    char simbol = '\'';
    bool exResult = true;
    int exIndex = 16;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::symbolConstantaShieldingOfShielding(){
    QString str = "char brac = '\\\\' ;";
    int indexStart = 13;
    char simbol = '\'';
    bool exResult = true;
    int exIndex = 16;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::stringConstant(){
    QString str = "String a= \"Hi, tun\";";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = true;
    int exIndex = 19;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::stringConstantTwoShields(){
    QString str = "String a= \"Hi\\\"t\\\"\";";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = true;
    int exIndex = 19;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::stringConstantShieldingOfShielding(){
    QString str = "String a= \"Hi, \\\\\";";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = true;
    int exIndex = 18;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::notCompletedSymbolConstant(){
    QString str = "char brac = 'a ;";
    int indexStart = 13;
    char simbol = '\'';
    bool exResult = false;
    int exIndex = 13;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::notCompletedStringConstant(){
    QString str = "String a= \"Hi, tun ;";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = false;
    int exIndex = 11;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::multipleShielding(){
    QString str = "String a= \"\\\\\\\\\\\" ;";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = false;
    int exIndex = 11;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::symbolConstantIncludesStringConstant(){
    QString str = "String a= \"Hi, 'u'\";";
    int indexStart = 11;
    char simbol = '"';
    bool exResult = true;
    int exIndex = 19;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
void testSkipConstant::stringConstantIncludesSimbolConstant(){
    QString str = "char brac = '\"' ;";
    int indexStart = 13;
    char simbol = '\'';
    bool exResult = true;
    int exIndex = 15;
    bool result = skipConstant(str, indexStart, simbol);
    QCOMPARE(result, exResult);
    QCOMPARE(indexStart, exIndex);
}
