#include "testsplitinterface.h"
#include "class_info.h"

void testsplitinterface::test_split_data() {
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("inputIndexString");
    QTest::addColumn<int>("inputIndexSimbol");
    QTest::addColumn<QStringList>("interfaceDeclaration");
    QTest::addColumn<interface_info>("expectedInterface");
    QTest::addColumn<int>("expectedIndexString");
    QTest::addColumn<int>("expectedIndexSimbol");
    QTest::addColumn<QSet<error>>("expectedErrors");

    // Тест 1: Интерфейс с методом и полем
    QTest::newRow("interface_with_method_and_field")
        << QStringList({"interface TestInterface {", "void interfaceMethod();", "int b;", "}", "float fd;"})
        << 0 << 27
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface",  // nameInterface
               "default",        // mod
               QStringList(),    // extends
               QMap<QString, field>({{"b", field("b", "int", "default", false)}}), // fields
               QSet<method>({{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}), // methods
               QMap<QString, interface_info>(), // includeInterface
               QMap<QString, class_info>(),     // includeClass
               QStringList()                    // import
               )
        << 3 << 1
        << QSet<error>();

    // Тест 2: Интерфейс в одной строке
    QTest::newRow("single_line_interface")
        << QStringList({"interface TestInterface {void interfaceMethod();int b;}float fd;"})
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface",
               "default",
               QStringList(),
               QMap<QString, field>({{"b", field("b", "int", "default", false)}}),
               QSet<method>({{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}),
               QMap<QString, interface_info>(),
               QMap<QString, class_info>(),
               QStringList()
               )
        << 0 << 55
        << QSet<error>();

    // Тест 3: Публичный интерфейс
    QTest::newRow("public_interface")
        << QStringList({"public interface TestInterface {", "void interfaceMethod();", "int b;", "}", "float fd;"})
        << 0 << 33
        << QStringList({"public", "interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface",
               "Public",
               QStringList(),
               QMap<QString, field>({{"b", field("b", "int", "default", false)}}),
               QSet<method>({{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}),
               QMap<QString, interface_info>(),
               QMap<QString, class_info>(),
               QStringList()
               )
        << 3 << 1
        << QSet<error>();

    // Тест 6: Один родительский интерфейс
    QTest::newRow("single_parent_interface")
        << QStringList({"interface TestInterface extends Test1{", "void interfaceMethod();", "int b;", "}", "float fd;"})
        << 0 << 38
        << QStringList({"interface", "TestInterface", "extends", "Test1", "{"})
        << interface_info(
               "TestInterface", "default", {"Test1"},
               {{"b", field("b", "int", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 7: Несколько родительских интерфейсов
    QTest::newRow("multiple_parent_interfaces")
        << QStringList({"interface TestInterface extends Test1,Test2,Test3{", "void interfaceMethod();", "int b;", "}", "float fd;"})
        << 0 << 51
        << QStringList({"interface", "TestInterface", "extends", "Test1", "Test2", "Test3", "{"})
        << interface_info(
               "TestInterface", "default", {"Test1", "Test2", "Test3"},
               {{"b", field("b", "int", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 8: Интерфейс с несколькими полями
    QTest::newRow("multiple_fields_interface")
        << QStringList({"interface TestInterface {", "void interfaceMethod();", "int b;", "String nil;", "float c = 8.3;", "}", "float fd;"})
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {
                   {"b", field("b", "int", "default", false)},
                   {"nil", field("nil", "String", "default", false)},
                   {"c", field("c", "float", "default", false)}
               },
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 5 << 1 << QSet<error>();

    // Тест 9: Интерфейс с несколькими методами
    QTest::newRow("multiple_methods_interface")
        << QStringList({"interface TestInterface {", "void interfaceMethod();", "int intTestMet1();", "float fTestMet2();", "int b;", "}", "float fd;"})
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {
                   {method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                   {method("intTestMet1", "int", false, false, "default", "intTestMet1()", {}, {})},
                   {method("fTestMet2", "float", false, false, "default", "fTestMet2()", {}, {})}
               },
               {}, {}, {}
               )
        << 5 << 1 << QSet<error>();

    // Тест 10: Вложенный класс
    QTest::newRow("nested_class_interface")
        << QStringList({"interface TestInterface {", "class NestedClass{ char c; }", "int b;", "}", "float fd;"})
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {},
               {},
               {{"NestedClass", class_info("NestedClass", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {},{}, {}, false, false)}},
               {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 11: Несколько вложенных классов
    QTest::newRow("multiple_nested_classes")
        << QStringList({
               "interface TestInterface {",
               "class NestedClass{ char c; }",
               "class nested1{ void hell(){} }",
               "int b;",
               "class nested2{}",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {},
               {},
               {
                   {"NestedClass", class_info("NestedClass", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {}, {}, {}, false, false)},
                   {"nested1", class_info("nested1", "default", "", {}, {}, {}, {method("hell", "void",false ,false,"default", "hell()", {"{}"},  {})}, {},{}, {}, false, false)},
                   {"nested2", class_info("nested2", "default", "", {}, {}, {}, {}, {},{}, {}, false, false)}
               },
               {}
               )
        << 5 << 1 << QSet<error>();

    // Тест 12: Вложенный интерфейс
    QTest::newRow("nested_interface")
        << QStringList({
               "interface TestInterface {",
               "interface nestedInter1{ int a; }",
               "int b;",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {},
               {{"nestedInter1", interface_info("nestedInter1", "default", {}, {{"a", field("a", "int", "default", false)}}, {}, {}, {}, {})}},
               {},
               {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 13: Несколько вложенных интерфейсов
    QTest::newRow("multiple_nested_interfaces")
        << QStringList({
               "interface TestInterface {",
               "interface Nested{ char c; }",
               "interface nested1{ void hell(){} }",
               "int b;",
               "interface nested2{}",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {},
               {
                   {"Nested", interface_info("Nested", "default", {}, {{"c", field("c", "char", "default", false)}}, {}, {}, {}, {})},
                   {"nested1", interface_info("nested1", "default", {}, {}, {method("hell", "void",false ,false,"default", "hell()", {"{}"},  {})}, {}, {}, {})},
                   {"nested2", interface_info("nested2", "default", {}, {}, {}, {}, {}, {})}
               },
               {},
               {}
               )
        << 5 << 1 << QSet<error>();

    // Тест 14: Вложенные интерфейс и класс
    QTest::newRow("mixed_nested_elements")
        << QStringList({
               "interface TestInterface {",
               "class Nested{ char c; }",
               "interface nested1{ void hell(){} }",
               "interface nested2{}",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {},
               {},
               {
                   {"nested1", interface_info("nested1", "default", {}, {}, {method("hell", "void",false ,false,"default", "hell()", {"{}"},  {})}, {}, {}, {})},
                   {"nested2", interface_info("nested2", "default", {}, {}, {}, {}, {}, {})}
               },
               {{"Nested", class_info("Nested", "default", "", {}, {}, {{"c", field("c", "char", "default", false)}}, {}, {},{}, {}, false, false)}},
               {}
               )
        << 4 << 1 << QSet<error>();

    // Тест 15: Две пары фигурных скобок
    QTest::newRow("two_brace_pairs")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();",
               "default void method2(){ int b =12; }",
               "int b;",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                {method("method2", "void", false, false, "default", "method2()", {"{ int b =12; }"}, {})}},
               {}, {}, {}
               )
        << 4 << 1 << QSet<error>();

    // Тест 16: Вложенные фигурные скобки
    QTest::newRow("nested_braces")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();",
               "default void method2(){ int b =12; if(12 == 12) {} }",
               "int b;",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                {method("method2", "void", false, false, "default", "method2()", {"{ int b =12; if(12 == 12) {} }"}, {})}},
               {}, {}, {}
               )
        << 4 << 1 << QSet<error>();

    // Тест 17: Фигурные скобки в однострочном комментарии
    QTest::newRow("brace_in_line_comment")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();// } field",
               "int b;",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {{ method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 18: Фигурные скобки в многострочном комментарии
    QTest::newRow("brace_in_multiline_comment")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();/*privet {} testiki {} } hihihi bububu }*/",
               "int b;",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 19: Фигурные скобки в строковой константе
    QTest::newRow("brace_in_string")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();",
               "String strochka = \"privetiki {} }}\";",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"strochka", field("strochka", "String", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 20: Фигурные скобки в символьной константе
    QTest::newRow("brace_in_char")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();",
               "char odin = '}';",
               "}", "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"odin", field("odin", "char", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 3 << 1 << QSet<error>();

    // Тест 21: Нет закрывающей фигурной скобки
    QTest::newRow("missing_closing_brace")
        << QStringList({
               "interface TestInterface {",
               "void interfaceMethod();",
               "int b;",
               "float fd;"
           })
        << 0 << 25
        << QStringList({"interface", "TestInterface", "{"})
        << interface_info(
               "TestInterface", "default", {},
               {{"b", field("b", "int", "default", false)}, {"fd", field("fd", "float", "default", false)}},
               {{method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 4 << 0
        << QSet<error>({error(typeMistakes::noClosingFiguredScoop, 0, 0,0,0,0,0,0,0,0,4)});
}

void testsplitinterface::test_split() {
    QFETCH(QStringList, code);
    QFETCH(int, inputIndexString);
    QFETCH(int, inputIndexSimbol);
    QFETCH(QStringList, interfaceDeclaration);
    QFETCH(interface_info, expectedInterface);
    QFETCH(int, expectedIndexString);
    QFETCH(int, expectedIndexSimbol);
    QFETCH(QSet<error>, expectedErrors);

    int actualIndexString = inputIndexString;
    int actualIndexSimbol = inputIndexSimbol;
    QSet<error> actualErrors;

    interface_info result = splitInterface(code,actualIndexString,actualIndexSimbol,interfaceDeclaration,actualErrors );

    // Проверка индексов
    QVERIFY2(actualIndexString == expectedIndexString,
             qPrintable(QString("\nИндекс строки: ожидалось %1, получено %2").arg(expectedIndexString).arg(actualIndexString)));
    QVERIFY2(actualIndexSimbol == expectedIndexSimbol,
             qPrintable(QString("\nИндекс символа: ожидалось %1, получено %2").arg(expectedIndexSimbol).arg(actualIndexSimbol)));
    QString msg = verifyInterface(result, expectedInterface);
    QVERIFY2(msg.isEmpty(), qPrintable(msg));
    verifyErrors(actualErrors, expectedErrors);
}

