#ifndef TESTSPLITBASE_H
#define TESTSPLITBASE_H

#include <QObject>
#include "error.h"
#include "argument.h"
#include "field.h"
#include "class_info.h"
#include "interface_info.h"
#include "method.h"


class testSplitBase : public QObject
{
    Q_OBJECT
protected:
    void verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected);
    void verifyErrors(const QSet<error>&actual, const QSet<error>&expected);
    void verifyConstructor(const constructor& actual,const constructor& expected);
    void verifyMethod(const method& actual,const method& expected);
    void verifyClass(const class_info& actual,const class_info& expected);
    void verifyInterface(const interface_info& actual,const interface_info& expected);
};

#endif // TESTSPLITBASE_H
