#include "testsplitimport.h"

void testsplitimport::test_split_import_data() {
    QTest::addColumn<QStringList>("importDeclaration");
    QTest::addColumn<QString>("expectedResult");

    /*!
     * \test Тест 1: Типичный импорт
     * Проверяет разбор стандартного импорта пакета
     */
    QTest::newRow("typical_import")
        << QStringList({{"import"}, {"java"}, {"util"}, {"List"}, {";"}})
        << QString("java.util.List");

    /*!
     * \test Тест 2: Импорт всех пакетов
     * Проверяет разбор импорта с (*)
     */
    QTest::newRow("add_all_package")
        << QStringList({{"import"}, {"java"}, {"util"}, {"List"}, {"*"}, {";"}})
        << QString("java.util.List.*");

    /*!
     * \test Тест 3: Один пакет
     * Проверяет разбор импорта одного пакета
     */
    QTest::newRow("one_package")
        << QStringList({{"import"}, {"java"}, {";"}})
        << QString("java");
}

void testsplitimport::test_split_import() {
    QFETCH(QStringList, importDeclaration);
    QFETCH(QString, expectedResult);

    QString result = splitImport(importDeclaration);
    QCOMPARE(result, expectedResult);
}
