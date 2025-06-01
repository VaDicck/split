#include "testsplitimport.h"

void testsplitimport::add_data() {
    QTest::addColumn<QStringList>("importDeclaration");
    QTest::addColumn<QString>("expectedResult");

    // Типичный импорт
    QTest::newRow("typical_import")
            << QStringList({{"import"}, {"java"}, {"util"}, {"List"}, {";"}})
            << QString("java.util.List");

    // Добавить все пакеты
    QTest::newRow("add_all_package")
            << QStringList({{"import"}, {"java"}, {"util"}, {"List"}, {"*"}, {";"}})
            << QString("java.util.List.*");
    // Один пакет
    QTest::newRow("one_package")
            << QStringList({{"import"}, {"java"}, {";"}})
            << QString("java");
}

void testsplitimport::add() {
    QFETCH(QStringList, importDeclaration);
    QFETCH(QString, expectedResult);

    QString result = splitImport(importDeclaration);
    QCOMPARE(result, expectedResult);
}
