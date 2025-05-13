#ifndef MAIN_H
#define MAIN_H
#include <QString>
#include <QTest>
#include "testskipconstant.h"

//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol);
//Пропустить многострочный комментарий
void skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSimbol);

#endif // MAIN_H
