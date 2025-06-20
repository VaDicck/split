#include "testsplitbase.h"
#include <QSet>
#include <QMap>
#include <QTest>
void testSplitBase::verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected){
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyActual;
    // Заполним
    foreach(const QString& key, actual.keys()){
        keyActual.insert(key);
    }
    QSet<QString> keyExpected;
    // Заполним
    foreach(const QString& key, expected.keys()){
        keyExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyActual&keyExpected){
        QVERIFY2(actual.value(key)== expected.value(key), qPrintable(QString("\nСодержимое поля (%1) не сходится!\n"
                                                                              "Имя полученного (%2)\tожидаемого (%3)\n"
                                                                              "Тип поля получился (%4)\tожидался (%5)\n"
                                                                              "Модификатор поля получился (%6)\tожидался (%7)\n"
                                                                              "Статическое ли поле получилось (%8)\tожидалось (%9)\t")
                                                                          .arg(key).arg(actual.value(key).getNameField()).arg(expected.value(key).getNameField()).arg(actual.value(key).getType())
                                                                          .arg(expected.value(key).getType()).arg(actual.value(key).getMod()).arg(expected.value(key).getMod()).arg(actual.value(key).getIsStatic()).arg(expected.value(key).getIsStatic())));
    }
    // Если есть лишние фактические
    if(!((keyActual-keyExpected).isEmpty())){
        foreach(const QString& key, keyActual){
            QVERIFY2(actual.value(key)== expected.value(key), qPrintable(QString("\nПоля (%1) нет в ожидаемом\n"
                                                                                  "Имя поля (%2)\n"
                                                                                  "Тип поля (%3)\n"
                                                                                  "Модификатор поля (%4)\n"
                                                                                  "Статическое ли поле (%5)\t")
                                                                              .arg(key).arg(actual.value(key).getNameField()).arg(actual.value(key).getType())
                                                                              .arg(actual.value(key).getMod()).arg(actual.value(key).getIsStatic())));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyExpected-keyActual).isEmpty())){
        foreach(const QString& key, keyExpected){
            QVERIFY2(actual.value(key)== expected.value(key), qPrintable(QString("\nПоля (%1) нет в фактическом\n"
                                                                                  "Имя поля (%2)\n"
                                                                                  "Тип поля (%3)\n"
                                                                                  "Модификатор поля (%4)\n"
                                                                                  "Статическое ли поле (%5)\t")
                                                                              .arg(key).arg(expected.value(key).getNameField()).arg(expected.value(key).getType())
                                                                              .arg(expected.value(key).getMod()).arg(expected.value(key).getIsStatic())));
        }
    }
}
