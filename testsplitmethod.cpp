#include "testsplitmethod.h"

void testsplitmethod::add_data() {
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("inputIndexString");
    QTest::addColumn<int>("inputIndexSimbol");
    QTest::addColumn<QString>("nameClass");
    QTest::addColumn<QStringList>("methodDeclaration");
    QTest::addColumn<method>("expectedMethod");
    QTest::addColumn<int>("expectedIndexString");
    QTest::addColumn<int>("expectedIndexSimbol");
    QTest::addColumn<QSet<error>>("expectedErrors");

    // Тест 1: Объявление метода без реализации
    QTest::newRow("method_declaration_only")
        << QStringList({"public class test {", "void  functionA(int lego);", "int c =14; }"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA",     // nameMethod
               "void",          // returnType
               false,           // isAbstract
               false,           // isStatic
               "default",       // mod
               "functionA(int)",// filename
               QStringList(),   // code (пустой)
               {argument("lego", "int")} // arguments (name, type)
               )
        << 1 << 26
        << QSet<error>();

    // Тест 2: Многострочная реализация
    QTest::newRow("multiline_implementation")
        << QStringList({"public class test {", "void  functionA(int lego){", "int c =14; char f = 'a';", "}}"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA",
               "void",
               false,
               false,
               "default",
               "functionA(int)",
               QStringList({"{","int c =14; char f = 'a';", "}"}),
               {argument("lego", "int")}
               )
        << 3 << 1
        << QSet<error>();

    // Тест 3: Однострочная реализация
    QTest::newRow("singleline_implementation")
        << QStringList({"public class test {", "void  functionA(int lego){       int c =14; char f = 'a';}"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA",
               "void",
               false,
               false,
               "default",
               "functionA(int)",
               QStringList({"{       int c =14; char f = 'a';}"}),
               {argument("lego", "int")}
               )
        << 1 << 58
        << QSet<error>();

    // Тест 4: } в символьной константе
    QTest::newRow("closing_brace_in_char")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = '}';", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = '}';","}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 5: } в строковой константе
    QTest::newRow("closing_brace_in_string")
        << QStringList({"public class test {", "void functionA(int lego){", "int c; string f = \" ll }\";", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c; string f = \" ll }\";", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 6: } в многострочном комментарии
    QTest::newRow("closing_brace_in_multiline_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; /*char f =\"}\";*/", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; /*char f =\"}\";*/" , "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 7: } в однострочном комментарии
    QTest::newRow("closing_brace_in_line_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; //}", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{","int c =14; //}", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 8: Метод с несколькими аргументами
    QTest::newRow("multiple_arguments")
        << QStringList({"public class test {", "void functionA(int lego, String cel, char vat);", "int c =14; }"})
        << 1 << 49 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ",", "String", "cel", ",", "char", "vat", ")", ";"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int, String, char)",
               QStringList(),
               {argument("lego", "int"), argument("cel", "String"), argument("vat", "char")}
               )
        << 1 << 49 << QSet<error>();

    // Тест 9: Абстрактный метод
    QTest::newRow("abstract_method")
        << QStringList({"public class test {", "abstract void functionA(int lego);", "int c =14;", "}"})
        << 1 << 35 << "test"
        << QStringList({"abstract", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 35 << QSet<error>();

    // Тест 10: Статический метод
    QTest::newRow("static_method")
        << QStringList({"public class test {", "static void functionA(int lego);", "int c =14; }"})
        << 1 << 33 << "test"
        << QStringList({"static", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", false, true, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 33 << QSet<error>();

    // Тест 11: Абстрактный публичный метод
    QTest::newRow("abstract_public_method")
        << QStringList({"public class test {", "abstract public void functionA(int lego);", "int c =14; }"})
        << 1 << 42 << "test"
        << QStringList({"abstract", "public", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Public", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 42 << QSet<error>();

    // Тест 12: Абстрактный приватный метод
    QTest::newRow("abstract_private_method")
        << QStringList({"public class test {", "abstract private void functionA(int lego);", "int c =14; }"})
        << 1 << 43 << "test"
        << QStringList({"abstract","private", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Private", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 43 << QSet<error>();

    // Тест 13: Абстрактный защищенный метод
    QTest::newRow("abstract_protected_method")
        << QStringList({"public class test {", "abstract protected void functionA(int lego);", "int c =14; }"})
        << 1 << 45 << "test"
        << QStringList({"abstract","protected", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Protected", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 45 << QSet<error>();

    // Тест 14: Конструктор
    QTest::newRow("constructor_method")
        << QStringList({"public class test {", "test(int lego){", "this.name = lego;", "}}"})
        << 1 << 15 << "test"
        << QStringList({"test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "default", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 15: Публичный конструктор
    QTest::newRow("public_constructor")
        << QStringList({"public class test {", "public test(int lego){", "this.name = lego;", "}}"})
        << 1 << 22 << "test"
        << QStringList({"public", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Public", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 16: Приватный конструктор
    QTest::newRow("private_constructor")
        << QStringList({"public class test {", "private test(int lego){", "this.name = lego;", "}}"})
        << 1 << 23 << "test"
        << QStringList({"private", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Private", "test(int)",
               QStringList({"{", "this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 17: Защищенный конструктор
    QTest::newRow("protected_constructor")
        << QStringList({"public class test {", "protected test(int lego){", "this.name = lego;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"protected", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Protected", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 18: Возвращаемое значение - контейнер
    QTest::newRow("container_return_type")
        << QStringList({"public class test {", "Map<int, float> functionA(int lego){", "int c =14; char f = 'a';", "return Map;", "}}"})
        << 1 << 36 << "test"
        << QStringList({"Map", "<", "int", ",", "float", ">", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "Map<int, float>", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "return Map;", "}"}), {argument("lego", "int")}
               )
        << 4 << 1 << QSet<error>();

    // Тест 19: Нестандартное возвращаемое значение
    QTest::newRow("custom_return_type")
        << QStringList({"public class test {", "classF funcB(int lego);", "int c =14;", "}"})
        << 1 << 23 << "test"
        << QStringList({"classF", "funcB", "(", "int", "lego", ")", ";"})
        << method(
               "funcB", "classF", false, false, "default", "funcB(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 23 << QSet<error>();

    // Тест 20: Метод без аргументов
    QTest::newRow("no_arguments_method")
        << QStringList({"public class test {", "int funcB();", "int c =14;", "}"})
        << 1 << 12 << "test"
        << QStringList({"int", "funcB", "(", ")", ";"})
        << method(
               "funcB", "int", false, false, "default", "funcB()",
               QStringList(), QVector<argument>()
               )
        << 1 << 12 << QSet<error>();

    //Тест 21: Контейнер в аргументах
    QTest::newRow("container_argument")
        << QStringList({"public class test {", "void functionA(Map<int, float> lego){", "int c =14; char f = 'a';", "}}"})
        << 1 << 37 << "test"
        << QStringList({"void", "functionA", "(", "Map", "<", "int", ",", "float", ">", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(Map<int, float>)",
               QStringList({"{", "int c =14; char f = 'a';", "}"}), {argument("lego", "Map<int, float>")}
               )
        << 3 << 1 << QSet<error>();

    // Тест 22: Две пары фигурных скобок
    QTest::newRow("nested_braces")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==6) {", "int s =4; }", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "if(c==6) {", "int s =4; }", "}"}), {argument("lego", "int")}
               )
        << 5 << 1 << QSet<error>();

    // Тест 23: Вложенность фигурных скобок
    QTest::newRow("deeply_nested_braces")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==6) {", "if(c == 14) {", "bool f = true;", "}", "int s =4;", "}", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{","int c =14; char f = 'a';", "if(c==6) {", "if(c == 14) {", "bool f = true;", "}", "int s =4;", "}", "}"}), {argument("lego", "int")}
               )
        << 9 << 1 << QSet<error>();

    // Тест 24: Не закрыт многострочный комментарий
    QTest::newRow("unclosed_multiline_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "/* int c =14; char f = 'a';", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "/* int c =14; char f = 'a';", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedComment, 0,0,0,0,0,0,0,0,0,2)});

    // Тест 25: Не закрыта символьная константа
    QTest::newRow("unclosed_char_constant")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedSingleQuotes, 0,0,0,0,0,0,0,0,0,2)});

    // Тест 26: Не закрыта строковая константа
    QTest::newRow("unclosed_string_constant")
        << QStringList({"public class test {", "void functionA(int lego){", "string f = \"aloo;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "string f = \"aloo;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedDoubleQuotes, 0,0,0,0,0,0,0,0,0,2)});

    // Тест 27: Нет закрывающей фигурной скобки
    QTest::newRow("unclosed_brace")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';"})
        << 1 << 26 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 26 << QSet<error>({error(typeMistakes::noClosingFiguredScoop, 0,0,0,0,0,0,0,0,0,1)});

    // Тест 28: Комплексная вложенность скобок
    QTest::newRow("complex_brace_nesting")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==14){", "if(c>5){/*{{*/}", "bool c = 1;}", "String str = \"{vloj}\";", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "if(c==14){", "if(c>5){/*{{*/}", "bool c = 1;}", "String str = \"{vloj}\";", "}"}), {argument("lego", "int")}
               )
        << 7 << 1 << QSet<error>();

    // Тест 29: Статический конструктор
    QTest::newRow("simple_static_initializer")
        << QStringList({
               "class SimpleClass {",
               "static int count;",
               "static {",
               "count = 10;",
               "}",
               "}"
           })
        << 2 << 8 << "SimpleClass"
        << QStringList({"static", "{"})
        << method("default", "static",QStringList({"{", "count = 10;", "}"}),{})
        << 4 << 1 << QSet<error>();


}

void testsplitmethod::add() {
    QFETCH(QStringList, code);
    QFETCH(int, inputIndexString);
    QFETCH(int, inputIndexSimbol);
    QFETCH(QString, nameClass);
    QFETCH(QStringList, methodDeclaration);
    QFETCH(method, expectedMethod);
    QFETCH(int, expectedIndexString);
    QFETCH(int, expectedIndexSimbol);
    QFETCH(QSet<error>, expectedErrors);

    int actualIndexString = inputIndexString;
    int actualIndexSimbol = inputIndexSimbol;
    QSet<error> actualErrors;

    // Вызов
    method result = splitMethod(code, actualIndexString, actualIndexSimbol, nameClass, methodDeclaration, actualErrors);

    // Проверка текущей строки и символа
    QCOMPARE(actualIndexString, expectedIndexString);
    QCOMPARE(actualIndexSimbol, expectedIndexSimbol);

    // Проверка имени метода
    QVERIFY2(result.getNameMethod() == expectedMethod.getNameMethod(), qPrintable(QString("\nИмя метода: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getNameMethod()).arg(result.getNameMethod())));

    // Проверка типа возращаемого значения
    QVERIFY2(result.getReturnType() == expectedMethod.getReturnType(),qPrintable(QString("\nТип возвращаемого значения: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getReturnType()).arg(result.getReturnType())));

    // Проверка абстрактный ли метод
    QVERIFY2(result.getIsAbstract() == expectedMethod.getIsAbstract(),qPrintable(QString("\nАбстрактный ли метод: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getIsAbstract()).arg(result.getIsAbstract())));

    // Проверка статистический ли метод
    QVERIFY2(result.getIsStatic() == expectedMethod.getIsStatic(),qPrintable(QString("\nСтатический ли метод: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getIsStatic()).arg(result.getIsStatic())));

    // Проверка модификатора доступа метода
    QVERIFY2(result.getMod() == expectedMethod.getMod(),qPrintable(QString("\nМодификатор доступа: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getMod()).arg(result.getMod())));

    // Проверка имени файла метода
    QVERIFY2(result.getFilename() == expectedMethod.getFilename(),qPrintable(QString("\nИмя файла: ожидалось (%1), получено (%2)\n").arg(expectedMethod.getFilename()).arg(result.getFilename())));

    //Проверка кода метода
    QVERIFY2(result.getCode() == expectedMethod.getCode(),qPrintable(QString("\nКод метода: ожидалось \n%1\nполучено \n%2\n").arg(expectedMethod.getCode().join("\n")).arg(result.getCode().join("\n"))));

    // Проверка аргументов
    QVector<argument> actualArgs = result.getArguments();
    QVector<argument> expectedArgs = expectedMethod.getArguments();

    QVERIFY2(actualArgs.size() == expectedArgs.size(),qPrintable(QString("\nКоличество аргументов: ожидалось (%1), получено (%2)\n").arg(expectedArgs.size()).arg(actualArgs.size())));

    for (int i = 0; i < qMin(actualArgs.size(), expectedArgs.size()); ++i) {
        QVERIFY2(actualArgs[i].getName() == expectedArgs[i].getName(),qPrintable(QString("\nИмя аргумента: ожидалось (%1), получено (%2)\n").arg(expectedArgs[i].getName()).arg(actualArgs[i].getName())));

        QVERIFY2(actualArgs[i].getType() == expectedArgs[i].getType(),qPrintable(QString("\nТип аргумента %1: ожидалось (%2), получено (%3)\n").arg(i).arg(expectedArgs[i].getType()).arg(actualArgs[i].getType())));
    }

    // Проверка ошибок
    if (actualErrors != expectedErrors) {
        QStringList messages;

        // Находим ошибки, которые есть в expected, но нет в actual
        QSet<error> missingErrors = expectedErrors - actualErrors;
        for (const error& err : missingErrors) {
            messages << QString("Отсутствует ожидаемая ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в actual, но нет в expected
        QSet<error> unexpectedErrors = actualErrors - expectedErrors;
        for (const error& err : unexpectedErrors) {
            messages << QString("Обнаружена неожиданная ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в обоих наборах, но различаются по полям
        QSet<error> commonErrors = actualErrors & expectedErrors;
        for (const error& err : commonErrors) {
            const error& expectedErr = *expectedErrors.find(err);
            if (!(err == expectedErr)) {
                QStringList diffFields;
                if (err.typeMistake != expectedErr.typeMistake) diffFields << "тип ошибки";
                if (err.fileNumber != expectedErr.fileNumber) diffFields << "номер файла";
                if (err.numberStr != expectedErr.numberStr) diffFields << "номер строки";
                // Добавьте другие поля по аналогии

                messages << QString("Ошибка %1 отличается по полям: %2")
                                .arg(int(err.typeMistake))
                                .arg(diffFields.join(", "));
            }
        }

        QVERIFY2(false,qPrintable(QString("Наборы ошибок не совпадают:\n%1\nОжидалось %2 ошибок, получено %3 ошибок").arg(messages.join("\n")).arg(expectedErrors.size()).arg(actualErrors.size())));
    }
}


