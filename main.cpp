#include <QCoreApplication>
#include <argument.h>
#include <main.h>


int main(int argc, char *argv[])
{
    system("chcp 1251>nul");
    // Если первый аргумент флаг тестирования
    if(argv[1] == "-test"){
        QTest::qExec(new testSkipMultipleComment);
        QTest::qExec(new testSkipConstant);
        QTest::qExec(new testFindLexemes);
        QTest::qExec(new testSplitField);
        QTest::qExec(new testsplitmethod);
        QTest::qExec(new testsplitimport);
        QTest::qExec(new testsplitclass);
        QTest::qExec(new testsplitinterface);
        QTest::qExec(new testsplitpackage);
        QTest::qExec(new testsplitproject);
        return 0;// Завершить программму
    }

    QCoreApplication a(argc, argv);

    // Контейнер с ошибками
    QSet<error> errors;
    // Пути к Java файлам
    QStringList javaFiles;
    // Код java файлов
    QList<QStringList> code;
    // Корневой пакет
    package_info rootPack("root");
    // Если смогли прочесть пути к Java файлам
    if(readPrjFile(argv[1], javaFiles, errors)){
        // Прочтем Java файлы
        readJavaFiles(javaFiles,code,errors);
        // Разобьем Java файлы
        splitProject(code,rootPack,errors);
        // Создадим выходные данные
        createDataFiles(argv[2],rootPack,errors);
    }
    // Выведем полученные ошибки
    printErrors(errors);
}

