#include "testsplitbase.h"
#include <QSet>
#include <QMap>
#include <QTest>
QString testSplitBase::verifyMapField(const QMap<QString, field>& actual,const QMap<QString, field>& expected){\
    QString msg;
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyActual;
    // Заполним
    foreach(const QString& key, actual.keys()){
        keyActual.insert(key);
    }
    QSet<QString> keyExpected;
    // Заполним
    foreach(const QString& key, expected.keys()){
        keyExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyActual&keyExpected){
        if(!(actual.value(key)== expected.value(key))){
            msg.append(
                QString("\nСодержимое поля (%1) не сходится!\n"
                        "Имя полученного (%2)\tожидаемого (%3)\n"
                        "Тип поля получился (%4)\tожидался (%5)\n"
                        "Модификатор поля получился (%6)\tожидался (%7)\n"
                        "Статическое ли поле получилось (%8)\tожидалось (%9)\t")
                    .arg(key).arg(actual.value(key).getNameField()).arg(expected.value(key).getNameField()).arg(actual.value(key).getType())
                    .arg(expected.value(key).getType()).arg(actual.value(key).getMod()).arg(expected.value(key).getMod()).arg(actual.value(key).getIsStatic()).arg(expected.value(key).getIsStatic()));
        }
    }
    // Если есть лишние фактические
    if(!((keyActual-keyExpected).isEmpty())){
        foreach(const QString& key, keyActual){
            msg.append(QString("\nПоля (%1) нет в ожидаемом\n"
                               "Имя поля (%2)\n"
                               "Тип поля (%3)\n"
                               "Модификатор поля (%4)\n"
                               "Статическое ли поле (%5)\t")
                           .arg(key).arg(actual.value(key).getNameField()).arg(actual.value(key).getType())
                           .arg(actual.value(key).getMod()).arg(actual.value(key).getIsStatic()));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyExpected-keyActual).isEmpty())){
        foreach(const QString& key, keyExpected){
            msg.append(QString("\nПоля (%1) нет в фактическом\n"
                               "Имя поля (%2)\n"
                               "Тип поля (%3)\n"
                               "Модификатор поля (%4)\n"
                               "Статическое ли поле (%5)\t")
                           .arg(key).arg(expected.value(key).getNameField()).arg(expected.value(key).getType())
                           .arg(expected.value(key).getMod()).arg(expected.value(key).getIsStatic()));
        }
    }
    return msg;
}
void testSplitBase::verifyErrors(const QSet<error>&actual, const QSet<error>&expected){
    if (actual != expected) {
        QStringList messages;

        // Находим ошибки, которые есть в expected, но нет в actual
        QSet<error> missingErrors = expected - actual;
        for (const error& err : missingErrors) {
            messages << QString("Отсутствует ожидаемая ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в actual, но нет в expected
        QSet<error> unexpected = actual - expected;
        for (const error& err : unexpected) {
            messages << QString("Обнаружена неожиданная ошибка: %1 (строка %2, файл %3)").arg(int(err.typeMistake)).arg(err.numberStr).arg(err.fileNumber);
        }

        // Находим ошибки, которые есть в обоих наборах, но различаются по полям
        QSet<error> commonErrors = actual & expected;
        for (const error& err : commonErrors) {
            const error& expectedErr = *expected.find(err);
            if (!(err == expectedErr)) {
                QStringList diffFields;
                if (err.typeMistake != expectedErr.typeMistake) diffFields << "тип ошибки";
                if (err.fileNumber != expectedErr.fileNumber) diffFields << "номер файла";
                if (err.numberStr != expectedErr.numberStr) diffFields << "номер строки";
                // Добавьте другие поля по аналогии

                messages << QString("Ошибка %1 отличается по полям: %2")
                                .arg(int(err.typeMistake))
                                .arg(diffFields.join(", "));
            }
        }

        QVERIFY2(false,qPrintable(QString("Наборы ошибок не совпадают:\n%1\nОжидалось %2 ошибок, получено %3 ошибок").arg(messages.join("\n")).arg(expected.size()).arg(actual.size())));
    }
}
// Сравнить методы
QString testSplitBase::verifyConstructor(const constructor& actual,const constructor& expected){
    QString msg;
    //===============================================Сравнение аргументов метода=====================================================
    QVector<argument> acturalArg = actual.getArguments();
    QVector<argument> expectedArg = expected.getArguments();
    // Для минимального количества аргументов
    for (int i = 0; i < std::min(acturalArg.size(), expectedArg.size()); ++i) {
        if(!(acturalArg[i] == expectedArg[i])){
            msg.append(QString("\nНе соответствие аргументов в позиции (%1)\n"
                               "Имя полученного (%2)\tожидаемого (%3)\n"
                               "Тип полученного (%4)\tожидаемого (%5)\n")
                           .arg(i).arg(acturalArg[i].getName()).arg(expectedArg[i].getName())
                           .arg(acturalArg[i].getType()).arg(expectedArg[i].getType()));
        }
    }
    // Если в фактическом лишний аргумент
    if (acturalArg.size() > expectedArg.size()) {
        for (int i = expectedArg.size(); i < acturalArg.size(); ++i) {
            msg.append(QString("\nЛишний фактический аргумент в позиции(%1)\n"
                               "Имя полученного (%2)\n"
                               "Тип полученного (%3)\n")
                           .arg(i).arg(acturalArg[i].getName()).arg(acturalArg[i].getType()));
        }
    }
    // Если в ожидаемом лишний аргумент
    else if (acturalArg.size() < expectedArg.size()) {
        for (int i = acturalArg.size(); i < expectedArg.size(); ++i) {
            msg.append(QString("\nОжидаемых аргументов больше с позиции(%1)\n"
                               "Имя ожидаемый (%2)\n"
                               "Тип ожидаемый (%3)\n")
                           .arg(i).arg(expectedArg[i].getName()).arg(expectedArg[i].getType()));
        }
    }
    //===============================================================================================
    if(actual.getMod()!=expected.getMod()) msg.append(QString("\nНе соответствие модификаторов доступа метода получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getMod()).arg(expected.getMod()));
    if(actual.getFilename()!=expected.getFilename()) msg.append(QString("\nНе соответствие имени файла метода получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getFilename()).arg(expected.getFilename()));
    if(actual.getCode()!=expected.getCode()) msg.append(QString("\nНесоответствие кода метода:\nПолучено: \n%1\nОжидалось: \n%2")
                       .arg(actual.getCode().join("\n"))
                       .arg(expected.getCode().join("\n")));
    return msg;
}
QString testSplitBase::verifyMethod(const method& actual,const method& expected){
    QString msg;
    if(actual.getIsStatic() != expected.getIsStatic()) msg.append(QString("\nЯвляется ли абстрактным получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getIsAbstract()).arg(expected.getIsAbstract()));
    if(actual.getIsAbstract() != expected.getIsAbstract()) msg.append(QString("\nЯвляется ли статическим получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getIsStatic()).arg(expected.getIsStatic()));
    if(actual.getNameMethod()!=expected.getNameMethod()) msg.append(QString("\nНе соответствие имен метода получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getNameMethod()).arg(expected.getNameMethod()));
    if(actual.getReturnType()!=expected.getReturnType()) msg.append(QString("\nНе соответствие возвращаемого значения метода получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getReturnType()).arg(expected.getReturnType()));
    msg.append(verifyConstructor(constructor(actual.getMod(), actual.getFilename(), actual.getCode(), actual.getArguments()), constructor(expected.getMod(), expected.getFilename(), expected.getCode(), expected.getArguments())));
    return msg;

}
// Сравнить классы
QString testSplitBase::verifyClass(const class_info& actual,const class_info& expected){
    QString msg;
    // Проверим поля класса не связанные с контейнерами
    if(actual.getMod()!=expected.getMod()) msg.append(QString("\nНе соответствие модификаторов доступа класса получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getMod()).arg(expected.getMod()));
    if(actual.getIsAbstract()!=expected.getIsAbstract()) msg.append(QString("\nЯвляется ли абстрактным получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getIsAbstract()).arg(expected.getIsAbstract()));
    if(actual.getIsStatic()!=expected.getIsStatic()) msg.append(QString("\nЯвляется ли статическим получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getIsStatic()).arg(expected.getIsStatic()));
    if(actual.getNameClass()!=expected.getNameClass()) msg.append(QString("\nНе соответствие имен класса получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getNameClass()).arg(expected.getNameClass()));
    if(actual.getExtend()!=expected.getExtend()) msg.append(QString("\nНе соответствие родительского класса получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getExtend()).arg(expected.getExtend()));
    if(actual.getImplements() != expected.getImplements()) msg.append(QString("\nНе соответсвие интерфейсов расширяющий класс:\nПолучено: \n%1\nОжидалось: \n%2")
                       .arg(actual.getImplements().join(", "))
                       .arg(expected.getImplements().join(", ")));
    if(actual.getImport() != expected.getImport()) msg.append(QString("\nНе соответсвие импортов класса:\nПолучено: \n%1\nОжидалось: \n%2")
                       .arg(actual.getImport().join("\n"))
                       .arg(expected.getImport().join("\n")));
    // =====================================================Проверим конструкторы
    if(!((actual.getConstructors()-expected.getConstructors()).isEmpty())){
        foreach(const constructor& currentConstructor, actual.getConstructors()-expected.getConstructors()){
            msg.append(QString("\nНайден конструктор не совпадающий ни с одим ожидаемым\n"
                               "Модификатор доступа полученного (%1)\n"
                               "Имя файла полученного (%2)\n"
                               "Код полученного \n%3\t")
                           .arg(currentConstructor.getMod()).arg(currentConstructor.getFilename()).arg(currentConstructor.getCode().join("\n")));
        }
    }
    else if(!((expected.getConstructors()-actual.getConstructors()).isEmpty())){
        foreach(const constructor& currentConstructor,expected.getConstructors()-actual.getConstructors()){
            msg.append(QString("\nНайден конструктор не совпадающий с фактическим\n"
                               "Модификатор доступа ожидаемого (%1)\n"
                               "Имя файла ожидаемого (%2)\n"
                               "Код ожидаемого \n%3\t")
                           .arg(currentConstructor.getMod()).arg(currentConstructor.getFilename()).arg(currentConstructor.getCode().join("\n")));
        }
    }
    //========================================================Проверим поля=============================
    msg += verifyMapField(actual.getFields(), expected.getFields());
    //=======================================================Проверим методы===============================
    if(!((actual.getMethods()-expected.getMethods()).isEmpty())){
        foreach(const method& currentMethod, actual.getMethods()-expected.getMethods()){
            msg.append(QString("\nНайден метод не совпадающий с ожидаемым\n"
                               "Имя метода (%1)\n"
                               "Возвращаемое значение метода (%2)\n"
                               "Код метода \n%3\t")
                           .arg(currentMethod.getNameMethod()).arg(currentMethod.getReturnType())
                           .arg(currentMethod.getCode().join("\n")));
        }
    }
    else if(!((expected.getMethods()-actual.getMethods()).isEmpty())){
        foreach(const method& currentMethod, expected.getMethods()-actual.getMethods()){
            msg.append(QString("\nНайден метод не совпадающий с фактическим\n"
                               "Имя метода (%1)\n"
                               "Возвращаемое значение метода (%2)\n"
                               "Код метода \n%3\t")
                           .arg(currentMethod.getNameMethod()).arg(currentMethod.getReturnType())
                           .arg(currentMethod.getCode().join("\n")));
        }
    }
    //=======================================================Проверим классы===============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyClassActual;
    // Заполним
    foreach(const QString& key, actual.getIncludesClasses().keys()){
        keyClassActual.insert(key);
    }
    QSet<QString> keyClassExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludesClasses().keys()){
        keyClassExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyClassActual&keyClassExpected){
        msg+=verifyClass(actual.getIncludesClasses().value(key), expected.getIncludesClasses().value(key));
    }
    // Если есть лишние фактические
    if(!((keyClassActual-keyClassExpected).isEmpty())){
        foreach(const QString& key, keyClassActual-keyClassExpected){
            msg.append(QString("\nКласса (%1) нет в ожидаемом\n"
                               "Имя класса (%2)\n"
                               "Модификатор доступа класса (%3)\t")
                           .arg(key).arg(actual.getIncludesClasses()[key].getNameClass()).arg(actual.getIncludesClasses()[key].getMod()));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyClassExpected-keyClassActual).isEmpty())){
        foreach(const QString& key, keyClassExpected-keyClassActual){
            msg.append(QString("\nКласса (%1) нет в фактическом\n"
                               "Имя класса (%2)\n"
                               "Модификатор доступа класса (%3)\t")
                           .arg(key).arg(expected.getIncludesClasses()[key].getNameClass()).arg(expected.getIncludesClasses()[key].getMod()));
        }
    }
    //=======================================================Проверим интерфейсы==============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyInterfaceActual;
    // Заполним
    foreach(const QString& key, actual.getIncludeInterface().keys()){
        keyInterfaceActual.insert(key);
    }
    QSet<QString> keyInterfaceExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludeInterface().keys()){
        keyInterfaceExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyInterfaceActual&keyInterfaceExpected){
        msg += verifyInterface(actual.getIncludeInterface()[key], expected.getIncludeInterface()[key]);
    }
    // Если есть лишние фактические
    if(!((keyInterfaceActual-keyInterfaceExpected).isEmpty())){
        foreach(const QString& key, keyInterfaceActual-keyInterfaceExpected){
            msg.append(QString("\nИнтерфейса (%1) нет в ожидаемом\n"
                               "Имя интерфейса (%2)\n"
                               "Модификатор доступа интерфейса (%3)\t")
                           .arg(key).arg(actual.getIncludeInterface()[key].getNameInterface()).arg(actual.getIncludeInterface()[key].getMod()));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyInterfaceExpected-keyInterfaceActual).isEmpty())){
        foreach(const QString& key, keyInterfaceExpected-keyInterfaceActual){
            msg.append(QString("\nИнтерфейса (%1) нет в фактическом\n"
                               "Имя интерфейса (%2)\n"
                               "Модификатор доступа интерфейса (%3)\t")
                           .arg(key).arg(expected.getIncludeInterface()[key].getNameInterface()).arg(expected.getIncludeInterface()[key].getMod()));
        }
    }
    return msg;
}
// Сравнить интерфейсы
QString testSplitBase::verifyInterface(const interface_info& actual,const interface_info& expected){
    QString msg;
    // Проверим поля класса не связанные с контейнерами
    if(actual.getMod()!=expected.getMod()) msg.append(QString("\nНе соответствие модификаторов доступа интерфейса получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getMod()).arg(expected.getMod()));
    if(actual.getNameInterface()!=expected.getNameInterface()) msg.append(QString("\nНе соответствие имен интерфейса получен:(%1) ожидалось:(%2)\n")
                       .arg(actual.getNameInterface()).arg(expected.getNameInterface()));
    if(actual.getExtends() != expected.getExtends()) msg.append(QString("\nНе соответсвие родительских интерфейсов:\nПолучено: \n%1\nОжидалось: \n%2")
                       .arg(actual.getExtends().join(", "))
                       .arg(expected.getExtends().join(", ")));
    if(actual.getImport() != expected.getImport()) msg.append(QString("\nНе соответсвие импортов класса:\nПолучено: \n%1\nОжидалось: \n%2")
                       .arg(actual.getImport().join("\n"))
                       .arg(expected.getImport().join("\n")));
    //========================================================Проверим поля=============================
    msg+=verifyMapField(actual.getFields(), expected.getFields());
    //=======================================================Проверим методы===============================
    if(!((actual.getMethods()-expected.getMethods()).isEmpty())){
        foreach(const method& currentMethod, actual.getMethods()-expected.getMethods()){
            msg.append(QString("\nНайден метод не совпадающий с ожидаемым\n"
                               "Имя метода (%1)\n"
                               "Возвращаемое значение метода (%2)\n"
                               "Код метода \n%3\t")
                           .arg(currentMethod.getNameMethod()).arg(currentMethod.getReturnType())
                           .arg(currentMethod.getCode().join("\n")));
        }
    }
    else if(!((expected.getMethods()-actual.getMethods()).isEmpty())){
        foreach(const method& currentMethod, expected.getMethods()-actual.getMethods()){
            msg.append(QString("\nНайден метод не совпадающий с фактическим\n"
                               "Имя метода (%1)\n"
                               "Возвращаемое значение метода (%2)\n"
                               "Код метода \n%3\t")
                           .arg(currentMethod.getNameMethod()).arg(currentMethod.getReturnType())
                           .arg(currentMethod.getCode().join("\n")));
        }
    }
    //=======================================================Проверим классы===============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyClassActual;
    // Заполним
    foreach(const QString& key, actual.getIncludeClass().keys()){
        keyClassActual.insert(key);
    }
    QSet<QString> keyClassExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludeClass().keys()){
        keyClassExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyClassActual&keyClassExpected){
        msg += verifyClass(actual.getIncludeClass().value(key), expected.getIncludeClass().value(key));
    }
    // Если есть лишние фактические
    if(!((keyClassActual-keyClassExpected).isEmpty())){
        foreach(const QString& key, keyClassActual-keyClassExpected){
            msg.append(QString("\nКласса (%1) нет в ожидаемом\n"
                               "Имя класса (%2)\n"
                               "Модификатор доступа класса (%3)\t")
                           .arg(key).arg(actual.getIncludeClass()[key].getNameClass()).arg(actual.getIncludeClass()[key].getMod()));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyClassExpected-keyClassActual).isEmpty())){
        foreach(const QString& key, keyClassExpected-keyClassActual){
            msg.append(QString("\nКласса (%1) нет в фактическом\n"
                               "Имя класса (%2)\n"
                               "Модификатор доступа класса (%3)\t")
                           .arg(key).arg(expected.getIncludeClass()[key].getNameClass()).arg(expected.getIncludeClass()[key].getMod()));
        }
    }
    //=======================================================Проверим интерфейсы==============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyInterfaceActual;
    // Заполним
    foreach(const QString& key, actual.getIncludeInterface().keys()){
        keyInterfaceActual.insert(key);
    }
    QSet<QString> keyInterfaceExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludeInterface().keys()){
        keyInterfaceExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyInterfaceActual&keyInterfaceExpected){
        msg+=verifyInterface(actual.getIncludeInterface()[key], expected.getIncludeInterface()[key]);
    }
    // Если есть лишние фактические
    if(!((keyInterfaceActual-keyInterfaceExpected).isEmpty())){
        foreach(const QString& key, keyInterfaceActual-keyInterfaceExpected){
            msg.append(QString("\nИнтерфейса (%1) нет в ожидаемом\n"
                               "Имя интерфейса (%2)\n"
                               "Модификатор доступа интерфейса (%3)\t")
                           .arg(key).arg(actual.getIncludeInterface()[key].getNameInterface()).arg(actual.getIncludeInterface()[key].getMod()));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyInterfaceExpected-keyInterfaceActual).isEmpty())){
        foreach(const QString& key, keyInterfaceExpected-keyInterfaceActual){
            msg.append(QString("\nИнтерфейса (%1) нет в фактическом\n"
                               "Имя интерфейса (%2)\n"
                               "Модификатор доступа интерфейса (%3)\t")
                           .arg(key).arg(expected.getIncludeInterface()[key].getNameInterface()).arg(expected.getIncludeInterface()[key].getMod()));
        }
    }
    return msg;
}


// Сравним пакеты
QString testSplitBase::verifyPack(const package_info& actual,const package_info& expected, QString pathPack ){
    QString msg;
    if(actual.getNamePackage() != expected.getNamePackage()) msg.append(QString("\nИмена пакетов не совпадают\n"
                           "Фактический путь пакета:(%1)\n"
                           "Ожидаемый путь пакета:(%2)\t").arg(pathPack+actual.getNamePackage()+".").arg(pathPack+expected.getNamePackage()+"."));
    pathPack.append(expected.getNamePackage()).append(".");
    //==============================================Сравним классы==================================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyClassActual;
    // Заполним
    foreach(const QString& key, actual.getIncludesClasses().keys()){
        keyClassActual.insert(key);
    }
    QSet<QString> keyClassExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludesClasses().keys()){
        keyClassExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyClassActual&keyClassExpected){
        QString msgClass;
        msgClass.append(verifyClass(actual.getIncludesClasses().value(key), expected.getIncludesClasses().value(key)));
        if(!msgClass.isEmpty()) msg.append(QString("\nВ пути (%1) не равны классы\n").arg(pathPack+"."));
        msg+=msgClass;
    }
    // Если есть лишние фактические
    if(!((keyClassActual-keyClassExpected).isEmpty())){
        msg.append(QString("\nВ пути (%1) лишние фактические классы:").arg(pathPack));
        foreach(const QString& key, keyClassActual-keyClassExpected){
            msg += QString("\nКласса (%1) нет в ожидаемом\n"
                                "Имя класса: %2\n"
                                "Модификатор доступа: %3\n")
                            .arg(key)
                            .arg(actual.getIncludesClasses()[key].getNameClass())
                            .arg(actual.getIncludesClasses()[key].getMod());
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyClassExpected-keyClassActual).isEmpty())){
        msg.append(QString("\nВ пути (%1) лишние ожидаемые классы:").arg(pathPack));
        foreach(const QString& key, keyClassExpected-keyClassActual){
            msg += QString("\nКласса (%1) нет в фактическом\n"
                                               "Имя класса (%2)\n"
                                               "Модификатор доступа класса (%3)\t")
                                           .arg(key).arg(expected.getIncludesClasses()[key].getNameClass()).arg(expected.getIncludesClasses()[key].getMod());
        }
    }
    //=======================================================Проверим интерфейсы==============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyInterfaceActual;
    // Заполним
    foreach(const QString& key, actual.getIncludesInterfaces().keys()){
        keyInterfaceActual.insert(key);
    }
    QSet<QString> keyInterfaceExpected;
    // Заполним
    foreach(const QString& key, expected.getIncludesInterfaces().keys()){
        keyInterfaceExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyInterfaceActual&keyInterfaceExpected){
        QString msgInterface;
        msgInterface.append(verifyInterface(actual.getIncludesInterfaces()[key], expected.getIncludesInterfaces()[key]));
        if(!msgInterface.isEmpty()) msg.append(QString("\nВ пути (%1) не равны интерфейсы\n").arg(pathPack));
        msg+=msgInterface;
    }
    // Если есть лишние фактические
    if(!((keyInterfaceActual-keyInterfaceExpected).isEmpty())){
        msg.append(QString("\nВ пути (%1) лишние фактические интерфейсы:\n").arg(pathPack));
        foreach(const QString& key, keyInterfaceActual-keyInterfaceExpected){
            msg += QString("\nИнтерфейса (%1) нет в ожидаемом\n"
                                "Имя интерфейса (%2)\n"
                                "Модификатор доступа интерфейса (%3)\t")
                            .arg(key).arg(actual.getIncludesInterfaces()[key].getNameInterface()).arg(actual.getIncludesInterfaces()[key].getMod());
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyInterfaceExpected-keyInterfaceActual).isEmpty())){
        msg.append(QString("\nВ пути (%1) лишние ожидаемые интерфейсы:\n").arg(pathPack));
        foreach(const QString& key, keyInterfaceExpected-keyInterfaceActual){
            msg +=QString("\nИнтерфейса (%1) нет в фактическом\n"
                                               "Имя интерфейса (%2)\n"
                                               "Модификатор доступа интерфейса (%3)\t")
                                           .arg(key).arg(expected.getIncludesInterfaces()[key].getNameInterface()).arg(expected.getIncludesInterfaces()[key].getMod());
        }
    }
    //=======================================================Проверим дочерние пакеты==============================
    // Создадим контейнер ключей для ожидаемых и фактических значений(для удобного поиска разности)
    QSet<QString> keyChildPackActual;
    // Заполним
    foreach(const QString& key, actual.getChildren().keys()){
        keyChildPackActual.insert(key);
    }
    QSet<QString> keyChildPackExpected;
    // Заполним
    foreach(const QString& key, expected.getChildren().keys()){
        keyChildPackExpected.insert(key);
    }
    // Сравним все одинаковые по ключу
    foreach(const QString& key, keyChildPackActual&keyChildPackExpected){
        QString msgPack;
        msgPack.append(verifyPack(actual.getChildren()[key], expected.getChildren()[key], pathPack));
        if(!msgPack.isEmpty()) msg.append(QString("\nВ пути (%1) не равны пакеты\n").arg(pathPack));
        msg+=msgPack;
    }
    // Если есть лишние фактические
    if(!((keyChildPackActual-keyChildPackExpected).isEmpty())){
        foreach(const QString& key, keyChildPackActual-keyChildPackExpected){
            msg.append(QString("\nПакета (%1) по пути (%2)нет в ожидаемом \n")
                           .arg(key).arg(pathPack+key));
        }
    }
    // Если есть лишние ожидаемые
    else if(!((keyChildPackExpected-keyChildPackActual).isEmpty())){
        foreach(const QString& key, keyChildPackExpected-keyChildPackActual){
            msg.append(QString("\nПакета (%1) по пути (%2)нет в фактическом \n")
                           .arg(key).arg(pathPack+key));
        }
    }
    return msg;
}
