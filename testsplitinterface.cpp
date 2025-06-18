#include "testsplitinterface.h"
#include "class_info.h"

void testsplitinterface::add_data() {
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
               QMap<QString, method>({{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}), // methods
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
               QMap<QString, method>({{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}),
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
               QMap<QString, method>({{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", QStringList(), QVector<argument>())}}),
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
                   {"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                   {"intTestMet1", method("intTestMet1", "int", false, false, "default", "intTestMet1()", {}, {})},
                   {"fTestMet2", method("fTestMet2", "float", false, false, "default", "fTestMet2()", {}, {})}
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
               {{"NestedClass", class_info("NestedClass", "default", "", {}, {}, {}, {}, {},{}, {}, false, false)}},
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
                   {"NestedClass", class_info("NestedClass", "default", "", {}, {}, {}, {}, {}, {}, {}, false, false)},
                   {"nested1", class_info("nested1", "default", "", {}, {}, {}, {}, {},{}, {}, false, false)},
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
                   {"nested1", interface_info("nested1", "default", {}, {}, {}, {}, {}, {})},
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
                   {"nested1", interface_info("nested1", "default", {}, {}, {}, {}, {}, {})},
                   {"nested2", interface_info("nested2", "default", {}, {}, {}, {}, {}, {})}
               },
               {{"Nested", class_info("Nested", "default", "", {}, {}, {}, {}, {},{}, {}, false, false)}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                {"method2", method("method2", "void", false, false, "default", "method2()", {"{ int b =12; }"}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})},
                {"method2", method("method2", "void", false, false, "default", "method2()", {"{ int b =12; if(12 == 12) {} }"}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
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
               {{"interfaceMethod", method("interfaceMethod", "void", false, false, "default", "interfaceMethod()", {}, {})}},
               {}, {}, {}
               )
        << 4 << 0
        << QSet<error>({error(typeMistakes::noClosingFiguredScoop, 0, 0,0,0,0,0,0,0,0,4)});
}

void testsplitinterface::add() {
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

    // Проверка ошибок
    if (actualErrors != expectedErrors) {
        QStringList messages;

        // Находим ошибки, которые есть в expected, но нет в actual
        QSet<error> missingErrors = expectedErrors - actualErrors;
        for (QSet<error>::const_iterator it = missingErrors.constBegin();it != missingErrors.constEnd(); ++it) {
            const error& err = *it;
            messages << QString("Отсутствует ожидаемая ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в actual, но нет в expected
        QSet<error> unexpectedErrors = actualErrors - expectedErrors;
        for (QSet<error>::const_iterator it = unexpectedErrors.constBegin();it != unexpectedErrors.constEnd(); ++it) {
            const error& err = *it;
            messages << QString("Обнаружена неожиданная ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в обоих наборах, но различаются по полям
        QSet<error> commonErrors = actualErrors & expectedErrors;
        for (QSet<error>::const_iterator it = commonErrors.constBegin();
             it != commonErrors.constEnd(); ++it) {
            const error& err = *it;
            const error& expectedErr = *expectedErrors.constFind(err);
            if (!(err == expectedErr)) {
                QStringList diffFields;
                if (err.typeMistake != expectedErr.typeMistake) diffFields << "тип ошибки";
                if (err.fileNumber != expectedErr.fileNumber) diffFields << "номер файла";
                if (err.numberStr != expectedErr.numberStr) diffFields << "номер строки";
                messages << QString("Ошибка %1 отличается по полям: %2").arg(int(err.typeMistake)).arg(diffFields.join(", "));
            }
        }

        QVERIFY2(false, qPrintable(QString("Наборы ошибок не совпадают:\n%1\nОжидалось %2 ошибок, получено %3 ошибок").arg(messages.join("\n")).arg(expectedErrors.size()).arg(actualErrors.size())));
    }

    // Проверка имени интерфейса
    QVERIFY2(result.getNameInterface() == expectedInterface.getNameInterface(),
             qPrintable(QString("\nИмя интерфейса: ожидалось '%1', получено '%2'").arg(expectedInterface.getNameInterface()).arg(result.getNameInterface())));

    // Проверка модификатора
    QVERIFY2(result.getMod() == expectedInterface.getMod(),
             qPrintable(QString("\nМодификатор: ожидалось '%1', получено '%2'").arg(expectedInterface.getMod()).arg(result.getMod())));

    // Проверка extends
    QStringList resultExtends = result.getExtends();
    QStringList expectedExtends = expectedInterface.getExtends();
    QVERIFY2(resultExtends == expectedExtends,
             qPrintable(QString("\nРодительские интерфейсы: ожидалось %1, получено %2").arg(expectedExtends.join(", ")).arg(resultExtends.join(", "))));

    // Проверка полей
    QMap<QString, field> resultFields = result.getFields();
    QMap<QString, field> expectedFields = expectedInterface.getFields();
    QStringList resultFieldKeys = resultFields.keys();
    QStringList expectedFieldKeys = expectedFields.keys();

    QVERIFY2(resultFieldKeys == expectedFieldKeys,
             qPrintable(QString("\nКлючи полей: ожидалось %1, получено %2").arg(expectedFieldKeys.join(", ")).arg(resultFieldKeys.join(", "))));

    QMap<QString, field>::const_iterator fieldIt;
    for (fieldIt = expectedFields.constBegin(); fieldIt != expectedFields.constEnd(); ++fieldIt) {
        const QString key = fieldIt.key();
        const field expectedField = fieldIt.value();
        const field resultField = resultFields.value(key);

        QVERIFY2(resultField.getNameField() == expectedField.getNameField(),
                 qPrintable(QString("\nИмя поля '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedField.getNameField()).arg(resultField.getNameField())));
        QVERIFY2(resultField.getType() == expectedField.getType(),
                 qPrintable(QString("\nТип поля '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedField.getType()).arg(resultField.getType())));
        QVERIFY2(resultField.getMod() == expectedField.getMod(),
                 qPrintable(QString("\nМодификатор поля '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedField.getMod()).arg(resultField.getMod())));
        QVERIFY2(resultField.getIsStatic() == expectedField.getIsStatic(),
                 qPrintable(QString("\nСтатичность поля '%1': ожидалось %2, получено %3").arg(key).arg(expectedField.getIsStatic()).arg(resultField.getIsStatic())));
    }

    // Проверка методов
    QMap<QString, method> resultMethods = result.getMethods();
    QMap<QString, method> expectedMethods = expectedInterface.getMethods();
    QStringList resultMethodKeys = resultMethods.keys();
    QStringList expectedMethodKeys = expectedMethods.keys();

    QVERIFY2(resultMethodKeys == expectedMethodKeys,
             qPrintable(QString("\nКлючи методов: ожидалось %1, получено %2").arg(expectedMethodKeys.join(", ")).arg(resultMethodKeys.join(", "))));

    QMap<QString, method>::const_iterator methodIt;
    for (methodIt = expectedMethods.constBegin(); methodIt != expectedMethods.constEnd(); ++methodIt) {
        const QString key = methodIt.key();
        const method expectedMethod = methodIt.value();
        const method resultMethod = resultMethods.value(key);

        QVERIFY2(resultMethod.getNameMethod() == expectedMethod.getNameMethod(),
                 qPrintable(QString("\nИмя метода '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedMethod.getNameMethod()).arg(resultMethod.getNameMethod())));
        QVERIFY2(resultMethod.getReturnType() == expectedMethod.getReturnType(),
                 qPrintable(QString("\nТип возвращаемого значения метода '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedMethod.getReturnType()).arg(resultMethod.getReturnType())));
        QVERIFY2(resultMethod.getMod() == expectedMethod.getMod(),
                 qPrintable(QString("\nМодификатор метода '%1': ожидалось '%2', получено '%3'").arg(key).arg(expectedMethod.getMod()).arg(resultMethod.getMod())));
    }

    // Проверка вложенных интерфейсов
    QMap<QString, interface_info> resultInterfaces = result.getIncludeInterface();
    QMap<QString, interface_info> expectedInterfaces = expectedInterface.getIncludeInterface();
    QStringList resultInterfaceKeys = resultInterfaces.keys();
    QStringList expectedInterfaceKeys = expectedInterfaces.keys();

    QVERIFY2(resultInterfaceKeys == expectedInterfaceKeys,
             qPrintable(QString("\nКлючи вложенных интерфейсов: ожидалось %1, получено %2").arg(expectedInterfaceKeys.join(", ")).arg(resultInterfaceKeys.join(", "))));

    // Проверка вложенных классов
    QMap<QString, class_info> resultClasses = result.getIncludeClass();
    QMap<QString, class_info> expectedClasses = expectedInterface.getIncludeClass();
    QStringList resultClassKeys = resultClasses.keys();
    QStringList expectedClassKeys = expectedClasses.keys();

    QVERIFY2(resultClassKeys == expectedClassKeys,
             qPrintable(QString("\nКлючи вложенных классов: ожидалось %1, получено %2").arg(expectedClassKeys.join(", ")).arg(resultClassKeys.join(", "))));

    // Проверка импортов
    QStringList resultImports = result.getImport();
    QStringList expectedImports = expectedInterface.getImport();
    QVERIFY2(resultImports == expectedImports,
             qPrintable(QString("\nИмпорты: ожидалось %1, получено %2").arg(expectedImports.join(", ")).arg(resultImports.join(", "))));
}