//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSymbol, const char &Symbol){
    //Если нет пары
    if(string.mid(indexCurrentSymbol).indexOf(Symbol) == -1){
        //Конец строки
        indexCurrentSymbol = string.length();
        return false; //Считать что пары в строке нет
    }
    //Найти индекс второй пары
    int indexConstant = indexCurrentSymbol+ string.mid(indexCurrentSymbol).indexOf(Symbol);
    //Если перед парой константы нет экранирования
    if(string[indexConstant-1] != '\\'){
        //Считаем текущий индекс за второй парой
        indexCurrentSymbol = indexConstant+1;
        //Считать пару найденной
        return true;
    }
    //Иначе
    else{
        //Считать, что экранирование одно
        int countBackup = 1;
        //Для каждого символа перед второй константой и до первой
        for(int i =indexConstant-2;i>=indexCurrentSymbol;--i){
            //Если сивол является экранированием увеличить счетчик количества экранирования
            if(string[i] == '\\'){
                countBackup++;
            }
            //Иначе закончить поиск
            else i =-1;
        }
        int beginSearch = indexCurrentSymbol;
        indexCurrentSymbol = indexConstant+1;
        //Если количество нечетное
        if(countBackup%2 != 0){
            //Исследовать строку далее
            bool resultSkip = skipConstant(string, indexCurrentSymbol, Symbol);
            if(resultSkip == false){
                indexCurrentSymbol = beginSearch;
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
bool skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSymbol){
    // Запомнить начальные значения
    int beginString = indexCurrentString, beginIndex = indexCurrentSymbol;
    // Пока не кончится код
    while(indexCurrentString<code.size()){
        int indexComment = code[indexCurrentString].mid(indexCurrentSymbol).indexOf("*/");
        // Если не был найден завершающий
        if(indexComment == -1){
            // Перейти на следующую строку
            indexCurrentString++;
            indexCurrentSymbol=0;
        }
        // Иначе
        else{
            // Индекс за комментария
            indexCurrentSymbol = indexCurrentSymbol+ indexComment + 2;
            // Закончить поиск
            return true;
        }
    }
    indexCurrentString = beginString, indexCurrentSymbol = beginIndex;
    return false;
}

//Найти лексемы
QPair<QString, QStringList> findLexemes(const QStringList &code, int &currentString, int &currentSymbol,const QStringList &neededLexemes,const QStringList &needSymbols, const QStringList &endLexemes)
{
    // Флаг нужных лексем
    bool flagNeedLexemes = true;
    if(neededLexemes.empty()){
        // Если пуст, то не нужны
        flagNeedLexemes = false;
    }
    // Найденные лексемы
    QPair<QString, QStringList> foundLexemes;
    // Создадим строки для поиска
    QString wordString ="";
    for(int i=0;i<needSymbols.size();++i){
        wordString.append("|\\");
        wordString.append(needSymbols[i]);
    }
    for(int i=0;i<endLexemes.size();++i){
        if(endLexemes[i].size() == 1){
            wordString.append("|\\");
            wordString.append(endLexemes[i]);
        }
    }
    // Создать шаблон для регулярного выражения, которое будет искать любые слова через разделители и нужные символы
    QString pattern = "\\b[a-zA-Z_]\\w*\\b|\\/\\*|\\\"|\\'|\\/\\/";
    pattern.append(wordString);
    // Создать регулярное выражение по шаблону
    QRegularExpression modifierRegex(pattern);
    // Пока текущая строка меньше строки с завершением лексем
    while(currentString<code.size()) {
        // Найти ближайшую лексему в текущей строке после текущего символа
        QRegularExpressionMatch match = modifierRegex.match(code[currentString].mid(currentSymbol));
        //Если найдена лексема
        if (match.hasMatch()) {
            QString foundWord =match.captured();
            currentSymbol = currentSymbol +match.capturedEnd();
            // Если многострочный комментарий
            if(foundWord == "/*"){
                //Пропустить многострочный комментарий
                skipMultilineComment(code, currentString, currentSymbol);
            }
            // Иначе если строковая константа
            else if(foundWord == "\""){
                //Пропустить строковую константу
                skipConstant(code[currentString], currentSymbol, '"');
            }
            // Иначе если символьная константа
            else if(foundWord == "'"){
                //Пропустить символьную константу
                skipConstant(code[currentString], currentSymbol, '\'');
            }
            // Иначе если однострочный комментарий
            else if(foundWord == "//"){
                //Перейти на следующую строку
                currentString++;
                currentSymbol=0;
            }
            // Иначе
            else{
                // Считать лексему найденно
                foundLexemes.second.append(foundWord);
                // Если она одна из нужных, то считать нужную лексему найденной
                for(int i=0;i<neededLexemes.size() && flagNeedLexemes == true;++i){
                    if(foundWord == neededLexemes[i]){
                        foundLexemes.first = foundWord;
                        flagNeedLexemes = false;
                    }
                }
                // Вернуть найденные лекскемы, если она одна из завершающих
                for(int i=0;i<endLexemes.size();++i){
                    if(foundWord == endLexemes[i]){
                        return foundLexemes;
                    }
                }
            }
        }
        // Иначе перейти на следующую строку
        else{
            currentString++;
            currentSymbol = 0;
        }
    }
    // Вернуть найденные лексемы
    return foundLexemes;
}

//Разбить пакет
package_info* splitPackage(const QStringList &packageDeclaration, package_info &rootPackage) {
    //Создать указатель на текущий пакет
    package_info *currentPack = &rootPackage;
    //Для каждого компонента
    for (int i=1;i<packageDeclaration.size()-1;++i) {
        //Если такой пакет уже существует в текущем пакете
        if (currentPack->getChildren().contains(packageDeclaration[i])) {
            //Считать этот пакет текущим
            currentPack = &currentPack->getChildren()[packageDeclaration[i]];
        }
        //Иначе
        else {
            //Создаем пакет
            package_info childPack;
            //Присваиваем пакету имя из компонентов
            childPack.setNamePackage(packageDeclaration[i]);
            //Добавляем пакет, как дочерний
            currentPack->addChildPackage(childPack.getNamePackage(), childPack);
            //Считать созданный пакет текущим
            currentPack = &currentPack->getChildren()[childPack.getNamePackage()];
        }
    }
    //Вернуть указатель на текущий пакет
    return currentPack;
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
method splitMethod(const QStringList &code, int &indexCurrentString, int &indexCurrentSymbol, const QString &nameClass, const QStringList &methodDeclaration, QSet<error> &errors){
    // Если является статическим блоком
    method currentMethod;
    // Если является статическим
    if(methodDeclaration.size() == 2 && methodDeclaration[0] == "static") currentMethod = method("default", "static", {}, {});
    // Иначе
    else{
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
            // Обходим аргументы с конца
            int i = stringArg.size();
            while(i>-1){
                QString type;
                i--;
                // Имя аргумента
                arg.setName(stringArg[i]);
                i--;
                // Флаг что внутри контейнера
                bool flagInsideContainer = false;
                // Количество открывающих и закрывающих скобок
                int countCloseScob = 0, countOpenScob = 0;
                // Делаем пока не дойдем до начала и (находимся не в контейнере или текущая лексема не является запятой)
                do{
                    // Если является концом метода
                    if(stringArg[i] == ">") {
                        // То увеличиваем счетчик закрывающих скоб
                        countCloseScob++;
                        // Считаем что внутри контейнера
                        flagInsideContainer = true;
                    }
                    // Если является открывающей скобкой метода
                    else if(stringArg[i] == "<"){
                        // Увеличиваем количество открывающих скоб
                        countOpenScob++;
                        // Если количества скоб совпали, считаем что находимся не в контейнере
                        if(countCloseScob == countOpenScob) flagInsideContainer=false;
                    }
                    // Если являтся скобкой и находимся внутри контейнера
                    if(stringArg[i] == "," && flagInsideContainer == true) type.prepend(", ");
                    // Иначе добавляем в начало
                    else type.prepend(stringArg[i]);
                    i--;
                }while(i>-1 && ((flagInsideContainer == true) || (stringArg[i]!=",")));
                // Добавим тип
                arg.setType(type);
                // Добавим в общий вектор аргументов(в начало)
                arguments.prepend(arg);
            }
        }
        // Создадим имя файла
        QString filename;
        filename.append("(");
        if(arguments.isEmpty() == false){
            for(int i = 0;i< arguments.size()-1;++i){
                filename.append(arguments[i].getType());
                filename.append(", ");
            }
            filename.append(arguments[arguments.size()-1].getType());
        }
        filename.append(")");
        currentMethod = method(mod, filename, QStringList({}), arguments);
        // Если имя метода не равно имени классу => метод
        if(nameMethod != nameClass){
            // Имя метода
            currentMethod.setNameMethod(nameMethod);
            // Найдем возвращаемое значение и является ли метод статическим или абстрактным
            QString reType;
            for(int i =0;i<stringBeforeArg.size()-1;++i){
                if(stringBeforeArg[i] == "public" ||stringBeforeArg[i] == "private" ||stringBeforeArg[i] == "protected" || stringBeforeArg[i] == "default"){}
                else if(stringBeforeArg[i] == "abstract") currentMethod.setIsAbstract(true);
                else if(stringBeforeArg[i] == "static")  currentMethod.setIsStatic(true);
                else if(stringBeforeArg[i] == ",") reType.append(", ");
                else  reType.append(stringBeforeArg[i]);
            }
            currentMethod.setReturnType(reType);
            currentMethod.setFilename(currentMethod.getFilename().prepend(nameMethod));
        }
        // Иначе конструктор
        else{
            // Нет возвращаемого значения
            currentMethod.setReturnType("");
            // Имя файла
            currentMethod.setFilename(currentMethod.getFilename().prepend(nameClass));
        }
    }
    //----------------------------------------найти код метода------------------------------------------
    //Запоминаем начало метода
    const int startCodeMethodString = indexCurrentString, startCodeMethodSymbol = indexCurrentSymbol;
    //Считаь что количество открывающих скоб 1 закрывающих 0
    int countOpenBracket = 1;
    int countCloseBracket = 0;
    QString pattern = "\\/\\*|\\\"|\\'|\\/\\/|\\}|\\{";
    QRegularExpression modifierRegex(pattern);
    //Пока текущая строка меньше строки с завершением лексем
    QStringList codeMethod;
    // Если есть код
    if(methodDeclaration.last() == "{"){
        while(indexCurrentString<code.size() && countOpenBracket!=countCloseBracket) {
            //Найти лексемы
            QRegularExpressionMatch match = modifierRegex.match(code[indexCurrentString].mid(indexCurrentSymbol));
            //Если нашли лексему
            if (match.hasMatch()) {
                QString foundWord =match.captured();
                indexCurrentSymbol = indexCurrentSymbol +match.capturedEnd();
                if(foundWord == "/*"){
                    if(!skipMultilineComment(code, indexCurrentString, indexCurrentSymbol)){
                        errors.insert(error(typeMistakes::notClosedComment,0,0,0,0,0,0,0,0,0,indexCurrentString));
                    }
                }
                else if(foundWord == "\""){
                    if(!skipConstant(code[indexCurrentString],indexCurrentSymbol, '"')){
                        errors.insert(error(typeMistakes::notClosedDoubleQuotes,0,0,0,0,0,0,0,0,0,indexCurrentString));
                    }
                }
                else if(foundWord == "'"){
                    if(!skipConstant(code[indexCurrentString],indexCurrentSymbol, '\'')){
                        errors.insert(error(typeMistakes::notClosedSingleQuotes,0,0,0,0,0,0,0,0,0,indexCurrentString));
                    }
                }
                else if(foundWord == "//"){
                    indexCurrentString++;// перейти на следующую строку
                    indexCurrentSymbol=0;
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
                indexCurrentSymbol = 0;
            }
        }
        // Если не нашли завершения метода
        if(countOpenBracket!= countCloseBracket){
            indexCurrentString = startCodeMethodString, indexCurrentSymbol=startCodeMethodSymbol;
            errors.insert(error(typeMistakes::noClosingFiguredScoop,0,0,0,0,0,0,0,0,0,indexCurrentString));
            return currentMethod;
        }
        // Если не в одной строке
        else if(startCodeMethodString!=indexCurrentString ){
            codeMethod.append(code[startCodeMethodString].mid(startCodeMethodSymbol-1));
            codeMethod.append(code.mid(startCodeMethodString+1, (indexCurrentString-1)-(startCodeMethodString)));
            codeMethod.append(code[indexCurrentString].mid(0, indexCurrentSymbol));
        }
        // Иначе в одной
        else{
            codeMethod.append(code[startCodeMethodString].mid(startCodeMethodSymbol-1,indexCurrentSymbol-(startCodeMethodSymbol-1)));
        }
    }
    currentMethod.setCode(codeMethod);
    return currentMethod;
}

// Разбить интерфейс
interface_info splitInterface(const QStringList &code, int &indexCurrentString, int &indexCurrentSymbol , const QStringList &interfaceDeclaration, QSet<error> &errors){
    // Найденный интерфейс
    interface_info foundInterface;
    // Если явлется публичным
    if(interfaceDeclaration[0] == "public"){
        foundInterface.setMod("Public");
        // Тогда имя интерфейса после ключевого слова
        foundInterface.setNameInterface(interfaceDeclaration[2]);
    }
    // Иначе метод дефолтный и имя так же после ключевого слова
    else{
        foundInterface.setMod("default");
        foundInterface.setNameInterface(interfaceDeclaration[1]);
    }
    // Если есть ключевое слово extends
    if(interfaceDeclaration.indexOf("extends") != -1){
        // Добавим родительские интерфейсы
        for(int i = interfaceDeclaration.indexOf("extends")+1; i<interfaceDeclaration.size()-1;++i){
            if(interfaceDeclaration[i] != ",") foundInterface.addExtend(interfaceDeclaration[i]);
        }
    }
    //Пока текущая строка меньше количества строк кода
    while(indexCurrentString < code.size()){
        // Найдем объявление
        QPair<QString, QStringList> foundLexemes  = findLexemes(code, indexCurrentString, indexCurrentSymbol,{ "class", "interface"}, {"[", "]", "(", ")", ",", "<", ">", "="}, {"{",";", "}"});
        if(indexCurrentString<code.size()){
            // Если нашли завершение блока кода возвращем интерфейс
            if(foundLexemes.second.last() == "}") return foundInterface;
            // Если нашли интерфейс разобьем и добавим интерфейс
            if(foundLexemes.first == "interface"){
                interface_info vlojeniInterface = splitInterface(code, indexCurrentString, indexCurrentSymbol,foundLexemes.second, errors);
                QMap<QString, interface_info> includesInterface = foundInterface.getIncludeInterface();
                includesInterface.insert(vlojeniInterface.getNameInterface(), vlojeniInterface);
                foundInterface.setIncludeInterface(includesInterface);
            }
            // Если нашли класс разобьем и добавим класс
            else if(foundLexemes.first == "class"){
                class_info vnutriClass = splitClass(code, indexCurrentString, indexCurrentSymbol,foundLexemes.second, errors);
                QMap<QString, class_info> includesClasses = foundInterface.getIncludeClass();
                includesClasses.insert(vnutriClass.getNameClass(), vnutriClass);
                foundInterface.setIncludeClass(includesClasses);
            }
            else {
                // Иначе если есть круглая скобка(начало аргументов)
                if(foundLexemes.second.contains("(") == true){
                    // разобьем метод и добавим к интерфейсу
                    method Method = splitMethod(code, indexCurrentString, indexCurrentSymbol, "", foundLexemes.second, errors);
                    QSet<method> methods = foundInterface.getMethods();
                    methods.insert(Method);
                    foundInterface.setMethods(methods);
                }
                // Иначе является полем, разобьем и добавим к интерфейсу
                else{
                    QMap<QString, field> Field = splitField(foundLexemes.second);
                    QMap<QString, field> fields = foundInterface.getFields();
                    fields.insert(Field);
                    foundInterface.setFields(fields);
                }
            }
        }
    }
    // Раз не вернулся интерфейс то не нашли } тогда добавим ошибку и вернем интерфейс
    errors.insert(error(typeMistakes::noClosingFiguredScoop, 0, 0,0,0,0,0,0,0,0,indexCurrentString));
    return foundInterface;
}

// Разбить поле
QMap<QString, field> splitField(const QStringList &fieldDeclaration){
    // Контейнер полей
    QMap<QString, field> arrayFields;
    field currentField;
    int currentIndex=1;
    // Если поле является статическим
    if(fieldDeclaration.contains("static")) {
        currentField.setIsStatic(true);
        currentIndex++;
    }
    // Найти модификатор доступа
    if(fieldDeclaration.contains("public"))  currentField.setMod("Public");
    else if(fieldDeclaration.contains("private")) currentField.setMod("Private");
    else if(fieldDeclaration.contains("protected"))  currentField.setMod("Protected");
    // Если модификатора доступа нет
    else{
        currentIndex--;
        currentField.setMod("default");
    }
    // Если является массивом, поставить [] у типа
    if(fieldDeclaration.contains("[")&&fieldDeclaration.contains("]")){
        currentField.setType(fieldDeclaration[currentIndex]+"["+"]");
        currentIndex++;
    }
    // Если тип является контейнером
    else if(fieldDeclaration.contains("<")&&fieldDeclaration.contains(">")){
        QString type;
        bool flagClose = false;
        int kolvoOpenScob = 0, kolvoCloseScob = 0;
        while(flagClose == false || currentIndex != fieldDeclaration.size()-1){
            if(fieldDeclaration[currentIndex] == ",") type.append(fieldDeclaration[currentIndex] + " ");
            else type.append(fieldDeclaration[currentIndex]);
            if(fieldDeclaration[currentIndex] == "<"){
                kolvoOpenScob++;
            }
            else if(fieldDeclaration[currentIndex] == ">"){
                kolvoCloseScob++;
            }
            if((kolvoOpenScob == kolvoCloseScob) && kolvoOpenScob!=0) flagClose=true;
            currentIndex++;
        }
        currentField.setType(type);
    }
    // Обычный тип
    else{
        currentField.setType(fieldDeclaration[currentIndex]);
        currentIndex++;
    }
    // Пока есть перечисление полей данного типа
    while(fieldDeclaration.mid(currentIndex).contains(",") == true){
        currentField.setNameField(fieldDeclaration[currentIndex]);
        // Добавить текущее поле в массив полей
        arrayFields.insert(fieldDeclaration[currentIndex], currentField);
        // Перейти к следующему
        currentIndex = fieldDeclaration.mid(currentIndex).indexOf(",")+currentIndex+1;
    }
    currentField.setNameField(fieldDeclaration[currentIndex]);
    arrayFields.insert(fieldDeclaration[currentIndex], currentField);
    // Вернуть массив полей
    return arrayFields;
}

// Разбить класс
class_info splitClass(const QStringList &code, int &indexCurrentString, int &indexCurrentSymbol,const QStringList &declarationClass, QSet<error> &errors){
    class_info foundClass;
    //Добавить имя класса(после ключевого слова класс)
    foundClass.setNameClass(declarationClass[declarationClass.indexOf("class")+1]);
    foundClass.setIsAbstract(declarationClass.contains("abstract"));
    foundClass.setIsStatic(declarationClass.contains("static"));
    if(declarationClass.contains("public")) foundClass.setMod("Public");
    //Иначе если в объявлении есть private
    //Считать что модификатор доступа private
    else if(declarationClass.contains("private")) foundClass.setMod("Private");
    //Иначе если в объявлении есть protected
    //Считать что модификатор доступа protected
    else if(declarationClass.contains("protected")) foundClass.setMod("Protected");
    //Иначе
    //Считать что модификатор доступа
    else foundClass.setMod("default");
    if(declarationClass.indexOf("extends") != -1) {
        foundClass.setExtend(declarationClass[declarationClass.indexOf("extends")+1]);
    }
    // Если есть ключевое слово implements добавим интерфейсы
    if(declarationClass.indexOf("implements") != -1) {
        QStringList implementsList;
        for(int i = declarationClass.indexOf("implements")+1; i<declarationClass.size()-1; ++i) {
            implementsList.append(declarationClass[i]);
        }
        foundClass.setImplements(implementsList);
    }

    //Пока индекс текущей строки меньше количества строк кода
    while(indexCurrentString < code.size()) {
        // Найдем лексемы
        QPair<QString, QStringList> foundLexemes = findLexemes(code, indexCurrentString, indexCurrentSymbol,{ "class", "interface"}, {"[", "]", "(", ")", ",", "<", ">", "="}, {"{",";", "}"});
        if(indexCurrentString<code.size()){
            // Если найдена завершающая скобка то вернем класс
            if(foundLexemes.second.last() == "}") return foundClass;
            else if(foundLexemes.second.size() > 1){
                // Если нашли ключевое слово интерфейс то разобьем и добавим к классу
                if(foundLexemes.first == "interface") {
                    interface_info vlojeniInterface = splitInterface(code, indexCurrentString, indexCurrentSymbol, foundLexemes.second, errors);
                    QMap<QString, interface_info> includeInterface = foundClass.getIncludeInterface();
                    includeInterface.insert(vlojeniInterface.getNameInterface(), vlojeniInterface);
                    foundClass.setIncludeInterface(includeInterface);
                }
                // Если нашли ключевое слово класс то разобьем и добавим к классу
                else if(foundLexemes.first == "class") {
                    class_info vlojeniClass = splitClass(code, indexCurrentString, indexCurrentSymbol, foundLexemes.second, errors);
                    QMap<QString, class_info> includesClasses = foundClass.getIncludesClasses();
                    includesClasses.insert(vlojeniClass.getNameClass(), vlojeniClass);
                    foundClass.setIncludesClasses(includesClasses);
                }
                // Иначе если есть открывающая скобка(аргументы) или является статическим блоком кода
                else if(foundLexemes.second.contains("(") || (foundLexemes.second.size()==2 &&foundLexemes.second[0]=="static")) {
                    // Разобьем метод
                    method Method = splitMethod(code, indexCurrentString, indexCurrentSymbol, foundClass.getNameClass(), foundLexemes.second, errors);
                    // Если является методом добавим к методам класса
                    if(!Method.getNameMethod().isEmpty()) {
                        QSet<method> methods = foundClass.getMethods();
                        methods.insert(Method);
                        foundClass.setMethods(methods);
                    }
                    // Иначе к конструкторам класса
                    else {
                        QSet<constructor> constructors = foundClass.getConstructors();
                        constructors.insert(Method);
                        foundClass.setConstructors(constructors);
                    }
                }
                // Иначе является полем, разобьем и добавим к классу
                else{
                    QMap<QString, field>  newField = splitField(foundLexemes.second);
                    QMap<QString, field> fields = foundClass.getFields();
                    fields.insert(newField);
                    foundClass.setFields(fields);
                }
            }
        }
    }
    // Если не вернуся класс, значит не найдена скобка. Тогда добавим ошибку и вернем найденный класс
    errors.insert(error(typeMistakes::noClosingFiguredScoop, 0, 0,0,0,0,0,0,0,0,indexCurrentString));
    return foundClass;
}

// Разбить проект
void splitProject(const QList<QStringList> &project, package_info &rootPack, QSet<error> &errors){
    int numberFile = 1;// Номер файла
    //Для каждого файла в проекте
    for (const QStringList &file : project) {
        //Считать текущий пакет для записи данных пустым
        package_info *currentPackage = NULL;
        //Считать индекс текущего символа и текущей строки нулевыми
        int indexCurrentSymbol = 0, indexCurrentString =0;
        //Считать контейнер импортов объявленных в файле пустым
        QStringList imports;
        //Пока индекс текущей строки меньше количества строк
        while(indexCurrentString<file.size()){
            //Найти лексемы с нужными ключевыми словами {"package", "import", "class", "interface"}(функция - foundLexemes())
            QPair<QString, QStringList> foundLexemes  = findLexemes(file, indexCurrentString, indexCurrentSymbol,{"package", "import", "class", "interface"}, {"*"}, {"{",";"});
            //Если ключевое слово package
            if(foundLexemes.first == "package"){
                //Разбить пакет (функция - splitPackage())
                currentPackage = splitPackage(foundLexemes.second, rootPack);
            }
            //Иначе если пакет не найден
            else if(currentPackage == NULL){
                errors.insert(error(typeMistakes::fileWithoutPackage, numberFile,0, 0, 0, 0, "", "", 0, 0,0, ""));
            }
            //Иначе...
            else{
                //Если ключевое слово import
                if(foundLexemes.first == "import"){
                    //Разбить импорт (функция - splitImport())
                    imports.append(splitImport(foundLexemes.second));
                }
                //Если ключевое слово class
                else if(foundLexemes.first == "class"){
                    //Разбить класс - (функция - splitClass())
                    class_info foundClass= splitClass(file, indexCurrentString, indexCurrentSymbol, foundLexemes.second, errors);
                    foundClass.setImport(imports);
                    //Добавить класс к текущему пакету
                    (*currentPackage).addMapClass(foundClass);

                }
                //Если ключевое слово interface
                else if(foundLexemes.first == "interface"){
                    //Разбить интерфейс - (функция - splitInterface())
                    interface_info foundInterface = splitInterface(file, indexCurrentString, indexCurrentSymbol,foundLexemes.second, errors);
                    foundInterface.setImport(imports);
                    //Добавить интерфейс к текущему пакету
                    (*currentPackage).addMapInterface(foundInterface);
                }
            }
        }
        numberFile++;
    }
}

// Прочитать prj файл
bool readPrjFile(const QString &pathFile, QStringList &pathJavaFile, QSet<error> &errors) {
    // Открываем файл
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Добавляем ошибку, если не удалось открыть файл
        errors.insert(error(typeMistakes::inputFileDoesNotExist));
        return false;
    }

    // Читаем содержимое файла
    QTextStream in(&file);
    bool isEmptyFile = true;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            // Проверяем, существует ли файл
            QFileInfo fileInfo(line);
            if (fileInfo.exists() && fileInfo.isFile()) {
                pathJavaFile.append(line);
                isEmptyFile = false; // Файл не пуст, так как нашли непустую строку
            } else {
                // Добавляем ошибку, если файл не существует
                errors.insert(error(typeMistakes::inputJavaFileDoesNotExist, 0,  0,  0, 0,  0,  "", "",  0,  0, 0, line));
            }
        }
    }

    file.close();

    // Проверяем, был ли файл пустым
    if (isEmptyFile) {
        errors.insert(error(typeMistakes::inputFileEmpty));
        return false;
    }
    file.close();
    // Проверяем количество файлов
    const int MAX_FILES = 30;
    if (pathJavaFile.size() > MAX_FILES) {
        errors.insert(error(typeMistakes::manyJavaFiles, 0, 0, pathJavaFile.size()));
        return false;
    }
    return true;
}

