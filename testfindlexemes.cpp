#include "testfindlexemes.h"
#include "main.h"


void testFindLexemes::add_data(){
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("indexCurrentString");
    QTest::addColumn<int>("indexCurrentSimbol");
    QTest::addColumn<QStringList>("neededLexemes");
    QTest::addColumn<QStringList>("needSimbols");
    QTest::addColumn<QStringList>("endLexems");
    QTest::addColumn<QPair<QString, QStringList>>("expectedResult");
    QTest::addColumn<int>("expectedIndexString");
    QTest::addColumn<int>("expectedIndexSimbol");
    // Тест 1: Базовый тест
    QTest::newRow("base")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10;

    // Тест 2: Нет нужных лексем
    QTest::newRow("no_needed_lexemes")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList()
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10;

    // Тест 3: Нет нужных символов
    QTest::newRow("no_needed_symbols")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList()
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {";"}})
        << 0 << 10;

    // Тест 4: Нет завершающих лексем
    QTest::newRow("no_end_lexemes")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList()
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"String"}, {"s"}, {"="}})
        << 2 << 0;

    // Тест 5: В коде нет нужных лексем
    QTest::newRow("no_matching_lexemes")
        << QStringList({"x = 5;", "s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"x"}, {"="}, {";"}})
        << 0 << 6;

    // Тест 6: Несколько нужных символов
    QTest::newRow("multiple_need_symbols")
        << QStringList({"int x = 5+7-3;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"=", "+", "-"})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"+"}, {"-"}, {";"}})
        << 0 << 14;

    // Тест 7: Несколько завершающих лексем
    QTest::newRow("multiple_end_lexemes")
        << QStringList({"int x = 5;;", "String s = \"potato\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({":", ";", "potato", "tomato"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10;

    // Тест 8: Одинаковые лексемы в нужных и завершающих
    QTest::newRow("same_lexemes_in_both")
        << QStringList({"chips= 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String", "chips"})
        << QStringList({"="})
        << QStringList({";", "chips"})
        << StringPair("chips", {{"chips"}})
        << 0 << 5;

    // Тест 9: Нужная лексема в однострочном комментарии
    QTest::newRow("lexeme_in_line_comment")
        << QStringList({"x = 5//int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("String", {{"x"}, {"="}, {"String"}, {"s"}, {"="}, {";"}})
        << 1 << 18;

    // Тест 10: Нужная лексема в многострочном комментарии
    QTest::newRow("lexeme_in_multiline_comment")
        << QStringList({"/*int x = 5;", "zachet u = 7+0;", "menya v = 8-1;", "karmane ura = 6+1;*/", "String s = \"test\";int x ;"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("String", {{"String"}, {"s"}, {"="}, {";"}})
        << 4 << 18;

    // Тест 11: Нужная лексема в символьной константе
    QTest::newRow("lexeme_in_char")
        << QStringList({"char x = 'k';", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"k", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"char"}, {"x"}, {"="}, {";"}})
        << 0 << 13;

    // Тест 12: Нужная лексема в строковой константе
    QTest::newRow("lexeme_in_string")
        << QStringList({"String hello = \"bool you\";", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"bool", "les"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"String"}, {"hello"}, {"="}, {";"}})
        << 0 << 26;

    // Тест 13: Поиск с середины кода
    QTest::newRow("search_from_middle")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 1 << 3
        << QStringList({"int", "s"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("s", {{"ing"}, {"s"}, {"="}, {";"}})
        << 1 << 18;

    // Тест 14: Множественные пробелы в коде
    QTest::newRow("multiple_spaces")
        << QStringList({"     int    x    = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 21;

    // Тест 15: Лексемы через перевод строки в коде
    QTest::newRow("newlines_in_code")
        << QStringList({"int", "x", "=", "5", ";", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 4 << 1;

    // Тест 16: Несколько нужных лексем в коде
    QTest::newRow("multiple_matching_lexemes")
        << QStringList({"int xel = last;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "xel", "last"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"xel"}, {"="}, {"last"}, {";"}})
        << 0 << 15;

    // Тест 17: Нужная лексема является символом
    QTest::newRow("lexeme_is_symbol")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"=", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("=", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10;

    // Тест 18: Завершающая лексема является словом
    QTest::newRow("end_lexeme_is_word")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({"String"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"String"}})
        << 1 << 6;

    // Тест 19: Лексемы с нижним подчеркиванием
    QTest::newRow("underscore_lexemes")
        << QStringList({"int_eger x_x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int_eger", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int_eger", {{"int_eger"}, {"x_x"}, {"="}, {";"}})
        << 0 << 17;

    // Тест 20: Лексемы с цифрами
    QTest::newRow("lexemes_with_digits")
        << QStringList({"int x34 = 5, b32fd53;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x34"}, {"="}, {"b32fd53"}, {";"}})
        << 0 << 21;
}

void testFindLexemes::add(){
    QFETCH(QStringList, code);
    QFETCH(int, indexCurrentString);
    QFETCH(int, indexCurrentSimbol);
    QFETCH(QStringList, neededLexemes);
    QFETCH(QStringList, needSimbols);
    QFETCH(QStringList, endLexems);
    QFETCH(StringPair, expectedResult);
    QFETCH(int, expectedIndexString);
    QFETCH(int, expectedIndexSimbol);

    int actualIndexString = indexCurrentString;
    int actualIndexSimbol = indexCurrentSimbol;

    StringPair actualResult = findLexemes(code,actualIndexString,actualIndexSimbol,
neededLexemes, needSimbols, endLexems);

    // Проверка результатов
    QCOMPARE(actualResult.first, expectedResult.first);
    if (actualResult.second.size() != expectedResult.second.size()) {
        QVERIFY2(false, qPrintable(QString("\nРазное количество лексем: ожидалось (%1) {%2}, получено (%3) {%4}")
        .arg(expectedResult.second.size()).arg(expectedResult.second.join(" "))
        .arg(actualResult.second.size()).arg(actualResult.second.join(" "))));
    } else {
        for (int i = 0; i < actualResult.second.size(); ++i) {
            if (actualResult.second[i] != expectedResult.second[i]) {
                QVERIFY2(false, qPrintable(QString("\nНесовпадение лексемы на позиции %1:\tОжидалось: \"%2\"\tПолучено: \"%3\"")
                .arg(i).arg(expectedResult.second[i]).arg(actualResult.second[i])));
            }
        }
    }
    QCOMPARE(actualIndexString, expectedIndexString);
    QCOMPARE(actualIndexSimbol, expectedIndexSimbol);
}
