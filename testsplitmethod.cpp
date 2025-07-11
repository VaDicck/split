#include "testsplitmethod.h"

void testsplitmethod::test_method_data() {
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("inputIndexString");
    QTest::addColumn<int>("inputIndexSimbol");
    QTest::addColumn<QString>("nameClass");
    QTest::addColumn<QStringList>("methodDeclaration");
    QTest::addColumn<method>("expectedMethod");
    QTest::addColumn<int>("expectedIndexString");
    QTest::addColumn<int>("expectedIndexSimbol");
    QTest::addColumn<QSet<error>>("expectedErrors");

    /*!
     * \test Тест 1: Объявление метода без реализации
     * Проверяет разбор объявления метода без тела
     */
    QTest::newRow("method_declaration_only")
        << QStringList({"public class test {", "void  functionA(int lego);", "int c =14; }"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 26
        << QSet<error>();

    /*!
     * \test Тест 2: Многострочная реализация
     * Проверяет разбор метода с многострочной реализацией
     */
    QTest::newRow("multiline_implementation")
        << QStringList({"public class test {", "void  functionA(int lego){", "int c =14; char f = 'a';", "}}"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{","int c =14; char f = 'a';", "}"}), {argument("lego", "int")}
               )
        << 3 << 1
        << QSet<error>();

    /*!
     * \test Тест 3: Однострочная реализация
     * Проверяет разбор метода с однострочной реализацией
     */
    QTest::newRow("singleline_implementation")
        << QStringList({"public class test {", "void  functionA(int lego){       int c =14; char f = 'a';}"})
        << 1 << 26
        << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{       int c =14; char f = 'a';}"}), {argument("lego", "int")}
               )
        << 1 << 58
        << QSet<error>();

    /*!
     * \test Тест 4: } в символьной константе
     * Проверяет игнорирование } в символьной константе
     */
    QTest::newRow("closing_brace_in_char")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = '}';", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = '}';","}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 5: } в строковой константе
     * Проверяет игнорирование } в строковой константе
     */
    QTest::newRow("closing_brace_in_string")
        << QStringList({"public class test {", "void functionA(int lego){", "int c; string f = \" ll }\";", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c; string f = \" ll }\";", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 6: } в многострочном комментарии
     * Проверяет игнорирование } в многострочном комментарии
     */
    QTest::newRow("closing_brace_in_multiline_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; /*char f =\"}\";*/", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; /*char f =\"}\";*/" , "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 7: } в однострочном комментарии
     * Проверяет игнорирование } в однострочном комментарии
     */
    QTest::newRow("closing_brace_in_line_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; //}", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{","int c =14; //}", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 8: Метод с несколькими аргументами
     * Проверяет разбор метода с несколькими параметрами
     */
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

    /*!
     * \test Тест 9: Абстрактный метод
     * Проверяет разбор абстрактного метода
     */
    QTest::newRow("abstract_method")
        << QStringList({"public class test {", "abstract void functionA(int lego);", "int c =14;", "}"})
        << 1 << 35 << "test"
        << QStringList({"abstract", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 35 << QSet<error>();

    /*!
     * \test Тест 10: Статический метод
     * Проверяет разбор статического метода
     */
    QTest::newRow("static_method")
        << QStringList({"public class test {", "static void functionA(int lego);", "int c =14; }"})
        << 1 << 33 << "test"
        << QStringList({"static", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", false, true, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 33 << QSet<error>();

    /*!
     * \test Тест 11: Абстрактный публичный метод
     * Проверяет разбор абстрактного публичного метода
     */
    QTest::newRow("abstract_public_method")
        << QStringList({"public class test {", "abstract public void functionA(int lego);", "int c =14; }"})
        << 1 << 42 << "test"
        << QStringList({"abstract", "public", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Public", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 42 << QSet<error>();

    /*!
     * \test Тест 12: Абстрактный приватный метод
     * Проверяет разбор абстрактного приватного метода
     */
    QTest::newRow("abstract_private_method")
        << QStringList({"public class test {", "abstract private void functionA(int lego);", "int c =14; }"})
        << 1 << 43 << "test"
        << QStringList({"abstract","private", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Private", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 43 << QSet<error>();

    /*!
     * \test Тест 13: Абстрактный защищенный метод
     * Проверяет разбор абстрактного защищенного метода
     */
    QTest::newRow("abstract_protected_method")
        << QStringList({"public class test {", "abstract protected void functionA(int lego);", "int c =14; }"})
        << 1 << 45 << "test"
        << QStringList({"abstract","protected", "void", "functionA", "(", "int", "lego", ")", ";"})
        << method(
               "functionA", "void", true, false, "Protected", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 45 << QSet<error>();

    /*!
     * \test Тест 14: Конструктор
     * Проверяет разбор конструктора класса
     */
    QTest::newRow("constructor_method")
        << QStringList({"public class test {", "test(int lego){", "this.name = lego;", "}}"})
        << 1 << 15 << "test"
        << QStringList({"test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "default", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 15: Публичный конструктор
     * Проверяет разбор публичного конструктора
     */
    QTest::newRow("public_constructor")
        << QStringList({"public class test {", "public test(int lego){", "this.name = lego;", "}}"})
        << 1 << 22 << "test"
        << QStringList({"public", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Public", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 16: Приватный конструктор
     * Проверяет разбор приватного конструктора
     */
    QTest::newRow("private_constructor")
        << QStringList({"public class test {", "private test(int lego){", "this.name = lego;", "}}"})
        << 1 << 23 << "test"
        << QStringList({"private", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Private", "test(int)",
               QStringList({"{", "this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 17: Защищенный конструктор
     * Проверяет разбор защищенного конструктора
     */
    QTest::newRow("protected_constructor")
        << QStringList({"public class test {", "protected test(int lego){", "this.name = lego;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"protected", "test", "(", "int", "lego", ")", "{"})
        << method(
               "", "", false, false, "Protected", "test(int)",
               QStringList({"{","this.name = lego;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 18: Возвращаемое значение - контейнер
     * Проверяет разбор метода с контейнерным типом возвращаемого значения
     */
    QTest::newRow("container_return_type")
        << QStringList({"public class test {", "Map<int, float> functionA(int lego){", "int c =14; char f = 'a';", "return Map;", "}}"})
        << 1 << 36 << "test"
        << QStringList({"Map", "<", "int", ",", "float", ">", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "Map<int, float>", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "return Map;", "}"}), {argument("lego", "int")}
               )
        << 4 << 1 << QSet<error>();

    /*!
     * \test Тест 19: Нестандартное возвращаемое значение
     * Проверяет разбор метода с пользовательским типом возвращаемого значения
     */
    QTest::newRow("custom_return_type")
        << QStringList({"public class test {", "classF funcB(int lego);", "int c =14;", "}"})
        << 1 << 23 << "test"
        << QStringList({"classF", "funcB", "(", "int", "lego", ")", ";"})
        << method(
               "funcB", "classF", false, false, "default", "funcB(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 23 << QSet<error>();

    /*!
     * \test Тест 20: Метод без аргументов
     * Проверяет разбор метода без параметров
     */
    QTest::newRow("no_arguments_method")
        << QStringList({"public class test {", "int funcB();", "int c =14;", "}"})
        << 1 << 12 << "test"
        << QStringList({"int", "funcB", "(", ")", ";"})
        << method(
               "funcB", "int", false, false, "default", "funcB()",
               QStringList(), QVector<argument>()
               )
        << 1 << 12 << QSet<error>();

    /*!
     * \test Тест 21: Контейнер в аргументах
     * Проверяет разбор метода с контейнерным типом параметра
     */
    QTest::newRow("container_argument")
        << QStringList({"public class test {", "void functionA(Map<int, float> lego){", "int c =14; char f = 'a';", "}}"})
        << 1 << 37 << "test"
        << QStringList({"void", "functionA", "(", "Map", "<", "int", ",", "float", ">", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(Map<int, float>)",
               QStringList({"{", "int c =14; char f = 'a';", "}"}), {argument("lego", "Map<int, float>")}
               )
        << 3 << 1 << QSet<error>();

    /*!
     * \test Тест 22: Две пары фигурных скобок
     * Проверяет обработку вложенных фигурных скобок
     */
    QTest::newRow("nested_braces")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==6) {", "int s =4; }", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "if(c==6) {", "int s =4; }", "}"}), {argument("lego", "int")}
               )
        << 5 << 1 << QSet<error>();

    /*!
     * \test Тест 23: Вложенность фигурных скобок
     * Проверяет обработку глубоко вложенных фигурных скобок
     */
    QTest::newRow("deeply_nested_braces")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==6) {", "if(c == 14) {", "bool f = true;", "}", "int s =4;", "}", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{","int c =14; char f = 'a';", "if(c==6) {", "if(c == 14) {", "bool f = true;", "}", "int s =4;", "}", "}"}), {argument("lego", "int")}
               )
        << 9 << 1 << QSet<error>();

    /*!
     * \test Тест 24: Не закрыт многострочный комментарий
     * Проверяет обработку незакрытого многострочного комментария
     */
    QTest::newRow("unclosed_multiline_comment")
        << QStringList({"public class test {", "void functionA(int lego){", "/* int c =14; char f = 'a';", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "/* int c =14; char f = 'a';", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedComment, 0,0,0,0,0,0,0,0,0,2)});

    /*!
     * \test Тест 25: Не закрыта символьная константа
     * Проверяет обработку незакрытой символьной константы
     */
    QTest::newRow("unclosed_char_constant")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedSingleQuotes, 0,0,0,0,0,0,0,0,0,2)});

    /*!
     * \test Тест 26: Не закрыта строковая константа
     * Проверяет обработку незакрытой строковой константы
     */
    QTest::newRow("unclosed_string_constant")
        << QStringList({"public class test {", "void functionA(int lego){", "string f = \"aloo;", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "string f = \"aloo;", "}"}), {argument("lego", "int")}
               )
        << 3 << 1 << QSet<error>({error(typeMistakes::notClosedDoubleQuotes, 0,0,0,0,0,0,0,0,0,2)});

    /*!
     * \test Тест 27: Нет закрывающей фигурной скобки
     * Проверяет обработку отсутствия закрывающей фигурной скобки
     */
    QTest::newRow("unclosed_brace")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';"})
        << 1 << 26 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList(), {argument("lego", "int")}
               )
        << 1 << 26 << QSet<error>({error(typeMistakes::noClosingFiguredScoop, 0,0,0,0,0,0,0,0,0,1)});

    /*!
     * \test Тест 28: Комплексная вложенность скобок
     * Проверяет обработку сложной вложенности фигурных скобок
     */
    QTest::newRow("complex_brace_nesting")
        << QStringList({"public class test {", "void functionA(int lego){", "int c =14; char f = 'a';", "if(c==14){", "if(c>5){/*{{*/}", "bool c = 1;}", "String str = \"{vloj}\";", "}}"})
        << 1 << 25 << "test"
        << QStringList({"void", "functionA", "(", "int", "lego", ")", "{"})
        << method(
               "functionA", "void", false, false, "default", "functionA(int)",
               QStringList({"{", "int c =14; char f = 'a';", "if(c==14){", "if(c>5){/*{{*/}", "bool c = 1;}", "String str = \"{vloj}\";", "}"}), {argument("lego", "int")}
               )
        << 7 << 1 << QSet<error>();

    /*!
     * \test Тест 29: Статический конструктор
     * Проверяет разбор статического блока инициализации
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
        << 2 << 8 << "SimpleClass"
        << QStringList({"static", "{"})
        << method("default", "static",QStringList({"{", "count = 10;", "}"}),{})
        << 4 << 1 << QSet<error>();
}

void testsplitmethod::test_method() {
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

    method result = splitMethod(code, actualIndexString, actualIndexSimbol, nameClass, methodDeclaration, actualErrors, 0);

    QCOMPARE(actualIndexString, expectedIndexString);
    QCOMPARE(actualIndexSimbol, expectedIndexSimbol);
    QString msg = verifyMethod(result, expectedMethod);
    QVERIFY2(msg.isEmpty(), qPrintable(msg));
    verifyErrors(actualErrors, expectedErrors);
}
