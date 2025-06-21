#ifndef TESTSPLITFIELD_H
#define TESTSPLITFIELD_H
#include <QObject>
#include <QTest>
#include "field.h"
#include "testsplitbase.h"


Q_DECLARE_METATYPE(field)
typedef QMap<QString, field> fieldMap;
Q_DECLARE_METATYPE(fieldMap)

class testSplitField : public testSplitBase
{
    Q_OBJECT
private slots:
    void test_field_data();
    void test_field();
};
#endif // TESTSPLITFIELD_H
