#ifndef TESTSPLITIMPORT_H
#define TESTSPLITIMPORT_H

#include <QObject>
#include <QTest>
#include <main.h>


class testsplitimport : public QObject
{
    Q_OBJECT
private slots:
    void test_split_import_data();
    void test_split_import();
};
#endif // TESTSPLITIMPORT_H
