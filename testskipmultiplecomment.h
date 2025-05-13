#ifndef TESTSKIPMULTIPLECOMMENT_H
#define TESTSKIPMULTIPLECOMMENT_H

#include <QObject>
#include <QTest>

class testSkipMultipleComment : public QObject
{
    Q_OBJECT
private slots:
    void inOneString(); //В одной строке
    void inDifferentStrokes(); //В разных строках
    void shielding(); //Экранирование
    void multipleShielding(); //Множественное экранирование
    void shieldingOfShieldingBeforeComment(); //Экранирование экранирования перед комменатрием
    void notCompleted(); //Не завершен
    void shieldingFinalComment(); //Экранирование завершающего комментария
    void slashInsideComment(); //Слэш внутри комментария
    void startCommentInternalComment(); //Начало комментария внутри комментария
    void closingCommentaryCrossSpace(); //Завершающий комментарий через пробел
};

#endif // TESTSKIPMULTIPLECOMMENT_H
