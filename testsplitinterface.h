#ifndef TESTSPLITINTERFACE_H
#define TESTSPLITINTERFACE_H

#include <QObject>
#include <QTest>
#include "interface_info.h"
#include "error.h"
#include "main.h"
#include "class_info.h"

class testsplitinterface : public testSplitBase
{
    Q_OBJECT
private slots:
    void test_split_data();
    void test_split();
};

#endif // TESTSPLITINTERFACE_H
