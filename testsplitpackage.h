#ifndef TESTSPLITPACKAGE_H
#define TESTSPLITPACKAGE_H
#include <QObject>
#include <QTest>
#include "package_info.h"
#include <main.h>


class testsplitpackage : public QObject
{
    Q_OBJECT
public:
    explicit testsplitpackage(QObject *parent = nullptr);
private slots:
    void empty_root_package();
    void no_among_the_children_root();
    void such_a_package_exists();
    void large_package_nesting();
    void existing_package_heavily_nested();
    void link_not_last_component_package();
    void insert_in_middle();
};
#endif // TESTSPLITPACKAGE_H
