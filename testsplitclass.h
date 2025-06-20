#ifndef TESTSPLITCLASS_H
#define TESTSPLITCLASS_H

#include <QObject>
#include <QTest>
#include "class_info.h"
#include "error.h"
#include "constructor.h"
#include "main.h"

class testsplitclass : public testSplitBase
{
    Q_OBJECT
private slots:
    void test_class_data();
    void test_class();

};
#endif // TESTSPLITCLASS_H
