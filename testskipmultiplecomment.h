#ifndef TESTSKIPMULTIPLECOMMENT_H
#define TESTSKIPMULTIPLECOMMENT_H

#include <QObject>
#include <QTest>

class testSkipMultipleComment : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};

#endif // TESTSKIPMULTIPLECOMMENT_H
