#ifndef TESTSKIPCONSTANT_H
#define TESTSKIPCONSTANT_H

#include <QObject>
#include <QTest>

class testSkipConstant : public QObject
{
    Q_OBJECT
private slots:
    void test_skip_const_data();
    void test_skip_const();
};

#endif // TESTSKIPCONSTANT_H
