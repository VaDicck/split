#include "testsplitpackage.h"


testsplitpackage::testsplitpackage(QObject *parent) : QObject(parent) {}

//Тест №1. Пустой корневой пакет
void testsplitpackage::empty_root_package()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    package_info expectedPackage("root");
    expectedPackage.addChildPackage("com", package_info("com"));
    expectedPackage.getChildren()["com"].addChildPackage("example", package_info("example"));

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"], qPrintable("Не совпадает указатель"));
}

//Тест №2. Нет среди детей корневого
void testsplitpackage::no_among_the_children_root()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["ru"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    package_info expectedPackage = rootPackage;
    expectedPackage.addChildPackage("com", package_info("com"));
    expectedPackage.getChildren()["com"].addChildPackage("example", package_info("example"));

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"], qPrintable("Не совпадает указатель"));
}

//Тест №3. Такой пакет существует
void testsplitpackage::such_a_package_exists()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("com", package_info("com"));
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["com"].addChildPackage("example", package_info("example"));
    rootPackage.getChildren()["ru"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    package_info expectedPackage = rootPackage;

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"], qPrintable("Не совпадает указатель"));
}

//Тест №4. Большая вложенность пакета
void testsplitpackage::large_package_nesting()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", "less", "hell", "boom", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["ru"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    package_info expectedPackage = rootPackage;
    expectedPackage.addChildPackage("com", package_info("com"));
    expectedPackage.getChildren()["com"].addChildPackage("example", package_info("example"));
    expectedPackage.getChildren()["com"].getChildren()["example"].addChildPackage("less", package_info("less"));
    expectedPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].addChildPackage("hell", package_info("hell"));
    expectedPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom", package_info("boom"));

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"]
                            .getChildren()["less"].getChildren()["hell"].getChildren()["boom"], qPrintable("Не совпадает указатель"));
}

//Тест №5. Существующий пакет большой вложенности
void testsplitpackage::existing_package_heavily_nested()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", "less", "hell", "boom", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["oldes"].addChildPackage("news", package_info("news"));
    rootPackage.getChildren()["oldes"].addChildPackage("news1", package_info("news1"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    rootPackage.addChildPackage("com", package_info("com"));
    rootPackage.getChildren()["com"].addChildPackage("example", package_info("example"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("less", package_info("less"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["bigur"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["bigur"].addChildPackage("hell1", package_info("hell1"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom", package_info("boom"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom1", package_info("boom1"));

    package_info expectedPackage = rootPackage;

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"]
                            .getChildren()["less"].getChildren()["hell"].getChildren()["boom"], qPrintable("Не совпадает указатель"));
}

//Тест №6. Ссылка не на последний компонент пакета
void testsplitpackage::link_not_last_component_package()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "com", "example", "less", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["oldes"].addChildPackage("news", package_info("news"));
    rootPackage.getChildren()["oldes"].addChildPackage("news1", package_info("news1"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    rootPackage.addChildPackage("com", package_info("com"));
    rootPackage.getChildren()["com"].addChildPackage("example", package_info("example"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("less", package_info("less"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["bigur"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["bigur"].addChildPackage("hell1", package_info("hell1"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom", package_info("boom"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom1", package_info("boom1"));

    package_info expectedPackage = rootPackage;

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"], qPrintable("Не совпадает указатель"));
}

//Тест №7. Вставка в середину
void testsplitpackage::insert_in_middle()
{
    // Объявление пакета
    QStringList packageDeclaration = {"package", "ru", "grechka", "low", ";"};
    // Создаем пакет на вход и ожидаемый
    package_info rootPackage("root");
    rootPackage.addChildPackage("ru", package_info("ru"));
    rootPackage.addChildPackage("oldes", package_info("oldes"));
    rootPackage.getChildren()["oldes"].addChildPackage("news", package_info("news"));
    rootPackage.getChildren()["oldes"].addChildPackage("news1", package_info("news1"));
    rootPackage.getChildren()["ru"].addChildPackage("grechka", package_info("grechka"));
    rootPackage.addChildPackage("com", package_info("com"));
    rootPackage.getChildren()["com"].addChildPackage("example", package_info("example"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("less", package_info("less"));
    rootPackage.getChildren()["com"].getChildren()["example"].addChildPackage("bigur", package_info("bigur"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["bigur"].addChildPackage("hell", package_info("hell"));
    rootPackage.getChildren()["com"].getChildren()["example"].getChildren()["less"].getChildren()["hell"].addChildPackage("boom", package_info("boom"));

    package_info expectedPackage = rootPackage;
    expectedPackage.getChildren()["ru"].getChildren()["grechka"].addChildPackage("low", package_info("low"));

    package_info* result = splitPackage(packageDeclaration, rootPackage);
    QString diff = rootPackage.compare(expectedPackage);
    QVERIFY2(diff.isEmpty(), qPrintable("Расхождения пакетов:\n" + diff));
    QVERIFY2(result==&rootPackage.getChildren()["ru"].getChildren()["grechka"].getChildren()["low"], qPrintable("Не совпадает указатель"));
}
