#include "testskipmultiplecomment.h"
#include "main.h"
void testSkipMultipleComment::add_data()
{
    QTest::addColumn<QStringList>("code");
    QTest::addColumn<int>("indexString");
    QTest::addColumn<int>("indexStart");
    QTest::addColumn<int>("exIndexString");
    QTest::addColumn<int>("exIndex");
    QTest::addColumn<bool>("exResult");

    QTest::newRow("inOneString")
        << QStringList{"char br /*=‘a’*/;", "int a=7, b=4;"}
        << 0 << 10 << 0 << 16 << true;

    QTest::newRow("inDifferentStrokes")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    QTest::newRow("shielding")
        << QStringList{"char br/**= ‘a’\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    QTest::newRow("multipleShielding")
        << QStringList{"char br/**= ‘a’\\\\\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    QTest::newRow("shieldingOfShieldingBeforeComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int \\\\\\\\*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    QTest::newRow("notCompleted")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g();   int c;"}
        << 0 << 9 << 0 << 9 << false;

    QTest::newRow("shieldingFinalComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g(); \\*/  int c;"}
        << 0 << 9 << 0 << 9 << false;

    QTest::newRow("slashInsideComment")
        << QStringList{"char br/**= ‘a’  ;", "int /a=7, /b=/4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    QTest::newRow("startCommentInternalComment")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, /*b=/4;", "int/* g();*/ int c;"}
        << 0 << 9 << 2 << 12 << true;

    QTest::newRow("closingCommentaryCrossSpace")
        << QStringList{"char br/**= ‘a’  ;", "int a* /=7, b=4;", "int *  /g();*/ int c;"}
        << 0 << 9 << 2 << 14 << true;
}

void testSkipMultipleComment::add()
{
    QFETCH(QStringList, code);
    QFETCH(int, indexString);
    QFETCH(int, indexStart);
    QFETCH(int, exIndexString);
    QFETCH(int, exIndex);
    QFETCH(bool, exResult);

    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
