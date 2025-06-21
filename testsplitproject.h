#ifndef TESTSPLITPROJECT_H
#define TESTSPLITPROJECT_H

#include <QObject>
#include <QTest>
#include <main.h>
#include <package_info.h>
#include "method.h"
#include "class_info.h"
#include "interface_info.h"


class testsplitproject : public testSplitBase
{
    Q_OBJECT
private slots:
    void test_pack_data();
    void test_pack();
};
#endif // TESTSPLITPROJECT_H
