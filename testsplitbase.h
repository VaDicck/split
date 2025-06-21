#ifndef TESTSPLITBASE_H
#define TESTSPLITBASE_H

#include <QObject>
#include "error.h"
#include "argument.h"
#include "field.h"
#include "class_info.h"
#include "interface_info.h"
#include "method.h"
#include "package_info.h"


class testSplitBase : public QObject
{
    Q_OBJECT
protected:
    QString verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected);
    void verifyErrors(const QSet<error>&actual, const QSet<error>&expected);
    QString verifyConstructor(const constructor& actual,const constructor& expected);
    QString verifyMethod(const method& actual,const method& expected);
    QString verifyClass(const class_info& actual,const class_info& expected);
    QString verifyInterface(const interface_info& actual,const interface_info& expected);
    QString verifyPack(const package_info& actual,const package_info& expected, QString pathPack);
};

#endif // TESTSPLITBASE_H
