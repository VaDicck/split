#ifndef TESTSPLITFIELD_H
#define TESTSPLITFIELD_H
#include <QObject>
#include <QTest>
#include "field.h"

Q_DECLARE_METATYPE(field)
typedef QMap<QString, field> fieldMap;
Q_DECLARE_METATYPE(fieldMap)

class testSplitField : public QObject
{
    Q_OBJECT
private slots:
    void add_data();
    void add();
};
#endif // TESTSPLITFIELD_H
