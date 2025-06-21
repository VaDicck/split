#ifndef TESTFINDLEXEMES_H
#define TESTFINDLEXEMES_H

#include <QObject>
#include <QTest>

typedef QPair<QString, QStringList> StringPair;
Q_DECLARE_METATYPE(StringPair)

class testFindLexemes : public QObject
{
    Q_OBJECT
private slots:
    void test_find_lexemes_data();
    void test_find_lexemes();
};

#endif // TESTFINDLEXEMES_H
