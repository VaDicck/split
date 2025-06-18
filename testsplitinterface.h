#ifndef TESTSPLITINTERFACE_H
#define TESTSPLITINTERFACE_H

#include <QObject>
#include <QTest>
#include "interface_info.h"
#include "error.h"
#include "main.h"
#include "class_info.h"

class testsplitinterface : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};

#endif // TESTSPLITINTERFACE_H
