#ifndef TESTSPLITMETHOD_H
#define TESTSPLITMETHOD_H

#include <QObject>
#include <QTest>
#include <QSet>
#include "method.h"
#include "main.h"
#include "error.h"


class testsplitmethod : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};

#endif // TESTSPLITMETHOD_H
