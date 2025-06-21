#include "testsplitfield.h"
#include "main.h"
#include <QMap>


void testSplitField::test_field_data() {
    QTest::addColumn<QStringList>("fieldDeclaration");
    QTest::addColumn<fieldMap>("expectedResult");

    // Тест 1: Публичное поле без инициализации
    QTest::newRow("public_field_no_init")
        << QStringList({"public", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Public", false)}
           });

    // Тест 2: Приватное поле без инициализации
    QTest::newRow("private_field_no_init")
        << QStringList({"private", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", false)}
           });

    // Тест 3: Защищенное поле без инициализации
    QTest::newRow("protected_field_no_init")
        << QStringList({ "protected", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Protected", false)}
           });

    // Тест 4: Поле без модификатора
    QTest::newRow("no_modifier_field")
        << QStringList({ "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)}
           });

    // Тест 5: Статическое поле без модификатора
    QTest::newRow("static_no_modifier")
        << QStringList({ "static", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", true)},
           });

    // Тест 6: Статическое перед модификатором
    QTest::newRow("static_before_modifier")
        << QStringList({ "static", "private", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", true)}
           });

    // Тест 7: Статическое после модификатора
    QTest::newRow("static_after_modifier")
        << QStringList({ "private", "static", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", true)}
           });

    // Тест 8: Инициализированное поле
    QTest::newRow("initialized_field")
        << QStringList({ "int", "a", "=", "6", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)}
           });

    // Тест 9: Несколько полей в объявлении
    QTest::newRow("multiple_fields")
        << QStringList({ "int", "a", "=", "6", ",", "ber", "=", "3", ",", "cac_e", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)},
               {"ber", field("ber", "int", "default", false)},
               {"cac_e", field("cac_e", "int", "default", false)}
           });

    // Тест 10: Контейнерный тип
    QTest::newRow("container_type")
        << QStringList({"Map", "<", "integer", ",", "float", ">", "len"})
        << fieldMap({
               {"len", field("len", "Map<integer, float>", "default", false)}
           });

    // Тест 11: Вложенные контейнеры
    QTest::newRow("nested_containers")
        << QStringList({"Map", "<", "List", "<", "char", ">", ",", "Map", "<", "int", ",", "double", ">", ">", "len"})
        << fieldMap({
               {"len", field("len", "Map<List<char>, Map<int, double>>", "default", false)}
           });

    // Тест 12: Массив
    QTest::newRow("array_type")
        << QStringList({"int", "a", "[", "]", ";"})
        << fieldMap({
               {"a", field("a", "int[]", "default", false)}
           });

    // Тест 13: Массив с размером
    QTest::newRow("sized_array")
        << QStringList({"int", "a", "[", "34", "]", ";"})
        << fieldMap({
               {"a", field("a", "int[]", "default", false)}
           });
}

void testSplitField::test_field() {
    QFETCH(QStringList, fieldDeclaration);
    QFETCH(fieldMap, expectedResult);

    // Вызов функции
    fieldMap actualResult = splitField(fieldDeclaration);
    // Проверка полей
    QString msg = verifyMapField(actualResult, expectedResult);
    QVERIFY2(msg.isEmpty(), qPrintable(msg));
}


