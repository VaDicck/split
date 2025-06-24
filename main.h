/*!
 \mainpage Программа для разбиения кода на языке java на элементы(поля, классы, ...)
 *
 * \section  Введение
 * Данная программа предназначена для анализа исходного кода на языке java и разбиение его на элементы:
 * - Пакеты, как директории имеющие иерархическую структуру
 * - Вложенные в пакеты классы и интерфейсы (файл .xml представляющих иерархию и информацию, .txt файлы с кодом методов)
 * - Так же вложенные в классы и интерфейсы поля и методы
 * - Их аргументы
 * Программа принимает:
 * - Путь до файла.prj содержащий пути к java файлам
 * - Путь до выходной директории для записи данных
 *
 * Для запуска программы:
 * 1. Программу необходимо сначала скомпилировать
 *
 * 2. Далее открыть папку debug, расположенную в данной директории
 *
 * 3. Далее в папке открыть cmd
 *
 * Пример запуска программы из командной строки:
 * split.exe input.prj outputDir
 *
 * Получение результата от программы:
 * Для проверки разбиения кода необходимо проверить директорию outputDir. Если в консоли отобразится ошибка, о том что файлы не найдены. То выходная директория останется пустой, иначе в консоли будут найденные ошибки, а в выходной директории результат разбиения.
 *
 *
* \file main.h - заголовочный файл, содержащий описание функций программы
* \file main.cpp - файл содержит реальзацию функций программы
*/

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
#include <QXmlStreamWriter>

/*!
 * \brief skipConstant - Пропускает константу в строке
 * \param[in] string - строка для анализа
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \param[in] simbol - символ константы (' или ")
 * \return true - константа успешно пропущена, false - не найдена закрывающая кавычка
 */
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol);

/*!
 * \brief skipMultilineComment - Пропускает многострочный комментарий
 * \param[in] code - код для анализа
 * \param[in,out] indexCurrentString - текущий индекс строки (изменяется в процессе)
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \return true - комментарий успешно пропущен, false - не найден конец комментария
 */
bool skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSimbol);

/*!
 * \brief findLexemes - Находит лексемы в коде (с указанием нужных и завершающих)
 * \param[in] code - код для анализа
 * \param[in,out] indexCurrentString - текущий индекс строки (изменяется в процессе)
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \param[in] neededLexemes - список искомых лексем
 * \param[in] needSimbols - список нужных символов
 * \param[in] endLexems - список завершающих лексем
 * \return Пара: найденная лексема из нужных и список всех найденных лексем до окончательной
 */
QPair<QString, QStringList> findLexemes(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QStringList &neededLexemes, const QStringList &needSimbols, const QStringList &endLexems);

/*!
 * \brief splitPackage - Разбивает объявление пакета
 * \param[in] packageDeclaration - объявление пакета
 * \param[in,out] rootPackage - корневой пакет (изменяется в процессе)
 * \return Указатель на созданный/найденный пакет
 */
package_info* splitPackage(const QStringList &packageDeclaration, package_info &rootPackage);

/*!
 * \brief splitImport - Собирает объявление импорта воедино
 * \param[in] declarationImport - объявление импорта
 * \return Строка с компонентами импорта
 */
QString splitImport(const QStringList &declarationImport);

/*!
 * \brief splitClass - Разбивает объявление класса и его содержимое
 * \param[in] code - код для анализа
 * \param[in,out] indexCurrentString - текущий индекс строки (изменяется в процессе)
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \param[in] declarationClass - объявление класса
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return Информация о классе
 */
class_info splitClass(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol,const QStringList &declarationClass, QSet<error> &errors);

/*!
 * \brief splitInterface - Разбивает объявление интерфейса
 * \param[in] code - код для анализа
 * \param[in,out] indexCurrentString - текущий индекс строки (изменяется в процессе)
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \param[in] interfaceDeclaration - объявление интерфейса
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return Информация об интерфейсе
 */
