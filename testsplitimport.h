#ifndef TESTSPLITIMPORT_H
#define TESTSPLITIMPORT_H

#include <QObject>
#include <QTest>
#include <main.h>


class testsplitimport : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};
#endif // TESTSPLITIMPORT_H
