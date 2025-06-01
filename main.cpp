#include <QCoreApplication>
#include <argument.h>
#include <main.h>


int main(int argc, char *argv[])
{
    //QTest::qExec(new testSkipConstant,argc,argv);
    //QTest::qExec(new testSkipMultipleComment,argc,argv);
    QTest::qExec(new testFindLexemes,argc,argv);
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

}

//Разбить метод
method splitMethod(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol, const QString &nameClass, const QStringList &methodDeclaration, QSet<error> errors){

}

// Разбить интерфейс
interface_info splitInterface(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol , const QStringList &interfaceDeclaration, QSet<error> errors){

}

// Разбить поле
QMap<QString, field> splitField(const QStringList &fieldDeclaration){

}

// Разбить класс
class_info splitClass(const QStringList &code, int &indexCurrentString, int &indexCurrentSimbol,const QStringList &declarationClass, QSet<error> errors){

}

// Разбить проект
void splitProject(const QList<QStringList> &project, package_info &rootPack){

}
