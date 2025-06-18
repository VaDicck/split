#ifndef TESTSPLITCLASS_H
#define TESTSPLITCLASS_H

#include <QObject>
#include <QTest>
#include "class_info.h"
#include "error.h"
#include "constructor.h"
#include "main.h"

class testsplitclass : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();

};
#endif // TESTSPLITCLASS_H
