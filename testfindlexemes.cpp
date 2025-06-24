#include "testfindlexemes.h"
#include "main.h"

void testFindLexemes::test_find_lexemes_data()
{
    QTest::addColumn<QStringList>("code");               ///< Исходный код для анализа
    QTest::addColumn<int>("indexCurrentString");         ///< Начальный индекс строки
    QTest::addColumn<int>("indexCurrentSimbol");         ///< Начальная позиция в строке
    QTest::addColumn<QStringList>("neededLexemes");      ///< Искомые лексемы
    QTest::addColumn<QStringList>("needSimbols");        ///< Искомые символы
    QTest::addColumn<QStringList>("endLexems");          ///< Завершающие лексемы
    QTest::addColumn<StringPair>("expectedResult");      ///< Ожидаемый результат (найденная лексема и список лексем)
    QTest::addColumn<int>("expectedIndexString");        ///< Ожидаемый индекс строки после поиска
    QTest::addColumn<int>("expectedIndexSimbol");        ///< Ожидаемая позиция в строке после поиска
    QTest::addColumn<QSet<error>>("expectedErrors");     ///< Ожидаемые ошибки

    // Тест 1: Базовый тест
    /*!
     * \test Тест 1: Базовый тест
     * Проверяет базовый случай поиска лексем с простым кодом
     */
    QTest::newRow("base")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10 << QSet<error>();

    // Тест 2: Нет нужных лексем
    /*!
     * \test Тест 2: Отсутствие искомых лексем
     * Проверяет поведение при пустом списке искомых лексем
     */
    QTest::newRow("no_needed_lexemes")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList()
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10 << QSet<error>();

    // Тест 3: Нет нужных символов
    /*!
     * \test Тест 3: Отсутствие искомых символов
     * Проверяет поведение при пустом списке искомых символов
     */
    QTest::newRow("no_needed_symbols")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList()
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {";"}})
        << 0 << 10 << QSet<error>();

    // Тест 4: Нет завершающих лексем
    /*!
     * \test Тест 4: Отсутствие завершающих лексем
     * Проверяет поведение при пустом списке завершающих лексем
     */
    QTest::newRow("no_end_lexemes")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList()
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"String"}, {"s"}, {"="}})
        << 2 << 0 << QSet<error>();

    // Тест 5: В коде нет нужных лексем
    /*!
     * \test Тест 5: Отсутствие совпадений с искомыми лексемами
     * Проверяет случай, когда в коде нет ни одной искомой лексемы
     */
    QTest::newRow("no_matching_lexemes")
        << QStringList({"x = 5;", "s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"x"}, {"="}, {";"}})
        << 0 << 6 << QSet<error>();

    // Тест 6: Несколько нужных символов
    /*!
     * \test Тест 6: Множественные искомые символы
     * Проверяет обработку нескольких искомых символов
     */
    QTest::newRow("multiple_need_symbols")
        << QStringList({"int x = 5+7-3;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"=", "+", "-"})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"+"}, {"-"}, {";"}})
        << 0 << 14 << QSet<error>();

    // Тест 7: Несколько завершающих лексем
    /*!
     * \test Тест 7: Множественные завершающие лексемы
     * Проверяет обработку нескольких завершающих лексем
     */
    QTest::newRow("multiple_end_lexemes")
        << QStringList({"int x = 5;;", "String s = \"potato\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({":", ";", "potato", "tomato"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10 << QSet<error>();

    // Тест 8: Одинаковые лексемы в нужных и завершающих
    /*!
     * \test Тест 8: Пересечение искомых и завершающих лексем
     * Проверяет обработку случая, когда лексемы есть в обоих списках
     */
    QTest::newRow("same_lexemes_in_both")
        << QStringList({"chips= 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String", "chips"})
        << QStringList({"="})
        << QStringList({";", "chips"})
        << StringPair("chips", {{"chips"}})
        << 0 << 5 << QSet<error>();

    // Тест 9: Нужная лексема в однострочном комментарии
    /*!
     * \test Тест 9: Лексема в однострочном комментарии
     * Проверяет игнорирование лексем в однострочных комментариях
     */
    QTest::newRow("lexeme_in_line_comment")
        << QStringList({"x = 5//int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("String", {{"x"}, {"="}, {"String"}, {"s"}, {"="}, {";"}})
        << 1 << 18 << QSet<error>();

    // Тест 10: Нужная лексема в многострочном комментарии
    /*!
     * \test Тест 10: Лексема в многострочном комментарии
     * Проверяет игнорирование лексем в многострочных комментариях
     */
    QTest::newRow("lexeme_in_multiline_comment")
        << QStringList({"/*int x = 5;", "zachet u = 7+0;", "menya v = 8-1;", "karmane ura = 6+1;*/", "String s = \"test\";int x ;"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("String", {{"String"}, {"s"}, {"="}, {";"}})
        << 4 << 18 << QSet<error>();

    // Тест 11: Нужная лексема в символьной константе
    /*!
     * \test Тест 11: Лексема в символьной константе
     * Проверяет игнорирование лексем в символьных константах
     */
    QTest::newRow("lexeme_in_char")
        << QStringList({"char x = 'k';", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"k", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"char"}, {"x"}, {"="}, {";"}})
        << 0 << 13 << QSet<error>();

    // Тест 12: Нужная лексема в строковой константе
    /*!
     * \test Тест 12: Лексема в строковой константе
     * Проверяет игнорирование лексем в строковых константах
     */
    QTest::newRow("lexeme_in_string")
        << QStringList({"String hello = \"bool you\";", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"bool", "les"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("", {{"String"}, {"hello"}, {"="}, {";"}})
        << 0 << 26 << QSet<error>();

    // Тест 13: Поиск с середины кода
    /*!
     * \test Тест 13: Поиск с середины кода
     * Проверяет корректность поиска при старте не с начала кода
     */
    QTest::newRow("search_from_middle")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 1 << 3
        << QStringList({"int", "s"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("s", {{"ing"}, {"s"}, {"="}, {";"}})
        << 1 << 18 << QSet<error>();

    // Тест 14: Множественные пробелы в коде
    /*!
     * \test Тест 14: Множественные пробелы
     * Проверяет обработку кода с избыточными пробелами
     */
    QTest::newRow("multiple_spaces")
        << QStringList({"     int    x    = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 21 << QSet<error>();

    // Тест 15: Лексемы через перевод строки в коде
    /*!
     * \test Тест 15: Лексемы на разных строках
     * Проверяет обработку лексем, разделенных переводами строк
     */
    QTest::newRow("newlines_in_code")
        << QStringList({"int", "x", "=", "5", ";", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {";"}})
        << 4 << 1 << QSet<error>();

    // Тест 16: Несколько нужных лексем в коде
    /*!
     * \test Тест 16: Несколько совпадений с искомыми лексемами
     * Проверяет обработку случая, когда в коде встречается несколько искомых лексем
     */
    QTest::newRow("multiple_matching_lexemes")
        << QStringList({"int xel = last;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "xel", "last"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"xel"}, {"="}, {"last"}, {";"}})
        << 0 << 15 << QSet<error>();

    // Тест 17: Нужная лексема является символом
    /*!
     * \test Тест 17: Искомая лексема - символ
     * Проверяет случай, когда искомая лексема совпадает с символом
     */
    QTest::newRow("lexeme_is_symbol")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"=", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("=", {{"int"}, {"x"}, {"="}, {";"}})
        << 0 << 10 << QSet<error>();

    // Тест 18: Завершающая лексема является словом
    /*!
     * \test Тест 18: Завершающая лексема - слово
     * Проверяет случай, когда завершающая лексема является словом
     */
    QTest::newRow("end_lexeme_is_word")
        << QStringList({"int x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({"String"})
        << StringPair("int", {{"int"}, {"x"}, {"="}, {"String"}})
        << 1 << 6 << QSet<error>();

    // Тест 19: Лексемы с нижним подчеркиванием
    /*!
     * \test Тест 19: Лексемы с подчеркиванием
     * Проверяет обработку идентификаторов с подчеркиванием
     */
    QTest::newRow("underscore_lexemes")
        << QStringList({"int_eger x_x = 5;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int_eger", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int_eger", {{"int_eger"}, {"x_x"}, {"="}, {";"}})
        << 0 << 17 << QSet<error>();

    // Тест 20: Лексемы с цифрами
    /*!
     * \test Тест 20: Лексемы с цифрами
     * Проверяет обработку идентификаторов, содержащих цифры
     */
    QTest::newRow("lexemes_with_digits")
        << QStringList({"int x34 = 5, b32fd53;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x34"}, {"="}, {"b32fd53"}, {";"}})
        << 0 << 21 << QSet<error>();

    // Тест 21: Ошибка, не закрыт многострочный комментарий
    /*!
     * \test Тест 21: Ошибка, не закрыт многострочный комментарий
     * Проверяет случилась ли ошибка при незакрытом комментарии и проверился ли далее нормально код
     */
    QTest::newRow("not_close_multiple_comm")
        << QStringList({"int x34 /*= 5, b32fd53;", "String s = \"test\";"})
        << 0 << 0
        << QStringList({"int", "String"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("int", {{"int"}, {"x34"}, {"="}, {"b32fd53"}, {";"}})
        << 0 << 23 << QSet<error>({error(typeMistakes::notClosedComment, 0,0,0,0,0,0,0,0,0,0)});
    // Тест 22: Ошибка, не закрыта строковая константа
    /*!
     * \test Тест 22: Ошибка, не закрыта строковая константа
     * Проверяет случилась ли ошибка при незакрытой строковой константе и проверился ли далее нормально код
     */
    QTest::newRow("not_close_string_const")
        << QStringList({"String x34 = \"b32fd53;", "char s = 't'  ;"})
        << 0 << 0
        << QStringList({"String", "char"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("char", {{"char"}, {"s"}, {"="}, {";"}})
        << 1 << 15 << QSet<error>({error(typeMistakes::notClosedDoubleQuotes, 0,0,0,0,0,0,0,0,0,0)});
    // Тест 23: Ошибка, не закрыта символьная константа
    /*!
     * \test Тест 23: Ошибка, не закрыта символьная константа
     * Проверяет случилась ли ошибка при незакрытой символьной константе и проверился ли далее нормально код
     */
    QTest::newRow("not_close_symbol_const")
        << QStringList({"char x34 = 'b;", "char s = 't'  ;"})
        << 0 << 0
        << QStringList({"char"})
        << QStringList({"="})
        << QStringList({";"})
        << StringPair("char", {{"char"}, {"s"}, {"="}, {";"}})
        << 1 << 15 << QSet<error>({error(typeMistakes::notClosedSingleQuotes, 0,0,0,0,0,0,0,0,0,0)});
}

void testFindLexemes::test_find_lexemes()
{
    QFETCH(QStringList, code);
    QFETCH(int, indexCurrentString);
    QFETCH(int, indexCurrentSimbol);
    QFETCH(QStringList, neededLexemes);
    QFETCH(QStringList, needSimbols);
    QFETCH(QStringList, endLexems);
    QFETCH(StringPair, expectedResult);
    QFETCH(int, expectedIndexString);
    QFETCH(int, expectedIndexSimbol);
    QFETCH(QSet<error>, expectedErrors);
    QSet<error> actualErrors;
    int actualIndexString = indexCurrentString;
    int actualIndexSimbol = indexCurrentSimbol;

    StringPair actualResult = findLexemes(code, actualIndexString, actualIndexSimbol,
                                          neededLexemes, needSimbols, endLexems, actualErrors, 0);

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
    // Проверим ошибки
    verifyErrors(actualErrors, expectedErrors);
    // Проверим индексы в коде
    QCOMPARE(actualIndexString, expectedIndexString);
    QCOMPARE(actualIndexSimbol, expectedIndexSimbol);
}