interface_info splitInterface(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol , const QStringList &interfaceDeclaration, QSet<error> &errors);

/*!
 * \brief splitMethod - Разбивает объявление метода
 * \param[in] code - код анализа
 * \param[in,out] indexCurrentString - текущий индекс строки (изменяется в процессе)
 * \param[in,out] indexCurrentSimbol - текущий индекс символа (изменяется в процессе)
 * \param[in] nameClass - имя класса
 * \param[in] methodDeclaration - объявление метода
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return Информация о методе
 */
method splitMethod(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QString &nameClass, const QStringList &methodDeclaration, QSet<error> &errors);

/*!
 * \brief splitField - Разбивает объявление поля
 * \param[in] declarationField - объявление поля
 * \return Карта полей (имя поля -> поле)
 */
QMap<QString, field> splitField(const QStringList &declarationField);

/*!
 * \brief splitProject - Разбивает весь проект
 * \param[in] project - код проекта, список кодов файлов
 * \param[in,out] rootPack - корневой пакет (изменяется в процессе)
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 */
void splitProject(const QList<QStringList> &project, package_info &rootPack, QSet<error> &errors);

/*!
 * \brief readPrjFile - Читает файл проекта
 * \param[in] pathFile - путь к файлу проекта
 * \param[in,out] pathJavaFile - список путей к Java файлам (изменяется в процессе)
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return true - файл успешно прочитан, false - ошибка чтения
 */
bool readPrjFile(const QString &pathFile, QStringList &pathJavaFile, QSet<error> &errors);

/*!
 * \brief readJavaFiles - Читает Java файлы
 * \param[in] pathJavaFiles - список путей к Java файлам
 * \param[in,out] filesCode - код файлов (изменяется в процессе)
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return true - файлы успешно прочитаны, false - ошибка чтения
 */
bool readJavaFiles(const QStringList &pathJavaFiles, QList<QStringList> &filesCode, QSet<error> &errors);

/*!
 * \brief printErrors - Выводит ошибки в консоль
 * \param[in] errors - контейнер с ошибками
 */
void printErrors(const QSet<error>& errors);

/*!
 * \brief createDataFiles - Создает выходные файлы с данными
 * \param[in] outputDirPath - путь к выходной директории
 * \param[in] currentPackage - текущий пакет
 * \param[in,out] errors - контейнер для ошибок (изменяется в процессе)
 * \return true - файлы успешно созданы, false - выходной или поддиректории не существует
 */
bool createDataFiles(const QString& outputDirPath,const package_info& currentPackage, QSet<error>& errors);

/*!
 * \brief Создает данные для интерфейса
 * \param[in] outputDirPath - путь к выходной директории
 * \param[in] currentInterface - текущий интерфейс
 */
void createDataInterface(const QString& outputDirPath,const interface_info& currentInterface);

/*!
 * \brief Создает данные для класса
 * \param[in] outputDirPath - путь к выходной директории
 * \param[in] currentClass - текущий класс
 */
void createDataClass(const QString& outputDirPath,const class_info& currentClass);

/*!
 * \brief Генерирует XML для класса
 * \param[in,out] writer - XML writer (изменяется в процессе)
 * \param[in] currentClass - текущий класс
 * \param[in] newDirPath - путь к директории
 * \param[in] depth - глубина вложенности
 */
void generateXMLClass(QXmlStreamWriter& writer, const class_info& currentClass,const QString& newDirPath,int depth = 0);

/*!
 * \brief Генерирует XML для интерфейса
 * \param[in,out] writer - XML writer (изменяется в процессе)
 * \param[in] currentInterface - текущий интерфейс
 * \param[in] newDirPath - путь к директории
 * \param[in] depth - глубина вложенности
 */
void generateXMLInterface(QXmlStreamWriter& writer, const interface_info& currentInterface,const QString& newDirPath,int depth = 0);

#endif // MAIN_H
