#ifndef MAIN_H
#define MAIN_H
#include <QString>
#include <QTest>
#include "testskipconstant.h"
#include "testskipmultiplecomment.h"
#include "testfindlexemes.h"
#include "testsplitfield.h"
#include "testsplitmethod.h"
#include "testsplitclass.h"
#include "testsplitimport.h"
#include "testsplitpackage.h"
#include "testsplitproject.h"
#include "testsplitinterface.h"
#include "package_info.h"
#include "class_info.h"
#include "method.h"
#include "error.h"
#include "interface_info.h"
#include "field.h"
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDir>


//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol);
//Пропустить многострочный комментарий
bool skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSimbol);
//Найти лексемы
QPair<QString, QStringList> findLexemes(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QStringList &neededLexemes, const QStringList &needSimbols, const QStringList &endLexems);
// Разбить пакет
package_info* splitPackage(const QStringList &packageDeclaration, package_info &rootPackage);
// Разбить импорт
QString splitImport(const QStringList &declarationImport);
// Разбить класс
class_info splitClass(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol,const QStringList &declarationClass, QSet<error> &errors);
// Разбить интерфейс
interface_info splitInterface(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol , const QStringList &interfaceDeclaration, QSet<error> &errors);
// Разбить метод
method splitMethod(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QString &nameClass, const QStringList &methodDeclaration, QSet<error> &errors);
// Разбить поле
QMap<QString, field> splitField(const QStringList &declarationField);
// Разбить проект
void splitProject(const QList<QStringList> &project, package_info &rootPack, QSet<error> &errors);
// Прочитать проджект файл
bool readPrjFile(const QString &pathFile, QStringList &pathJavaFile, QSet<error> &errors);
// Прочитать Java файл
bool readJavaFiles(const QStringList &pathJavaFiles, QList<QStringList> &filesCode, QSet<error> &errors) ;
// Создать выходные данные

#endif // MAIN_H
