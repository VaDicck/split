#include "testskipmultiplecomment.h"
#include "main.h"

void testSkipMultipleComment::inOneString(){
    QStringList code ={"char br /*=‘a’*/;",
                        "int a=7, b=4;"};
    int indexString = 0;
    int indexStart = 10;
    int exIndexString = 0;
    int exIndex = 16;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::inDifferentStrokes(){
    QStringList code ={"char br/**= ‘a’  ;",
        "int a=7, b=4;",
        "int g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 10;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::shielding(){
    QStringList code ={"char br/**= ‘a’\\*/;",
        "int a=7, b=4;",
        "int g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 10;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::multipleShielding(){
    QStringList code ={"char br/**= ‘a’\\\\\\*/;",
        "int a=7, b=4;",
        "int g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 10;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::shieldingOfShieldingBeforeComment(){
    QStringList code ={"char br/**= ‘a’   ;",
                        "int a=7, b=4;",
                        "int \\\\\\\\*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 10;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::notCompleted(){
    QStringList code ={"char br/**= ‘a’   ;",
        "int a=7, b=4;",
        "int g();   int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 0;
    int exIndex = 9;
    bool exResult = false;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::shieldingFinalComment(){
    QStringList code ={"char br/**= ‘a’   ;",
        "int a=7, b=4;",
        "int g(); \\*/  int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 0;
    int exIndex = 9;
    bool exResult = false;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::slashInsideComment(){
    QStringList code ={"char br/**= ‘a’  ;",
        "int /a=7, /b=/4;",
        "int g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 10;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::startCommentInternalComment(){
    QStringList code ={"char br/**= ‘a’  ;",
        "int a=7, /*b=/4;",
        "int/* g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 12;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
void testSkipMultipleComment::closingCommentaryCrossSpace(){
    QStringList code ={"char br/**= ‘a’  ;",
        "int a* /=7, b=4;",
        "int *  /g();*/ int c;"};
    int indexString = 0;
    int indexStart = 9;
    int exIndexString = 2;
    int exIndex = 14;
    bool exResult = true;
    bool result = skipMultilineComment(code, indexString, indexStart);
    QCOMPARE(result, exResult);
    QCOMPARE(indexString, exIndexString);
    QCOMPARE(indexStart, exIndex);
}