// Прочитать Java файлы
bool readJavaFiles(const QStringList &pathJavaFile, QList<QStringList> &filesCode, QSet<error> &errors){
    // Для каждого пути к Java файлу
    for (const QString &filePath : pathJavaFile) {
        QFile file(filePath);
        // Копируем данные из файла
        QTextStream in(&file);
        QStringList fileLines;
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        while (!in.atEnd()) {
            fileLines.append(in.readLine());
        }
        // Если количество строк файла более 10000 добавим ошибку
        if(fileLines.size()>10000){
            errors.insert(error(typeMistakes::manyStrokes, 0, fileLines.size(), 0, 0, 0, "", "", 0, 0,0, filePath));
        }
        else{
            filesCode.append(fileLines);
        }
        file.close();
    }

    return filesCode.size() == 0;
}

// Вывести ошибки
void printErrors(const QSet<error>& errors) {
    for (const error& err : errors) {
        switch (err.getTypeMistake()) {
        case typeMistakes::inputFileDoesNotExist:
            qInfo() << "Неверно указан файл с входными данными. Возможно, файл не существует.";
            break;

        case typeMistakes::inputJavaFileDoesNotExist:
            qInfo() << "Указанный Java файл не существует:"
                     << err.getPathJavaFile();
            break;

        case typeMistakes::manyStrokes:
            qInfo() << "Превышено допустимое количество строк в" << err.getFileNumber()
                     << "файле. Максимально возможное количество строк 10000. Сейчас"
                     << err.getCountStrFile();
            break;

        case typeMistakes::inputFileEmpty:
            qInfo() <<"Неверно указан файл с входными данными. Данный файл пуст.";
            break;

        case typeMistakes::outputFileDoesNotExist:
            qInfo() << "Неверно указан каталог с выходными данными. Возможно, каталога не существует.";
            break;

        case typeMistakes::manyJavaFiles:
            qInfo() << "Количество путей к файлам .java превышает допустимое. Максимальное количество 30. Сейчас"
                     << err.getCountJavaFile();
            break;

        case typeMistakes::fileWithoutPackage:
            qInfo() << "Явно не указан пакет в" << err.getFileNumber()
                     << "файле. В каждом файле пакет должен быть явно указан.";
            break;

        case typeMistakes::manyClassesInFile:
            qInfo() << "Превышено количество классов в" << err.getFileNumber()
                     << "файле. Максимально допустимое количество 15. Сейчас"
                     << err.getCountClasses();
            break;

        case typeMistakes::manyInterfacesInFile:
            qInfo() << "Превышено количество интерфейсов в" << err.getFileNumber()
                     << "файле. Максимально допустимое количество 15. Сейчас"
                     << err.getCountInterfaces();
            break;

        case typeMistakes::manyMethodInClass:
            qInfo() << "Превышено количество методов класса в" << err.getFileNumber()
                     << "файле в" << err.getNameClass() << "классе. Максимально допустимое методов 25. Сейчас"
                     << err.getCountMethod();
            break;

        case typeMistakes::manyMethodInInterface:
            qInfo() << "Превышено количество методов интерфейса в" << err.getFileNumber()
                     << "файле в" << err.getNameInterface() << "интерфейсе. Максимально допустимое количество методов 25. Сейчас"
                     << err.getCountMethod();
            break;

        case typeMistakes::manyFieldInClass:
            qInfo() << "Превышено количество полей класса в" << err.getFileNumber()
                     << "файле в" << err.getNameClass() << "классе. Максимально допустимое количество полей 25. Сейчас"
                     << err.getCountField();
            break;

        case typeMistakes::manyFieldInInterface:
            qInfo() << "Превышено количество полей интерфейса в" << err.getFileNumber()
                     << "файле в" << err.getNameInterface() << "интерфейсе. Максимально допустимое количество полей 25. Сейчас"
                     << err.getCountField();
            break;

        case typeMistakes::noClosingFiguredScoop:
            qInfo() << "Код синтаксически не верен. Отсутствует закрывающая фигурная скобка в"
                     << err.getFileNumber() << "файле c" << err.getNumberStr() << "строки.";
            break;

        case typeMistakes::noOpenningFiguredScoop:
            qInfo() << "Код синтаксически не верен. Отсутствует открывающая фигурная скобка в"
                     << err.getFileNumber() << "файле перед" << err.getNumberStr() << "строкой.";
            break;

        case typeMistakes::notClosedComment:
            qInfo() << "Код синтаксически не верен. Многострочный комментарий не закрыт в"
                     << err.getFileNumber() << "файле с" << err.getNumberStr() << "строки.";
            break;

        case typeMistakes::notClosedSingleQuotes:
            qInfo() << "Код синтаксически не верен. Не закрыты одинарные кавычки в"
                     << err.getFileNumber() << "файле с" << err.getNumberStr() << "строки.";
            break;

        case typeMistakes::notClosedDoubleQuotes:
            qInfo() << "Код синтаксически не верен. Не закрыты двойные кавычки в"
                     << err.getFileNumber() << "файле с" << err.getNumberStr() << "строки.";
            break;
        }
    }
}

