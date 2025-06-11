#include <QCoreApplication>
#include <argument.h>
#include <main.h>


int main(int argc, char *argv[])
{
    //QTest::qExec(new testSkipConstant,argc,argv);
    //QTest::qExec(new testSkipMultipleComment,argc,argv);
    //QTest::qExec(new testFindLexemes,argc,argv);
    //QTest::qExec(new testSplitField,argc,argv);
    //QTest::qExec(new testsplitimport,argc,argv);
    QTest::qExec(new testsplitmethod,argc,argv);
}

//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol){
    //Если нет пары
    if(string.mid(indexCurrentSimbol).indexOf(simbol) == -1){
        //Конец строки
        indexCurrentSimbol = string.length();
        return false; //Считать что пары в строке нет
    }
    //Найти индекс второй пары
    int indexConstant = indexCurrentSimbol+ string.mid(indexCurrentSimbol).indexOf(simbol);
    //Если перед парой константы нет экранирования
    if(string[indexConstant-1] != '\\'){
        //Считаем текущий индекс за второй парой
        indexCurrentSimbol = indexConstant+1;
        //Считать пару найденной
        return true;
    }
    //Иначе
    else{
        //Считать, что экранирование одно
        int countBackup = 1;
        //Для каждого символа перед второй константой и до первой
        for(int i =indexConstant-2;i>=indexCurrentSimbol;--i){
            //Если сивол является экранированием увеличить счетчик количества экранирования
            if(string[i] == '\\'){
                countBackup++;
            }
            //Иначе закончить поиск
            else i =-1;
        }
        int beginSearch = indexCurrentSimbol;
        indexCurrentSimbol = indexConstant+1;
        //Если количество нечетное
        if(countBackup%2 != 0){
            //Исследовать строку далее
            bool resultSkip = skipConstant(string, indexCurrentSimbol, simbol);
            if(resultSkip == false){
                indexCurrentSimbol = beginSearch;
            }
            return resultSkip;
        }
        //Иначе нашли пару
        else{
            return true;
        }
    }
}

//Пропустить многострочный комментарий
bool skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSimbol){
    // Запомнить начальные значения
    int beginString = indexCurrentString, beginIndex = indexCurrentSimbol;
    // Пока не кончится код
    while(indexCurrentString<code.size()){
        int indexComment = code[indexCurrentString].mid(indexCurrentSimbol).indexOf("*/");
        // Если не был найден завершающий
        if(indexComment == -1){
            // Перейти на следующую строку
            indexCurrentString++;
            indexCurrentSimbol=0;
        }
        // Иначе
        else{
            // Индекс за комментария
            indexCurrentSimbol = indexCurrentSimbol+ indexComment + 2;
            // Закончить поиск
            return true;
        }
    }
    indexCurrentString = beginString, indexCurrentSimbol = beginIndex;
    return false;
}

