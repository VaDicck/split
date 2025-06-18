#include "testsplitproject.h"

void testsplitproject::add_data() {
    QTest::addColumn<QList<QStringList>>("project");
    QTest::addColumn<package_info>("inputRootPack");
    QTest::addColumn<package_info>("expectedRootPack");
    QTest::addColumn<QSet<error>>("expectedErrors");

    // Тест 1: Простой класс
    QTest::newRow("single_class")
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
        {{"method1", method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},      // methods
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
            {{"method1", method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},{}, {}, {"ru.still"}, false, false )}},
        {{"Inter", interface_info("Inter", "default", {}, {},
        {{"swim", method("swim", "void", false,false, "default", "swim()", {}, {})}}, {}, {}, {"ru.still", "lil.ress"})} })}}, {}, {})}}, {}, {})
        << QSet<error>{};

    // Тест 3: Смена текущего пакета
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
                        QList<constructor>(), // constructors
                        {{"pole1", field("pole1", "int", "default", false)}}, // fields
                        {{"method1", method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}}, // methods
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
                                        {{"swim", method("swim", "void", false,false, "default", "swim()", {}, {})}}, // methods
                                        QMap<QString, interface_info>(), // includeInterface
                                        QMap<QString, class_info>(),    // includeClass
                                        {"ru.still", "lil.ress", "lil.non.*"} // import
                                        )}})}}, QMap<QString, class_info>(), QMap<QString, interface_info>())} }, QMap<QString, class_info>(), QMap<QString, interface_info>())
        << QSet<error>{}; // expectedErrors
    // Тест 4: Несколько файлов
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
        << package_info("root", {{"com", package_info("com", {{"example", package_info("example", {},
            {{"kol", class_info("kol", "default", "", {}, {},{{"pole1", field("pole1", "int", "default", false)}},
                {{"method1", method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},{}, {}, {"ru.still"}, false, false)}}, {})},
{"example", package_info("example", {{"list", package_info("list", {}, {
{"kolkiy", class_info(
                                                      "kolkiy", "default", "", {}, {},
                                                     {{"pole4", field("pole4", "int", "default", false)}},
                                                    {{"method5", method("method5", "void", false,false, "default", "method5()", {"{}"}, {})}},
                                                    {}, {}, {"java"}, false, false
                                                    )}}, {})}}, {}, {})}}, {}, {})},
{"spat", package_info("spat", {
{"hochu", package_info("hochu", {}, {}, {
{"inter", interface_info("inter", "default", {}, {},{{"swim", method("swim", "void", false,false, "default", "swim()", {}, {})}},
{}, {}, {"ru.still", "lil.ress", "lil.non.*"}
)}
})}
 }, {}, {})},
                 {"len", package_info("len", {}, {}, {
{"inter23", interface_info("inter23", "default", {}, {{"pole1", field("pole1", "int", "default", false)}, {"poleInter", field("poleInter", "bool", "default", false)}},
{{"methodInter", method("method1", "void", false,false, "default", "method1()", {"{}"}, {})}},{}, {}, {"ru.still"})},
{"inter", interface_info(
"inter", "default", {}, {},
{{"swim", method("swim", "void", false,false, "default", "swim()", {}, {})}},
{}, {}, {"ru.still"}
)}
 })}
}, {}, {})
        << QSet<error>{};

}