// Создать файл с данными
bool createDataFiles(const QString& outputDirPath,const package_info& currentPackage, QSet<error>& errors){
    QFileInfo dirInfo(outputDirPath);

    // Проверяем, существует ли директория
    if (!dirInfo.exists() ||!dirInfo.isDir() ) {
        errors.insert(error(typeMistakes::outputFileDoesNotExist,0, 0, 0, 0, 0, "", "", 0, 0, 0, outputDirPath));
        return false;
    }
    //==================================Создадим классы========================
    foreach(const class_info& currentClass, currentPackage.getIncludesClasses()){
        createDataClass(outputDirPath, currentClass);
    }
    //=================================Создадим интерфейсы======================
    foreach(const interface_info& currentInterface, currentPackage.getIncludesInterfaces()){
        createDataInterface(outputDirPath, currentInterface);
    }
    // Создадим данные о дочерних пакетах рекурсивно
    foreach(const package_info& currentPack, currentPackage.getChildren()){
        QDir(outputDirPath).mkdir(currentPack.getNamePackage());
        QString newDirPack = outputDirPath+"/"+currentPack.getNamePackage();
        if(!createDataFiles(newDirPack,currentPack, errors)) return false;
    }
    return true;
}

// Создать данные о классе
void createDataClass(const QString& outputDirPath,const class_info& currentClass){
    // Создадим директорию класса
    QDir(outputDirPath).mkdir("class_"+currentClass.getNameClass());
    // Получим новый путь в директорию класса
    QString newDirPath = outputDirPath+"/"+"class_"+currentClass.getNameClass();
    // Создадим xml файл в новой директории
    QFile file(newDirPath+"/"+currentClass.getNameClass()+".xml");

    QXmlStreamWriter writer(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    writer.setAutoFormatting(true);  // Читабельное форматирование
    // Начнем документ
    writer.writeStartDocument();
    // Сгенирируем xml и txt файл с кодом рекурсивно
    generateXMLClass(writer, currentClass, newDirPath);
    writer.writeEndDocument(); // Завершаем документ
    // Закроем файл
    file.close();
    // Рекурсивно обойдем вложенные классы
    foreach(const class_info& nestedClass,currentClass.getIncludesClasses()){
        createDataClass(newDirPath, nestedClass);
    }
    // Рекурсивно обойдем вложенные интерфейсы
    foreach(const interface_info& nestedInterface,currentClass.getIncludeInterface()){
        createDataInterface(newDirPath, nestedInterface);
    }
}

// Сгенерировать xml и txt файлы для класса
void generateXMLClass(QXmlStreamWriter& writer, const class_info& currentClass,const QString& newDirPath,int depth)
{
    // Форматирование отступа
    writer.writeCharacters("\n" + QString(depth * 2, ' '));

    // Открываем элемент класса
    writer.writeStartElement("class");
    writer.writeAttribute("name", currentClass.getNameClass());
    writer.writeAttribute("access", currentClass.getMod());
    writer.writeAttribute("extend", currentClass.getExtend());
    writer.writeAttribute("implements", currentClass.getImplements().join(", "));
    writer.writeAttribute("isStatic", currentClass.getIsStatic() ? "true" : "false");
    writer.writeAttribute("isAbstract", currentClass.getIsAbstract() ? "true" : "false");
    writer.writeAttribute("imports", currentClass.getImport().join("|"));
    writer.writeAttribute("depth", QString::number(depth));

    // Рекурсивно обрабатываем вложенные классы
    foreach (const class_info& innerClass, currentClass.getIncludesClasses()) {
        generateXMLClass(writer, innerClass, newDirPath, depth + 1);
    }
    // Рекурсивно обрабатываем вложенные интерфейсы
    foreach (const interface_info& nestedInterface, currentClass.getIncludeInterface()) {
        generateXMLInterface(writer, nestedInterface, newDirPath, depth + 1);
    }

    // Методы класса
    foreach (const method& currentMethod, currentClass.getMethods()) {
        writer.writeCharacters("\n" + QString((depth + 1) * 2, ' '));
        writer.writeStartElement("method");
        writer.writeAttribute("name", currentMethod.getNameMethod());
        writer.writeAttribute("returnType", currentMethod.getReturnType());
        writer.writeAttribute("access", currentMethod.getMod());
        writer.writeAttribute("isStatic", currentMethod.getIsStatic() ? "true" : "false");
        writer.writeAttribute("isAbstract", currentMethod.getIsAbstract() ? "true" : "false");
        // Аргументы метода
        foreach (const argument& currentArgument, currentMethod.getArguments()) {
            writer.writeStartElement("argument");
            writer.writeAttribute("name", currentArgument.getName());
            writer.writeAttribute("type", currentArgument.getType());
            writer.writeEndElement(); // </argument>
        }
        // Создаем .txt файл с кодом метода если на нулевой глубине
        if(depth==0){
            QString methodFilePath = newDirPath + "/" + currentMethod.getFilename() + ".txt";
            QFile methodFile(methodFilePath);
            if (methodFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&methodFile);
                for (const QString& line : currentMethod.getCode()) {
                    out << line << "\n";
                }
                methodFile.close();
            }
        }
        writer.writeEndElement(); // </method>
    }

    // Конструкторы
    foreach (const constructor& currentConstructor, currentClass.getConstructors()) {
        writer.writeCharacters("\n" + QString((depth + 1) * 2, ' '));
        writer.writeStartElement("constructor");
        writer.writeAttribute("name", currentClass.getNameClass());
        writer.writeAttribute("access", currentConstructor.getMod());
        // Аргументы конструктора
        foreach (const argument& currentArgument, currentConstructor.getArguments()) {
            writer.writeStartElement("argument");
            writer.writeAttribute("name", currentArgument.getName());
            writer.writeAttribute("type", currentArgument.getType());
            writer.writeEndElement(); // </argument>
        }
        // Создаем .txt файл с кодом конструктора если на нулевой глубине
        if(depth==0){
            QString methodFilePath = newDirPath + "/" + currentConstructor.getFilename() + ".txt";
            QFile methodFile(methodFilePath);
            if (methodFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&methodFile);
                for (const QString& line : currentConstructor.getCode()) {
                    out << line << "\n";
                }
                methodFile.close();
            }
        }
        writer.writeEndElement(); // </constructor>
    }

    // Поля класса
    foreach (const field& currentField, currentClass.getFields()) {
        writer.writeCharacters("\n" + QString((depth + 1) * 2, ' '));
        writer.writeStartElement("field");
        writer.writeAttribute("name", currentField.getNameField());
        writer.writeAttribute("type", currentField.getType());
        writer.writeAttribute("access", currentField.getMod());
        writer.writeAttribute("isStatic", currentField.getIsStatic()? "true" : "false");
        writer.writeEndElement(); // </field>
    }

    // Закрываем элемент класса
    writer.writeCharacters("\n" + QString(depth * 2, ' '));
    writer.writeEndElement(); // </class>
}

