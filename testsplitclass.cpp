#include "testsplitclass.h"
#include "typeMistakes.h"
#include "main.h"

void testsplitclass::test_class_data() {
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("inputIndexString");
    QTest::addColumn<int>("inputIndexSimbol");
    QTest::addColumn<QStringList>("classDeclaration");
    QTest::addColumn<class_info>("expectedClass");
    QTest::addColumn<int>("expectedIndexString");
    QTest::addColumn<int>("expectedIndexSimbol");
    QTest::addColumn<QSet<error>>("expectedErrors");
    // Тест 1: Класс с методом и полем
    /*!
     * \test Тест 1: Класс с методом и полем
     * Проверяет обработку простого класса с одним методом и одним полем
     */
    QTest::newRow("class_with_method_and_field")
        << QStringList({
               "class TestClass {",
               "void classMethod(){",
               "int a;",
               "}",
               "int b;",
               "}",
               "float fd;"
           })
        << 0 << 17
        << QStringList({"class", "TestClass", "{"})
        << class_info(
               "TestClass", "default", "", QStringList(), {},
               {{"b", field("b", "int", "default", false)}},
               {                    method(
                                    "classMethod", "void", false, false, "default", "classMethod()",
                                    {"{", "int a;" , "}"}, {}
                                    )},
               {}, {}, {}, false, false
               )
        << 5 << 1 << QSet<error>();

    // Тест 2: Класс в одной строке (фигурные скобки метода в одной строке)
    /*!
     * \test Тест 2: Класс в одной строке
     * Проверяет обработку класса, объявленного в одной строке
     */
    QTest::newRow("single_line_class")
        << QStringList({"  class TestClass {void classMethod(){};int b;}float fd;"})
        << 0 << 19
        << QStringList({"class", "TestClass", "{"})
        << class_info(
               "TestClass", "default", "", QStringList(), {},
               {{"b", field("b", "int", "default", false)}},
               {{method(
                                    "classMethod", "void", false, false, "default", "classMethod()",
                                    {"{}"}, {}
                                    )}},
               {}, {}, {}, false, false
               )
        << 0 << 47 << QSet<error>();

    // Тест 3: Публичный класс (метод без реализации - без скобок)
    /*!
     * \test Тест 3: Публичный класс
     * Проверяет обработку класса с модификатором доступа public
     */
    QTest::newRow("public_class")
        << QStringList({
               "public class TestClass {",
               "void classMethod();",
               "int b;",
               "}",
               "float fd;"
           })
        << 0 << 23
        << QStringList({"public", "class", "TestClass", "{"})
        << class_info(
               "TestClass", "Public", "", QStringList(), {},
               {{"b", field("b", "int", "default", false)}},
               {{method(
                                    "classMethod", "void", false, false, "default", "classMethod()",
                                    {}, {}
                                    )}},
               {}, {}, {}, false, false
               )
        << 3 << 1 << QSet<error>();

    // Тест 4: Приватный класс
    /*!
     * \test Тест 4: Приватный класс
     * Проверяет обработку класса с модификатором доступа private
     */
QTest::newRow("private_class")
    << QStringList({
        "private class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 25
    << QStringList({"private", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Private", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 5: Защищенный класс
    /*!
     * \test Тест 5: Защищенный класс
     * Проверяет обработку класса с модификатором доступа protected
     */
QTest::newRow("protected_class")
    << QStringList({
        "protected class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 27
    << QStringList({"protected", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Protected", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 6: Один интерфейс
/*!
     * \test Тест 6: Один интерфейс
     * Проверяет обработку класса, реализующего один интерфейс
     */
QTest::newRow("single_interface")
    << QStringList({
        "class TestClass implements Test1{",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 33
    << QStringList({"class", "TestClass", "implements", "Test1", "{"})
    << class_info(
        "TestClass", "default", "", {"Test1"}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 7: Несколько интерфейсов
/*!
     * \test Тест 7: Несколько интерфейсов
     * Проверяет обработку класса, реализующего несколько интерфейсов
     */
QTest::newRow("multiple_interfaces")
    << QStringList({
        "class TestClass implements Test1,Test2,Test3{",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 46
    << QStringList({"class", "TestClass", "implements", "Test1", "Test2", "Test3", "{"})
    << class_info(
        "TestClass", "default", "", {"Test1", "Test2", "Test3"}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 8: Родительский класс
/*!
     * \test Тест 8: Родительский класс
     * Проверяет обработку класса с родительским классом
     */
QTest::newRow("parent_class")
    << QStringList({
        "class TestClass extends parentClass{",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 36
    << QStringList({"class", "TestClass", "extends", "parentClass", "{"})
    << class_info(
        "TestClass", "default", "parentClass", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 9: Родитель и интерфейсы
/*!
     * \test Тест 9: Родитель и интерфейсы
     * Проверяет обработку класса с родительским классом и интерфейсами
     */
QTest::newRow("parent_and_interfaces")
    << QStringList({
        "class TestClass extends parentClass implements Test1, Test2{",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 61
    << QStringList({"class", "TestClass", "extends", "parentClass", "implements", "Test1", "Test2", "{"})
    << class_info(
        "TestClass", "default", "parentClass", {"Test1", "Test2"}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 10: Несколько полей
/*!
     * \test Тест 10: Несколько полей
     * Проверяет обработку класса с несколькими полями
     */
QTest::newRow("multiple_fields")
    << QStringList({
        "class TestClass {",
        "void classMethod();",
        "int b;",
        "String nil;",
        "float c = 8.3;",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {
            {"b", field("b", "int", "default", false)},
            {"nil", field("nil", "String", "default", false)},
            {"c", field("c", "float", "default", false)}
        },
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, false
    )
    << 5 << 1 << QSet<error>();

// Тест 11: Несколько методов
/*!
     * \test Тест 11: Несколько методов
     * Проверяет обработку класса с несколькими методами
     */
QTest::newRow("multiple_methods")
    << QStringList({
        "class TestClass {",
        "void classMethod(){}",
        "int intTestMet1(){bool el = true;}",
        "float fTestMet2();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {
            {method("classMethod", "void", false, false, "default", "classMethod()", {"{}"}, {})},
            {method("intTestMet1", "int", false, false, "default", "intTestMet1()", {"{bool el = true;}"}, {})},
            {method("fTestMet2", "float", false, false, "default", "fTestMet2()", {}, {})}
        },
        {}, {}, {}, false, false
    )
    << 5 << 1 << QSet<error>();

// Тест 12: Конструктор
/*!
     * \test Тест 12: Конструктор
     * Проверяет обработку класса с конструктором
     */
QTest::newRow("with_constructor")
    << QStringList({
        "class TestClass {",
        "TestClass(string men){this.alo = men;}",
        "int intTestMet1(){}",
        "float fTestMet2(){}",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {},
        {constructor( "default", "TestClass(string)", {"{this.alo = men;}"}, {argument("men", "string")})},
        {{"b", field("b", "int", "default", false)}},
        {
            {method("intTestMet1", "int", false, false, "default", "intTestMet1()", {"{}"}, {})},
            {method("fTestMet2", "float", false, false, "default", "fTestMet2()", {"{}"}, {})}
        },
        {}, {}, {}, false, false
    )
    << 5 << 1 << QSet<error>();

// Тест 13: Статический класс
/*!
     * \test Тест 13: Статический класс
     * Проверяет обработку класса с модификатором static
     */
QTest::newRow("static_class")
    << QStringList({
        "static class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 24
    << QStringList({"static", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, true
    )
    << 3 << 1 << QSet<error>();

// Тест 14: Абстрактный класс
/*!
     * \test Тест 14: Абстрактный класс
     * Проверяет обработку класса с модификатором abstract
     */
QTest::newRow("abstract_class")
    << QStringList({
        "abstract class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 26
    << QStringList({"abstract", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, true, false
    )
    << 3 << 1 << QSet<error>();

// Тест 15: Публичный статический класс
/*!
     * \test Тест 15: Публичный статический класс
     * Проверяет обработку класса с модификаторами public и static
     */
QTest::newRow("public_static_class")
    << QStringList({
        "public static class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 31
    << QStringList({"public", "static", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Public", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, true
    )
    << 3 << 1 << QSet<error>();

// Тест 16: Статический публичный класс (порядок модификаторов)
/*!
     * \test Тест 16: Статический публичный класс
     * Проверяет обработку класса с модификаторами static и public (разный порядок)
     */
QTest::newRow("static_public_class")
    << QStringList({
        "static public class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 31
    << QStringList({"static", "public", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Public", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, false, true
    )
    << 3 << 1 << QSet<error>();

// Тест 17: Публичный статический абстрактный класс
/*!
     * \test Тест 17: Публичный статический абстрактный класс
     * Проверяет обработку класса с модификаторами public, static и abstract
     */
QTest::newRow("public_static_abstract_class")
    << QStringList({
        "public static abstract class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 40
    << QStringList({"public", "static", "abstract", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Public", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, true, true
    )
    << 3 << 1 << QSet<error>();

// Тест 18: Публичный абстрактный статический класс (разный порядок)
/*!
     * \test Тест 18: Публичный абстрактный статический класс
     * Проверяет обработку класса с модификаторами public, abstract и static (разный порядок)
     */
QTest::newRow("public_abstract_static_class")
    << QStringList({
        "public abstract static class TestClass {",
        "void classMethod();",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 40
    << QStringList({"public", "abstract", "static", "class", "TestClass", "{"})
    << class_info(
        "TestClass", "Public", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
        {}, {}, {}, true, true
    )
    << 3 << 1 << QSet<error>();

// Тест 19: Вложенный класс
/*!
     * \test Тест 19: Вложенный класс
     * Проверяет обработку класса с одним вложенным классом
     */
QTest::newRow("nested_class")
    << QStringList({
        "class TestClass {",
        "class NestedClass{ char c; }",
        "int b;",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {{"b", field("b", "int", "default", false)}},
        {},
        {{"NestedClass", class_info("NestedClass", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {}, {}, {}, false, false)}},
        {}, {}, false, false
    )
    << 3 << 1 << QSet<error>();

// Тест 20: Несколько вложенных классов
/*!
     * \test Тест 20: Несколько вложенных классов
     * Проверяет обработку класса с несколькими вложенными классами
     */
QTest::newRow("multiple_nested_classes")
    << QStringList({
           "class TestClass {",
           "class NestedClass{ char c; }",
           "class nested1{",
           "void hell(){}",
           "}",
           "int b;",
           "class nested2{",
           "}",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {},
           {
               {"NestedClass", class_info("NestedClass", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {}, {}, {}, false, false)},
               {"nested1", class_info("nested1", "default", "", {}, {}, {}, {{method("hell", "void", false, false, "default", "hell()", {"{}"}, {})}}, {}, {}, {}, false, false)},
               {"nested2", class_info("nested2", "default", "", {}, {}, {}, {}, {}, {}, {}, false, false)}
           },
           {}, {}, false, false
           )
    << 8 << 1 << QSet<error>();

// Тест 21: Вложенный интерфейс
/*!
     * \test Тест 21: Вложенный интерфейс
     * Проверяет обработку класса с вложенным интерфейсом
     */
QTest::newRow("nested_interface")
    << QStringList({
           "class TestClass {",
           "interface nestedInter1{int a; }",
           "int b;",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {},
           {},
           {
               {"nestedInter1", interface_info(
                                    "nestedInter1",
                                    "default",
                                    QStringList(),
                                    {{"a", field("a", "int", "default", false)}},
                                    {},
                                    {},
                                    {},
                                    QStringList()
                                    )}
           },
           {}, false, false
           )
    << 3 << 1 << QSet<error>();

// Тест 22: Несколько вложенных интерфейсов
/*!
     * \test Тест 22: Несколько вложенных интерфейсов
     * Проверяет обработку класса с несколькими вложенными интерфейсами
     */
QTest::newRow("multiple_nested_interfaces")
    << QStringList({
           "class TestClass {",
           "interface Nested{ char c; }",
           "interface nested1{",
           "void hell(){}",
           "}",
           "int b;",
           "interface nested2{",
           "}",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {},
           {},
           {
               {"Nested", interface_info("Nested", "default", QStringList(), {{"c", field("c", "char", "default", false)}}, {}, {}, {}, QStringList())},
               {"nested1", interface_info("nested1", "default", QStringList(), {}, {{method("hell", "void", false, false, "default", "hell()", {"{}"}, {})}}, {}, {}, QStringList())},
               {"nested2", interface_info("nested2", "default", QStringList(), {}, {}, {}, {}, QStringList())}
           },
           {}, false, false
           )
    << 8 << 1 << QSet<error>();

// Тест 23: Вложены и интерфейс, и класс
/*!
     * \test Тест 23: Вложены и интерфейс, и класс
     * Проверяет обработку класса с вложенными и классом, и интерфейсом
     */
QTest::newRow("nested_class_and_interface")
    << QStringList({
           "class TestClass {",
           "class Nested{ char c; }",
           "interface nested1{",
           "void hell(){}",
           "}",
           "interface nested2{",
           "}",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {},
           {},
           {
               {"Nested", class_info("Nested", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {}, {}, {}, false, false)}
           },
           {
               {"nested1", interface_info("nested1", "default", QStringList(), {}, {{method("hell", "void", false, false, "default", "hell()", {"{}"}, {})}}, {}, {}, QStringList())},
               {"nested2", interface_info("nested2", "default", QStringList(), {}, {}, {}, {}, QStringList())}
           },
           {}, false, false
           )
    << 7 << 1 << QSet<error>();

// Тест 24: Две пары фигурных скоб
/*!
     * \test Тест 24: Две пары фигурных скоб
     * Проверяет обработку класса с несколькими парами фигурных скобок
     */
QTest::newRow("two_brace_pairs")
    << QStringList({
           "class TestClass {",
           "void classMethod();",
           "void method2(){",
           "int c =12;",
           "}",
           "int b;",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})},
            {method("method2", "void", false, false, "default", "method2()", {"{", "int c =12;", "}"}, {})}},
           {}, {}, {}, false, false
       )
    << 6 << 1 << QSet<error>();

// Тест 25: Вложенные фигурные скобы
/*!
     * \test Тест 25: Вложенные фигурные скобы
     * Проверяет обработку вложенных фигурных скобок в методах класса
     */
QTest::newRow("nested_braces")
    << QStringList({
           "class TestClass {",
           "void classMethod(){",
           "if(14 == 13){",
           "int c =12;",
           "if(12 == 12) { }",
           "}}",
           "int b;",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {{method("classMethod", "void", false, false, "default", "classMethod()", {"{","if(14 == 13){","int c =12;","if(12 == 12) { }", "}}"},{})}},
           {}, {}, {}, false, false
       )
    << 7 << 1 << QSet<error>();

// Тест 26: Фигурные скобки в однострочном комментарии
/*!
     * \test Тест 26: Фигурные скобки в однострочном комментарии
     * Проверяет игнорирование скобок в однострочных комментариях
     */
QTest::newRow("braces_in_singleline_comment")
    << QStringList({
           "class TestClass {",
           "void classMethod();// } field",
           "int b;",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
           {}, {}, {}, false, false
       )
    << 3 << 1 << QSet<error>();

// Тест 27: Фигурные скобки в многострочном комментарии
/*!
     * \test Тест 27: Фигурные скобки в многострочном комментарии
     * Проверяет игнорирование скобок в многострочных комментариях
     */
QTest::newRow("braces_in_multiline_comment")
    << QStringList({
           "class TestClass {",
           "void classMethod();/*privet {}",
           "testiki {} } hihihi",
           "bububu }*/",
           "int b;",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"b", field("b", "int", "default", false)}},
           {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
           {}, {}, {}, false, false
       )
    << 5 << 1 << QSet<error>();

// Тест 28: Фигурные скобки в строковой константе
/*!
     * \test Тест 28: Фигурные скобки в строковой константе
     * Проверяет игнорирование скобок в строковых константах
     */
QTest::newRow("braces_in_string_literal")
    << QStringList({
           "class TestClass {",
           "void classMethod();",
           "String strochka = \"privetiki {} }}\";",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"strochka", field("strochka", "String", "default", false)}},
           {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
           {}, {}, {}, false, false
       )
    << 3 << 1 << QSet<error>();

// Тест 29: Фигурные скобки в символьной константе
/*!
     * \test Тест 29: Фигурные скобки в символьной константе
     * Проверяет игнорирование скобок в символьных константах
     */
QTest::newRow("braces_in_char_literal")
    << QStringList({
           "class TestClass {",
           "void interfaceMethod();",
           "char odin = '}';",
           "}",
           "float fd;"
       })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
           "TestClass", "default", "", QStringList(), {},
           {{"odin", field("odin", "char", "default", false)}},
           {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
           {}, {}, {}, false, false
       )
    << 3 << 1 << QSet<error>();

// Тест 30: Нет закрывающей скобки (ошибка)
/*!
     * \test Тест 30: Нет закрывающей скобки (ошибка)
     * Проверяет обработку ситуации с отсутствующей закрывающей скобкой класса
     */
QTest::newRow("unclosed_class_brace")
    << QStringList({
        "class TestClass {",
        "void classMethod();",
        "int b;",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
             << class_info(
           "TestClass", "default", "", QStringList(), {},
                    {{"b", field("b", "int", "default", false)},{"fd", field("fd", "float", "default", false)} },
                    {{method("classMethod", "void", false, false, "default", "classMethod()", {}, {})}},
                    {}, {}, {}, false, false
                )
    << 4 << 0
    << QSet<error>({error(typeMistakes::noClosingFiguredScoop, 0, 0,0,0,0,0,0,0,0,4)});

// Тест 31: Методы с одинаковыми именами (перегрузка)
/*!
     * \test Тест 31: Методы с одинаковыми именами (перегрузка)
     * Проверяет обработку перегруженных методов в классе
     */
QTest::newRow("overloaded_methods")
    << QStringList({
        "class TestClass {",
        "void classMethod(int l, float v);",
        "void classMethod(int l, bool v);",
        "void classMethod(){}",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {}, {},
        {},
        {
            {method("classMethod", "void", false, false, "default", "classMethod(int, float)", {}, {argument("l", "int"), argument("v", "float")})},
            {method("classMethod", "void", false, false, "default", "classMethod(int, bool)", {}, {argument("l", "int"), argument("v", "bool")})},
            {method("classMethod", "void", false, false, "default", "classMethod()", {"{}"}, {})}
        },
        {}, {}, {}, false, false
    )
    << 4 << 1 << QSet<error>();

// Тест 32: Несколько конструкторов
/*!
     * \test Тест 32: Несколько конструкторов
     * Проверяет обработку класса с несколькими конструкторами
     */
QTest::newRow("multiple_constructors")
    << QStringList({
        "class TestClass {",
        "public TestClass(){this.odin = \"less\";}",
        "TestClass(String l){this.odin = l;}",
        "TestClass(String v){if(!v.isEmpty())this.odin = v;}",
        "char odin = '}';",
        "}",
        "float fd;"
    })
    << 0 << 17
    << QStringList({"class", "TestClass", "{"})
    << class_info(
        "TestClass", "default", "", {},
        {
            constructor( "Public", "TestClass()", {"{this.odin = \"less\";}"}, {}),
            constructor( "default", "TestClass(String)", {"{this.odin = l;}"}, {argument("l", "String")}),
            constructor( "default", "TestClass(String)", {"{if(!v.isEmpty())this.odin = v;}"}, {argument("v", "String")})
        },
        {{"odin", field("odin", "char", "default", false)}},
        {},
        {}, {}, {}, false, false
    )
    << 5 << 1 << QSet<error>();

// Тест 33: Статический конструктор в классе
/*!
     * \test Тест 33: Статический конструктор в классе
     * Проверяет обработку статического блока инициализации в классе
     */
QTest::newRow("simple_static_initializer")
    << QStringList({
           "class SimpleClass {",
           "static int count;",
           "static {",
           "count = 10;",
           "}",
           "}"
       })
    << 0 << 19
    << QStringList({"class", "SimpleClass", "{"})
    << class_info(
           "SimpleClass", "default", "", {},
           {constructor( "default", "static", {"{","count = 10;", "}"}, {})},
           {{"count", field("count", "int", "default", true)}}, // Статическое поле
           {}, // Нет методов
           {}, {}, {}, false, false
           )
    << 5 << 1 << QSet<error>();
}

void testsplitclass::test_class() {
    QFETCH(QStringList, code);
    QFETCH(int, inputIndexString);
    QFETCH(int, inputIndexSimbol);
    QFETCH(QStringList, classDeclaration);
    QFETCH(class_info, expectedClass);
    QFETCH(int, expectedIndexString);
    QFETCH(int, expectedIndexSimbol);
    QFETCH(QSet<error>, expectedErrors);

    // Подготовка
    int actualIndexString = inputIndexString;
    int actualIndexSimbol = inputIndexSimbol;
    QSet<error> actualErrors;

    // Вызов функции
    class_info result = splitClass( code,actualIndexString,actualIndexSimbol,classDeclaration,actualErrors);

    // Проверка индексов
    QCOMPARE(actualIndexString, expectedIndexString);
    QCOMPARE(actualIndexSimbol, expectedIndexSimbol);

    QString msg = verifyClass(result, expectedClass);
    QVERIFY2(msg.isEmpty(), qPrintable(msg));
    verifyErrors(actualErrors,expectedErrors);
}