//Найти лексемы
QPair<QString, QStringList> findLexemes(const QStringList &code, int &currentString, int &currentSimbol,const QStringList &neededLexemes,const QStringList &needSimbols, const QStringList &endLexemes)
{
    bool flagNeedLexemes = true;
    if(neededLexemes.empty()){
        flagNeedLexemes = false;
    }
    QPair<QString, QStringList> foundLexemes;
    QStringList lexems;
    QString wordString ="";
    for(int i=0;i<needSimbols.size();++i){
        wordString.append("|\\");
        wordString.append(needSimbols[i]);
    }
    for(int i=0;i<endLexemes.size();++i){
        if(endLexemes[i].size() == 1){
            wordString.append("|\\");
            wordString.append(endLexemes[i]);
        }
    }
    //Создать шаблон для регулярного выражения, которое будет искать любые слова через разделители и нужные символы
    QString pattern = "\\b\\w+\\b|\\/\\*|\\\"|\\'|\\//";
    //QString pattern = "\\b[a-zA-Z_\\d]+(_[a-zA-Z_\\d]+)*\\b|\\/\\*|\\\"|\\'|\\//";
    pattern.append(wordString);
    //Создать регулярное выражение по шаблону
    QRegularExpression modifierRegex(pattern);
    //Пока текущая строка меньше строки с завершением лексем
    while(currentString<code.size()) {
        //Найти ближайшую лексему в текущей строке после текущего символа
        QRegularExpressionMatch match = modifierRegex.match(code[currentString].mid(currentSimbol));
        //Если найдена лексема
        if (match.hasMatch()) {
            QString foundWord =match.captured();
            currentSimbol = currentSimbol +match.capturedEnd();
            //Если многострочный комментарий
            if(foundWord == "/*"){
                //Пропустить многострочный комментарий
                skipMultilineComment(code, currentString, currentSimbol);
            }
            //Иначе если строковая константа
            else if(foundWord == "\""){
                //Пропустить строковую константу
                skipConstant(code[currentString], currentSimbol, '"');
            }
            //Иначе если символьная константа
            else if(foundWord == "'"){
                //Пропустить символьную константу
                skipConstant(code[currentString], currentSimbol, '\'');
            }
            //Иначе если однострочный комментарий
            else if(foundWord == "//"){
                //Перейти на следующую строку
                currentString++;
                currentSimbol=0;
            }
            //Иначе
            else{
                //Считать лексему найденно
                foundLexemes.second.append(foundWord);
                //Если она одна из нужных, то считать нужную лексему найденной
                for(int i=0;i<neededLexemes.size() && flagNeedLexemes == true;++i){
                    if(foundWord == neededLexemes[i]){
                        foundLexemes.first = foundWord;
                        flagNeedLexemes = false;
                    }
                }
                //Вернуть найденные лекскемы, если она одна из завершающих
                for(int i=0;i<endLexemes.size();++i){
                    if(foundWord == endLexemes[i]){
                        return foundLexemes;
                    }
                }
            }
        }
        //Иначе перейти на следующую строку
        else{
            currentString++;
            currentSimbol = 0;
        }
    }
    //Вернуть найденные лексемы
    return foundLexemes;
}

//Разбить пакет
package_info* splitPackage(const QStringList &packageDeclaration, package_info &rootPackage) {

}


//Разбить импорт
QString splitImport(const QStringList &declarationImport){
    //Считать компоненты импорта пустыми
    QString componentsImport = "";
    //Если
    if(!declarationImport.isEmpty()){
        //Для каждого компонента, кроме последнего
        for(int i =1;i<declarationImport.size()-2;++i){
            //Добавить компонент в строку и добавить точку после него
            componentsImport.append(declarationImport[i]);
            componentsImport.append(".");
        }
        //Добавить последний компонент в строку
        componentsImport.append(declarationImport[declarationImport.size()-2]);
    }
    //Добавить строку с имортом в пакет
    return componentsImport;
}