// Создать данные интерфейса
void createDataInterface(const QString& outputDirPath,const interface_info& currentInterface){
    // Создадим директорию интерфейса
    QDir(outputDirPath).mkdir("interface_"+currentInterface.getNameInterface());
    // Создадим для нее новый путь
    QString newDirPath = outputDirPath+"/"+"interface_"+currentInterface.getNameInterface();
    // Создадим xml файл
    QFile file(newDirPath+"/"+currentInterface.getNameInterface()+".xml");

    QXmlStreamWriter writer(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    writer.setAutoFormatting(true);  // Читабельное форматирование
    // Начнем документ
    writer.writeStartDocument();
    // Сгенерируем данные xml и txt рекурсивно
    generateXMLInterface(writer, currentInterface, newDirPath);
    writer.writeEndDocument(); // Завершаем документ
    // Закрываем файл
    file.close();
    // Сгенерируем данные о вложенных интерфейсах
    foreach(const interface_info& nestedInterface,currentInterface.getIncludeInterface()){
        createDataInterface(newDirPath, nestedInterface);
    }
    // Сгенерируем данные о вложенных классах
    foreach(const class_info& nestedClass, currentInterface.getIncludeClass()){
        createDataClass(newDirPath, nestedClass);
    }
}

// Сгенерируем данные xml и txt о интерфейсе
void generateXMLInterface(QXmlStreamWriter& writer, const interface_info& currentInterface,const QString& newDirPath,int depth)
{
    // Форматирование отступа
    writer.writeCharacters("\n" + QString(depth * 2, ' '));

    // Открываем элемент интерфейса
    writer.writeStartElement("interface");
    writer.writeAttribute("name", currentInterface.getNameInterface());
    writer.writeAttribute("access", currentInterface.getMod());
    writer.writeAttribute("extends", currentInterface.getExtends().join(", "));
    writer.writeAttribute("imports", currentInterface.getImport().join("|"));
    writer.writeAttribute("depth", QString::number(depth));

    // Рекурсивно обрабатываем вложенные интерфейсы
    foreach (const interface_info& nestedInterface, currentInterface.getIncludeInterface()) {
        generateXMLInterface(writer, nestedInterface, newDirPath, depth + 1);
    }
    // Рекурсивно обрабатываем вложенные классы
    foreach (const class_info& innerClass, currentInterface.getIncludeClass()) {
        generateXMLClass(writer, innerClass, newDirPath, depth + 1);
    }

    // Методы интерфейса
    foreach (const method& currentMethod, currentInterface.getMethods()) {
        writer.writeCharacters("\n" + QString((depth + 1) * 2, ' '));
        writer.writeStartElement("method");
        writer.writeAttribute("name", currentMethod.getNameMethod());
        writer.writeAttribute("returnType", currentMethod.getReturnType());
        writer.writeAttribute("access", currentMethod.getMod());
        writer.writeAttribute("isStatic", currentMethod.getIsStatic() ? "true" : "false");
        // Аргументы метода
        foreach (const argument& currentArgument, currentMethod.getArguments()) {
            writer.writeStartElement("argument");
            writer.writeAttribute("name", currentArgument.getName());
            writer.writeAttribute("type", currentArgument.getType());
            writer.writeEndElement(); // </argument>
        }
        // Создаем .txt файл с кодом метода если на нулевой глубине
        if(depth==0){
            QString methodFilePath = newDirPath + "/" + currentMethod.getFilename() + ".txt";
            QFile methodFile(methodFilePath);
            if (methodFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&methodFile);
                for (const QString& line : currentMethod.getCode()) {
                    out << line << "\n";
                }
                methodFile.close();
            }
        }
        writer.writeEndElement(); // </method>
    }

    // Поля интерфейса
    foreach (const field& currentField, currentInterface.getFields()) {
        writer.writeCharacters("\n" + QString((depth + 1) * 2, ' '));
        writer.writeStartElement("field");
        writer.writeAttribute("name", currentField.getNameField());
        writer.writeAttribute("type", currentField.getType());
        writer.writeAttribute("access", currentField.getMod());
        writer.writeEndElement(); // </field>
    }

    // Закрываем элемент интерфейса
    writer.writeCharacters("\n" + QString(depth * 2, ' '));
    writer.writeEndElement(); // </class>
}
