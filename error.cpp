#include "error.h"

// Конструктор по умолчанию
error::error() :
    typeMistake(typeMistakes::inputFileDoesNotExist),
    fileNumber(0),
    countStrFile(0),
    countJavaFile(0),
    countClasses(0),
    countInterfaces(0),
    nameClass(""),
    nameInterface(""),
    countMethod(0),
    countField(0),
    numberStr(0),
    pathJavaFile(""){}

// Конструктор с параметрами
error::error(typeMistakes type, int fNum, int cStr, int cJava,
             int cCls, int cInt, const QString& nCls,
             const QString& nInt, int cMeth, int cFld, int nStr, QString pthJvFile) :
    typeMistake(type),
    fileNumber(fNum),
    countStrFile(cStr),
    countJavaFile(cJava),
    countClasses(cCls),
    countInterfaces(cInt),
    nameClass(nCls),
    nameInterface(nInt),
    countMethod(cMeth),
    countField(cFld),
    numberStr(nStr),
    pathJavaFile(pthJvFile) {}

typeMistakes error::getTypeMistake() const { return typeMistake; }
int error::getFileNumber() const { return fileNumber; }
int error::getCountStrFile() const { return countStrFile; }
int error::getCountJavaFile() const { return countJavaFile; }
int error::getCountClasses() const { return countClasses; }
int error::getCountInterfaces() const { return countInterfaces; }
QString error::getNameClass() const { return nameClass; }
QString error::getNameInterface() const { return nameInterface; }
int error::getCountMethod() const { return countMethod; }
int error::getCountField() const { return countField; }
int error::getNumberStr() const { return numberStr; }
QString error::getPathJavaFile() const { return pathJavaFile; }

// Сеттеры
void error::setTypeMistake(typeMistakes type) { typeMistake = type; }
void error::setFileNumber(int fNum) { fileNumber = fNum; }
void error::setCountStrFile(int cStr) { countStrFile = cStr; }
void error::setCountJavaFile(int cJava) { countJavaFile = cJava; }
void error::setCountClasses(int cCls) { countClasses = cCls; }
void error::setCountInterfaces(int cInt) { countInterfaces = cInt; }
void error::setNameClass(const QString& nCls) { nameClass = nCls; }
void error::setNameInterface(const QString& nInt) { nameInterface = nInt; }
void error::setCountMethod(int cMeth) { countMethod = cMeth; }
void error::setCountField(int cFld) { countField = cFld; }
void error::setNumberStr(int nStr) { numberStr = nStr; }
void error::setPathJavaFile(const QString& path) { pathJavaFile = path; }

// Оператор сравнения
bool error::operator==(const error& other) const {
    return typeMistake == other.typeMistake &&
           fileNumber == other.fileNumber &&
           countStrFile == other.countStrFile &&
           countJavaFile == other.countJavaFile &&
           countClasses == other.countClasses &&
           countInterfaces == other.countInterfaces &&
           nameClass == other.nameClass &&
           nameInterface == other.nameInterface &&
           countMethod == other.countMethod &&
           countField == other.countField &&
           numberStr == other.numberStr &&
           pathJavaFile == other.pathJavaFile;
}
bool error::operator!=(const error& other) const {
    return typeMistake != other.typeMistake &&
           fileNumber != other.fileNumber &&
           countStrFile != other.countStrFile &&
           countJavaFile != other.countJavaFile &&
           countClasses != other.countClasses &&
           countInterfaces != other.countInterfaces &&
           nameClass != other.nameClass &&
           nameInterface != other.nameInterface &&
           countMethod != other.countMethod &&
           countField != other.countField &&
           numberStr != other.numberStr &&
           pathJavaFile != other.pathJavaFile;
}
