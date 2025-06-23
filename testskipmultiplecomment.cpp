#include "testskipmultiplecomment.h"
#include "main.h"

void testSkipMultipleComment::test_skip_comm_data()
{
    QTest::addColumn<QStringList>("code");       ///< Исходный код с комментариями
    QTest::addColumn<int>("indexString");        ///< Начальный индекс строки
    QTest::addColumn<int>("indexStart");         ///< Начальная позиция в строке
    QTest::addColumn<int>("exIndexString");      ///< Ожидаемый индекс строки после обработки
    QTest::addColumn<int>("exIndex");           ///< Ожидаемая позиция в строке после обработки
    QTest::addColumn<bool>("exResult");         ///< Ожидаемый результат (успешность пропуска)

    // Тест 1. В одной строке
    /*!
     * \test Тест 1: Комментарий в одной строке
     * Проверяет обработку многострочного комментария, полностью находящегося в одной строке
     */
    QTest::newRow("inOneString")
        << QStringList{"char br /*=‘a’*/;", "int a=7, b=4;"}
        << 0 << 10 << 0 << 16 << true;

    // Тест 2. В разных строках
    /*!
     * \test Тест 2: Комментарий в разных строках
     * Проверяет обработку многострочного комментария, занимающего несколько строк
     */
    QTest::newRow("inDifferentStrokes")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 3. Экранирование
    /*!
     * \test Тест 3: Экранированный комментарий
     * Проверяет обработку экранированного символа '*' перед закрытием комментария
     */
    QTest::newRow("shielding")
        << QStringList{"char br/**= ‘a’\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 0 << 18 << true;

    // Тест 4. Множественное экранирование
    /*!
     * \test Тест 4: Множественное экранирование
     * Проверяет обработку нескольких экранированных символов перед закрытием комментария
     */
    QTest::newRow("multipleShielding")
        << QStringList{"char br/**= ‘a’\\\\\\*/;", "int a=7, b=4;", "int g();*/ int c;"}
        << 0 << 9 << 0 << 20 << true;

    // Тест 5. Экранирование экранирования перед комментарием
    /*!
     * \test Тест 5: Экранирование перед комментарием
     * Проверяет обработку экранированных символов перед закрывающим комментарием
     */
    QTest::newRow("shieldingOfShieldingBeforeComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int \\\\\\\\*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 6. Не завершен
    /*!
     * \test Тест 6: Незавершенный комментарий
     * Проверяет обработку случая, когда комментарий не закрыт
     */
    QTest::newRow("notCompleted")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g();   int c;"}
        << 0 << 9 << 0 << 9 << false;

    // Тест 7. Экранирован завершающий комментарий
    /*!
     * \test Тест 7: Экранированный закрывающий комментарий
     * Проверяет обработку экранированного закрывающего комментария
     */
    QTest::newRow("shieldingFinalComment")
        << QStringList{"char br/**= ‘a’   ;", "int a=7, b=4;", "int g(); \\*/  int c;"}
        << 0 << 9 << 2 << 12 << true;

    // Тест 8. Слэш внутри комментария
    /*!
     * \test Тест 8: Слэш внутри комментария
     * Проверяет обработку символа '/' внутри комментария
     */
    QTest::newRow("slashInsideComment")
        << QStringList{"char br/**= ‘a’  ;", "int /a=7, /b=/4;", "int g();*/ int c;"}
        << 0 << 9 << 2 << 10 << true;

    // Тест 9. Начало комментария внутри комментария
    /*!
     * \test Тест 9: Вложенный комментарий
     * Проверяет обработку начала нового комментария внутри существующего
     */
    QTest::newRow("startCommentInternalComment")
        << QStringList{"char br/**= ‘a’  ;", "int a=7, /*b=/4;", "int/* g();*/ int c;"}
        << 0 << 9 << 2 << 12 << true;

    // Тест 10. Завершающий комментарий через пробел
    /*!
     * \test Тест 10: Разделенный закрывающий комментарий
     * Проверяет обработку закрывающего комментария, разделенного пробелом
     */
    QTest::newRow("closingCommentaryCrossSpace")
        << QStringList{"char br/**= ‘a’  ;", "int a* /=7, b=4;", "int *  /g();*/ int c;"}
        << 0 << 9 << 2 << 14 << true;
}

void testSkipMultipleComment::test_skip_comm()
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
