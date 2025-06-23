#include "testsplitfield.h"
#include "main.h"
#include <QMap>

void testSplitField::test_field_data() {
    QTest::addColumn<QStringList>("fieldDeclaration");
    QTest::addColumn<fieldMap>("expectedResult");

    /*!
     * \test Тест 1: Публичное поле без инициализации
     * Проверяет обработку публичного поля без значения по умолчанию
     */
    QTest::newRow("public_field_no_init")
        << QStringList({"public", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Public", false)}
           });

    /*!
     * \test Тест 2: Приватное поле без инициализации
     * Проверяет обработку приватного поля без значения по умолчанию
     */
    QTest::newRow("private_field_no_init")
        << QStringList({"private", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", false)}
           });

    /*!
     * \test Тест 3: Защищенное поле без инициализации
     * Проверяет обработку защищенного поля без значения по умолчанию
     */
    QTest::newRow("protected_field_no_init")
        << QStringList({ "protected", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Protected", false)}
           });

    /*!
     * \test Тест 4: Поле без модификатора
     * Проверяет обработку поля без указания модификатора доступа
     */
    QTest::newRow("no_modifier_field")
        << QStringList({ "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)}
           });

    /*!
     * \test Тест 5: Статическое поле без модификатора
     * Проверяет обработку статического поля без модификатора доступа
     */
    QTest::newRow("static_no_modifier")
        << QStringList({ "static", "int", "a", ";"})
        << fieldMap({
                     {"a", field("a", "int", "default", true)},
                     });

    /*!
     * \test Тест 6: Статическое перед модификатором
     * Проверяет обработку статического поля с модификатором доступа после static
     */
    QTest::newRow("static_before_modifier")
        << QStringList({ "static", "private", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", true)}
           });

    /*!
     * \test Тест 7: Статическое после модификатора
     * Проверяет обработку статического поля с модификатором доступа перед static
     */
    QTest::newRow("static_after_modifier")
        << QStringList({ "private", "static", "int", "a", ";"})
        << fieldMap({
               {"a", field("a", "int", "Private", true)}
           });

    /*!
     * \test Тест 8: Инициализированное поле
     * Проверяет обработку поля с инициализацией значения
     */
    QTest::newRow("initialized_field")
        << QStringList({ "int", "a", "=", "6", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)}
           });

    /*!
     * \test Тест 9: Несколько полей в объявлении
     * Проверяет обработку нескольких полей в одном объявлении
     */
    QTest::newRow("multiple_fields")
        << QStringList({ "int", "a", "=", "6", ",", "ber", "=", "3", ",", "cac_e", ";"})
        << fieldMap({
               {"a", field("a", "int", "default", false)},
               {"ber", field("ber", "int", "default", false)},
               {"cac_e", field("cac_e", "int", "default", false)}
           });

    /*!
     * \test Тест 10: Контейнерный тип
     * Проверяет обработку поля с типом-контейнером
     */
    QTest::newRow("container_type")
        << QStringList({"Map", "<", "integer", ",", "float", ">", "len"})
        << fieldMap({
               {"len", field("len", "Map<integer, float>", "default", false)}
           });

    /*!
     * \test Тест 11: Вложенные контейнеры
     * Проверяет обработку поля с вложенными типами-контейнерами
     */
    QTest::newRow("nested_containers")
        << QStringList({"Map", "<", "List", "<", "char", ">", ",", "Map", "<", "int", ",", "double", ">", ">", "len"})
        << fieldMap({
               {"len", field("len", "Map<List<char>, Map<int, double>>", "default", false)}
           });

    /*!
     * \test Тест 12: Массив
     * Проверяет обработку поля-массива без указания размера
     */
    QTest::newRow("array_type")
        << QStringList({"int", "a", "[", "]", ";"})
        << fieldMap({
               {"a", field("a", "int[]", "default", false)}
           });

    /*!
     * \test Тест 13: Массив с размером
     * Проверяет обработку поля-массива с указанием размера
     */
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
