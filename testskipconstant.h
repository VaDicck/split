#ifndef TESTSKIPCONSTANT_H
#define TESTSKIPCONSTANT_H

#include <QObject>
#include <QTest>

class testSkipConstant : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};

#endif // TESTSKIPCONSTANT_H