void verifyPackagesContent(const package_info& actual, const package_info& expected) {
    // Проверка классов в текущем пакете
    const QMap<QString, class_info>& actualClasses = actual.getIncludesClasses();
    const QMap<QString, class_info>& expectedClasses = expected.getIncludesClasses();

    QVERIFY2(actualClasses.size() == expectedClasses.size(),
             qPrintable(QString("В пакете %1: количество классов не совпадает (ожидалось %2, получено %3)").arg(actual.getNamePackage()).arg(expectedClasses.size()).arg(actualClasses.size())));

    for (QMap<QString, class_info>::const_iterator it = expectedClasses.constBegin();
         it != expectedClasses.constEnd(); ++it) {
        const QString& className = it.key();
        QVERIFY2(actualClasses.contains(className),
                 qPrintable(QString("В пакете %1: отсутствует ожидаемый класс %2").arg(actual.getNamePackage()).arg(className)));
    }

    // Проверка интерфейсов в текущем пакете
    const QMap<QString, interface_info>& actualInterfaces = actual.getIncludesInterfaces();
    const QMap<QString, interface_info>& expectedInterfaces = expected.getIncludesInterfaces();

    QVERIFY2(actualInterfaces.size() == expectedInterfaces.size(),
             qPrintable(QString("В пакете %1: количество интерфейсов не совпадает (ожидалось %2, получено %3)").arg(actual.getNamePackage()).arg(expectedInterfaces.size()).arg(actualInterfaces.size())));

    for (QMap<QString, interface_info>::const_iterator it = expectedInterfaces.constBegin();
         it != expectedInterfaces.constEnd(); ++it) {
        const QString& interfaceName = it.key();
        QVERIFY2(actualInterfaces.contains(interfaceName),
                 qPrintable(QString("В пакете %1: отсутствует ожидаемый интерфейс %2").arg(actual.getNamePackage()).arg(interfaceName)));
    }

    // Рекурсивная проверка дочерних пакетов
    const QMap<QString, package_info>& actualChildren = actual.getChildren();
    const QMap<QString, package_info>& expectedChildren = expected.getChildren();

    for (QMap<QString, package_info>::const_iterator it = expectedChildren.constBegin();
         it != expectedChildren.constEnd(); ++it) {
        const QString& packageName = it.key();
        QVERIFY2(actualChildren.contains(packageName),
                 qPrintable(QString("Отсутствует ожидаемый пакет %1.%2").arg(actual.getNamePackage()).arg(packageName)));

        verifyPackagesContent(actualChildren.value(packageName), it.value());
    }
}

void testsplitproject::add() {
    QFETCH(QList<QStringList>, project);
    QFETCH(package_info, inputRootPack);
    QFETCH(package_info, expectedRootPack);
    QFETCH(QSet<error>, expectedErrors);

    package_info actualRootPack = inputRootPack;
    QSet<error> actualErrors;

    // Вызов тестируемой функции
    splitProject(project, actualRootPack, actualErrors);

    // Проверка ошибок
    if (actualErrors != expectedErrors) {
        QStringList messages;

        // Находим ошибки, которые есть в expected, но нет в actual
        QSet<error> missingErrors = expectedErrors - actualErrors;
        for (QSet<error>::const_iterator it = missingErrors.constBegin(); it != missingErrors.constEnd(); ++it) {
            const error& err = *it;
            messages << QString("Отсутствует ожидаемая ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в actual, но нет в expected
        QSet<error> unexpectedErrors = actualErrors - expectedErrors;
        for (QSet<error>::const_iterator it = unexpectedErrors.constBegin(); it != unexpectedErrors.constEnd(); ++it) {
            const error& err = *it;
            messages << QString("Обнаружена неожиданная ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в обоих наборах, но различаются по полям
        QSet<error> commonErrors = actualErrors & expectedErrors;
        for (QSet<error>::const_iterator it = commonErrors.constBegin(); it != commonErrors.constEnd(); ++it) {
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

    // Рекурсивная проверка структуры пакетов
    QString diff = actualRootPack.compare(expectedRootPack);
    QVERIFY2(diff.isEmpty(),
             qPrintable(QString("Структура пакетов не совпадает:\n%1").arg(diff)));

    // Рекурсивная проверка классов и интерфейсов во всех пакетах
    verifyPackagesContent(actualRootPack, expectedRootPack);
    // Проверка полного совпадения
    QCOMPARE(actualRootPack, expectedRootPack);
}