//Разбить метод
method splitMethod(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QString &nameClass, const QStringList &methodDeclaration, QSet<error> errors){
    //Запоминаем начало метода
    const int startCodeMethodString = indexCurrentString, startCodeMethodSimbol = indexCurrentSimbol-1;
    //Считаь что количество открывающих скоб 1 закрывающих 0
    int countOpenBracket = 1;
    int countCloseBracket = 0;
    QString pattern = "\\/\\*|\\\"|\\'|\\/\\/|\\}|\\{";
    QRegularExpression modifierRegex(pattern);
    //Пока текущая строка меньше строки с завершением лексем
    QStringList codeMethod;
    if(methodDeclaration.last() == "{"){
        while(indexCurrentString<code.size() && countOpenBracket!=countCloseBracket) {
            //Найти слова
            QRegularExpressionMatch match = modifierRegex.match(code[indexCurrentString].mid(indexCurrentSimbol));
            //Если нашли слово
            if (match.hasMatch()) {
                QString foundWord =match.captured();
                indexCurrentSimbol = indexCurrentSimbol +match.capturedEnd();
                if(foundWord == "/*"){
                    skipMultilineComment(code, indexCurrentString, indexCurrentSimbol);
                }
                else if(foundWord == "\""){
                    skipConstant(code[indexCurrentString],indexCurrentSimbol, '"');
                }
                else if(foundWord == "'"){
                    skipConstant(code[indexCurrentString],indexCurrentSimbol, '\'');
                }
                else if(foundWord == "//"){
                    indexCurrentString++;
                    indexCurrentSimbol=0;
                }
                else if(foundWord == "{"){
                    countOpenBracket++;
                }
                else{
                    countCloseBracket++;
                }
            }
            //Иначе перейти на следующую строку
            else{
                indexCurrentString++;
                indexCurrentSimbol = 0;
            }
        }
        codeMethod.append(code[startCodeMethodString].mid(startCodeMethodSimbol-1));
        codeMethod.append(code.mid(startCodeMethodString+1, (indexCurrentString-1)-(startCodeMethodString)));
        codeMethod.append(code[indexCurrentString].mid(0, indexCurrentSimbol));
    }
    QString nameMethod;
    QString mod;
    //Найти индекс начала ( с аргументами
    int indexStartArg = methodDeclaration.indexOf("(");
    //Найти имя метода(перед скобкой с аргументами)
    nameMethod = methodDeclaration[indexStartArg-1];
    //Если имя не совпадает с именем класса
    //Получить строки до ( это объявление
    //Получить строку в ) это аргументы
    QStringList stringBeforeArg = methodDeclaration.mid(0, indexStartArg);
    QStringList stringArg = methodDeclaration.mid(indexStartArg+1, methodDeclaration.size() -indexStartArg-3 );
    //Если в объявлении есть public
    //Считать что модификатор доступа public
    if(stringBeforeArg.contains("public"))  mod = "Public";
    //Иначе если в объявлении есть private
    //Считать что модификатор доступа private
    else if(stringBeforeArg.contains("private")) mod = "Private";
    //Иначе если в объявлении есть protected
    //Считать что модификатор доступа protected
    else if(stringBeforeArg.contains("protected"))  mod = "Protected";
    //Иначе
    //Считать что модификатор доступа private
    else  mod = "default";
    QVector<argument> arguments;
    //Если список аргументов не пуст
    if(!stringArg.empty()){
        argument arg;
        int i=-1;
        do{
            i++;
            arg.setType(stringArg[i]);
            i++;
            arg.setName(stringArg[i]);
            i++;
            arguments.append(arg);
        }while(i < stringArg.size() && stringArg[i] == ",");
    }
    QString filename;
    filename.append("(");
    if(arguments.isEmpty() == false){
        for(int i = 0;i< arguments.size()-1;++i){
            filename.append(arguments[i].getType());
            filename.append(" ,");
        }
        filename.append(arguments[arguments.size()-1].getType());
    }
    filename.append(")");
    method currentMethod(mod, filename, codeMethod, arguments);
    if(nameMethod != nameClass){
        currentMethod.setNameMethod(nameMethod);
        if(stringBeforeArg.contains("abstract"))  currentMethod.setIsAbstract(true);
        else if(stringBeforeArg.contains("static")) currentMethod.setIsStatic(true);
        currentMethod.setReturnType(stringBeforeArg[stringBeforeArg.size()-2]);
        currentMethod.setFilename(currentMethod.getFilename().prepend(nameMethod));
    }
    else{
        constructor currentConstructor(mod, filename, codeMethod, arguments);
        currentMethod.setFilename(currentMethod.getFilename().prepend(nameClass));
    }
    return currentMethod;
}

// Разбить интерфейс
interface_info splitInterface(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol , const QStringList &interfaceDeclaration, QSet<error> errors){

}

// Разбить поле
QMap<QString, field> splitField(const QStringList &fieldDeclaration){
    QMap<QString, field> arrayFields;
    field currentField;
    int indexType=1;
    if(fieldDeclaration.contains("static")) {
        currentField.setIsStatic(true);
        indexType++;
    }
    if(fieldDeclaration.contains("public"))  currentField.setMod("Public");
    else if(fieldDeclaration.contains("private")) currentField.setMod("Private");
    else if(fieldDeclaration.contains("protected"))  currentField.setMod("Protected");
    else{
        indexType--;
        currentField.setMod("Private");
    }
    currentField.setType(fieldDeclaration[indexType]);
    indexType++;
    while(fieldDeclaration.mid(indexType).contains(",") == true){
        currentField.setNameField(fieldDeclaration[indexType]);
        arrayFields.insert(fieldDeclaration[indexType], currentField);
        indexType = fieldDeclaration.mid(indexType).indexOf(",")+indexType+1;
    }
    currentField.setNameField(fieldDeclaration[indexType]);
    arrayFields.insert(fieldDeclaration[indexType], currentField);
    return arrayFields;
}

// Разбить класс
class_info splitClass(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol,const QStringList &declarationClass, QSet<error> errors){

}

// Разбить проект
void splitProject(const QList<QStringList> &project, package_info &rootPack){

}
