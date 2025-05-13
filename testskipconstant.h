#ifndef TESTSKIPCONSTANT_H
#define TESTSKIPCONSTANT_H

#include <QObject>
#include <QTest>

class testSkipConstant : public QObject
{
    Q_OBJECT
private slots:
    void symbolConstat(); //Символьная константа
    void symbolConstantaShielding(); //Символьная константа экранирование
    void symbolConstantaShieldingOfShielding(); //Символьная константа экранирование экранированиия
    void stringConstant(); //Строковая константа
    void stringConstantTwoShields(); //Строковая константа два экранирования
    void stringConstantShieldingOfShielding(); //Строковая константа экранирования экранирования
    void notCompletedSymbolConstant(); //Не завершена символьная константа
    void notCompletedStringConstant(); //Не завершена строковая константа
    void multipleShielding(); //Множественное экранирование
    void symbolConstantIncludesStringConstant(); //Символьная константа включает строковую
    void stringConstantIncludesSimbolConstant(); //Строковая константа включает символьную
};

#endif // TESTSKIPCONSTANT_H
