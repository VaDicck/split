#ifndef TESTSPLITMETHOD_H
#define TESTSPLITMETHOD_H

#include <QObject>
#include <QTest>
#include <QSet>
#include "method.h"
#include "main.h"
#include "error.h"

class testsplitmethod : public testSplitBase
{
    Q_OBJECT
private slots:
    void test_method_data();
    void test_method();
};

#endif // TESTSPLITMETHOD_H
