#ifndef TESTSPLITPROJECT_H
#define TESTSPLITPROJECT_H

#include <QObject>
#include <QTest>
#include <main.h>
#include <package_info.h>
#include "method.h"
#include "class_info.h"
#include "interface_info.h"


class testsplitproject : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};
#endif // TESTSPLITPROJECT_H
