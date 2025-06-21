#ifndef TESTSKIPMULTIPLECOMMENT_H
#define TESTSKIPMULTIPLECOMMENT_H

#include <QObject>
#include <QTest>

class testSkipMultipleComment : public QObject
{
    Q_OBJECT
private slots:
    void test_skip_comm_data();
    void test_skip_comm();
};

#endif // TESTSKIPMULTIPLECOMMENT_H
