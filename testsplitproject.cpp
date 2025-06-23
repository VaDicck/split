#include "testsplitproject.h"

void testsplitproject::test_pack_data() {
    QTest::addColumn<QList<QStringList>>("project");
    QTest::addColumn<package_info>("inputRootPack");
    QTest::addColumn<package_info>("expectedRootPack");
    QTest::addColumn<QSet<error>>("expectedErrors");

    // Тест 1: Простой файл
    /*!
     * \test Тест 1: Простой файл
     * Проверяет разбор проекта с одним файлом, содержащим класс
     */
    QTest::newRow("single_file")
        << QList<QStringList>({
               {"package com.example;",
                "import ru.still;",
                "class Kol {",
                "    void method1() {}",
                "    int pole1;",
                "}"}
           })
        << package_info("root", {}) // inputRootPack
        << package_info("root", {{"com", package_info("com", {{"example", package_info("example", {}, {
        {"Kol", class_info("Kol", "default", "",
        {},             // implements
        {},             // constructors
        {{"pole1", field("pole1", "int", "default", false)}}, // fields
        {{method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},      // methods
        {},             // includesClasses
        {},             // includeInterface
        {"ru.still"},   // import
        false,          // isAbstract
        false           // isStatic
        )}
        }, {})}
        }, {}, {})}
        }, {}, {})
        << QSet<error>{}; // expectedErrors

    // Тест 2: Класс и интерфейс, и новый импорт
    /*!
     * \test Тест 2: Класс и интерфейс, и новый импорт
     * Проверяет разбор проекта с классом, интерфейсом и дополнительным импортом
     */
    QTest::newRow("class_and_interface_and_new_import")
        << QList<QStringList>({
               {"package com.example;",
                "import ru.still;",
                "class Kol {",
                "    void method1() {}",
                "    int pole1;",
                "}",
                "import lil.ress;",
                "interface Inter {",
                "    void swim();",
                "}"}
           })
        << package_info("root", {})
        << package_info("root", {{"com", package_info("com", {{"example", package_info("example", {}, {
            {"Kol", class_info("Kol", "default", "", {}, {},{{"pole1", field("pole1", "int", "default", false)}},
            {{method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},{}, {}, {"ru.still"}, false, false )}},
        {{"Inter", interface_info("Inter", "default", {}, {},
        {{method("swim", "void", false,false, "default", "swim()", {}, {})}}, {}, {}, {"ru.still", "lil.ress"})} })}}, {}, {})}}, {}, {})
        << QSet<error>{};

    // Тест 3: Смена текущего пакета
    /*!
     * \test Тест 3: Смена текущего пакета
     * Проверяет обработку смены пакета в середине файла
     */
    QTest::newRow("package_switch_in_file")
        << QList<QStringList>({
               {"package com.example;",
                "import ru.still;",
                "class kol {",
                "    void method1() {}",
                "    int pole1;",
                "}",
                "package spat.hochu;",
                "import lil.ress;",
                "import lil.non.*;",
                "interface inter {",
                "    void swim();",
                "}"}
           })
        << package_info("root", {})
        << package_info("root", {
                // Пакет com.example
                {"com", package_info("com", {
                    {"example", package_info("example", {}, {
                        {"kol", class_info(
                        "kol",          // nameClass
                        "default",             // mod
                        "",             // extend
                        QStringList(),  // implements
                        {}, // constructors
                        {{"pole1", field("pole1", "int", "default", false)}}, // fields
                        {{method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}}, // methods
                        QMap<QString, class_info>(),    // includesClasses
                        QMap<QString, interface_info>(), // includeInterface
                        {"ru.still"},   // import
                        false,          // isAbstract
                        false           // isStatic
                        )}
            }, QMap<QString, interface_info>())}}, QMap<QString, class_info>(), QMap<QString, interface_info>())},
            // Пакет spat.hochu
                        {"spat", package_info("spat", {
                            {"hochu", package_info("hochu",
                                QMap<QString, package_info>(),
                                QMap<QString, class_info>(),
                                { // interfaces
                                    {"inter", interface_info(
                                        "inter",    // nameInterface
                                        "default",         // mod
                                        QStringList(), // extends
                                        QMap<QString, field>(), // fields
                                        {{method("swim", "void", false,false, "default", "swim()", {}, {})}}, // methods
                                        QMap<QString, interface_info>(), // includeInterface
                                        QMap<QString, class_info>(),    // includeClass
                                        {"ru.still", "lil.ress", "lil.non.*"} // import
                                        )}})}}, QMap<QString, class_info>(), QMap<QString, interface_info>())} }, QMap<QString, class_info>(), QMap<QString, interface_info>())
        << QSet<error>{}; // expectedErrors
    // Тест 4: Несколько файлов
    /*!
     * \test Тест 4: Несколько файлов
     * Проверяет обработку нескольких файлов с разными пакетами
     */
    QTest::newRow("multiple_files_complex")
        << QList<QStringList>({
               // Файл 1
               {
                   "package com.example;",
                   "import ru.still;",
                   "class kol {",
                   "    void method1() {}",
                   "    int pole1;",
                   "}",
                   "package spat.hochu;",
                   "import lil.ress;",
                   "import lil.non.*;",
                   "interface inter {",
                   "    void swim();",
                   "}"
               },
               // Файл 2
               {
                   "package com.example.list;",
                   "import java;",
                   "class kolkiy {",
                   "    void method5() {}",
                   "    int pole4;",
                   "}"
               },
               // Файл 3
               {
                   "package len;",
                   "import ru.still;",
                   "interface inter23 {",
                   "    void methodInter() {}",
                   "    int pole1;",
                   "    bool poleInter;",
                   "}",
                   "interface inter {",
                   "    void swim();",
                   "}"
               }
           })
        << package_info("root", {})
        << package_info("root", {
            {"com", package_info("com",
                {{"example", package_info("example", {
                            {"list", package_info("list", {}, {
                                {"kolkiy", class_info("kolkiy", "default", "", {}, {},
                                {{"pole4", field("pole4", "int", "default", false)}},
                                {{ method("method5", "void", false,false, "default", "method5()", {"{}"}, {})}},
                                {}, {}, {"java"}, false, false)}}, {})}},
                            {{"kol", class_info("kol", "default", "", {}, {},{{"pole1", field("pole1", "int", "default", false)}},
                                {{method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},{}, {},
                                {"ru.still"}, false, false)}}, {})},}, {}, {})},
            {"spat", package_info("spat", {
                {"hochu", package_info("hochu", {}, {},
                                {{"inter", interface_info("inter", "default", {}, {},
                                    {{method("swim", "void", false,false, "default", "swim()", {}, {})}},
                                    {}, {}, {"ru.still", "lil.ress", "lil.non.*"})}})}}, {}, {})},
            {"len", package_info("len", {}, {}, {
                                {"inter23", interface_info("inter23", "default", {},
                                        {{"pole1", field("pole1", "int", "default", false)}, {"poleInter", field("poleInter", "bool", "default", false)}},
                                        {{method("methodInter", "void", false,false, "default", "methodInter()", {"{}"}, {})}},{}, {}, {"ru.still"})},
                                {"inter", interface_info("inter", "default", {}, {},
                                        {{method("swim", "void", false,false, "default", "swim()", {}, {})}},
                                        {}, {}, {"ru.still"})}})}}, {}, {})
        << QSet<error>{};

}



void testsplitproject::test_pack() {
    QFETCH(QList<QStringList>, project);
    QFETCH(package_info, inputRootPack);
    QFETCH(package_info, expectedRootPack);
    QFETCH(QSet<error>, expectedErrors);

    package_info actualRootPack = inputRootPack;
    QSet<error> actualErrors;

    // Вызов тестируемой функции
    splitProject(project, actualRootPack, actualErrors);

    QString msg = verifyPack(actualRootPack, expectedRootPack, "");
    QVERIFY2(msg.isEmpty(), qPrintable(msg));
    verifyErrors(actualErrors, expectedErrors);
}

