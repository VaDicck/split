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

    // Тест 1. В одной строке
    QTest::newRow("inOneString")
        << QStringList{"char br /*=‘a’*/;", "int a=7, b=4;"}
        << 0 << 10 << 0 << 16 << true;

    // Тест 2. В разных строках
    QTest::newRow("inDifferentStrokes")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 3. Экранирование
    QTest::newRow("shielding")
        << QStringList{"char br/**= ‘a’\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 4. Множественное экранирование
    QTest::newRow("multipleShielding")
        << QStringList{"char br/**= ‘a’\\\\\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 5. Экранирование экранирования перед комментарием
    QTest::newRow("shieldingOfShieldingBeforeComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int \\\\\\\\*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 6. Не завершен
    QTest::newRow("notCompleted")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g();   int c;"}
        << 0 << 9 << 0 << 9 << false;

    // Тест 7. Экранирован завершающий комментарий
    QTest::newRow("shieldingFinalComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g(); \\*/  int c;"}
        << 0 << 9 << 0 << 9 << false;

    // Тест 8. Слэш внутри комментария
    QTest::newRow("slashInsideComment")
        << QStringList{"char br/**= ‘a’  ;", "int /a=7, /b=/4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 9. Начало комментария внутри комментария
    QTest::newRow("startCommentInternalComment")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, /*b=/4;", "int/* g();*/ int c;"}
        << 0 << 9 << 2 << 12 << true;

    // Тест 10. Завершающий комментарий через пробел
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
