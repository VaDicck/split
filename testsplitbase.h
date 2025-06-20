#ifndef TESTSPLITBASE_H
#define TESTSPLITBASE_H

#include <QObject>
#include "field.h"

class testSplitBase : public QObject
{
    Q_OBJECT
protected:
    void verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected);
};

#endif // TESTSPLITBASE_H
