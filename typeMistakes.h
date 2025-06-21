#ifndef TYPEMISTAKES_H
#define TYPEMISTAKES_H
enum class typeMistakes {
    inputFileDoesNotExist,    // входного файла не существует
    inputJavaFileDoesNotExist,// входного Java файла не существует
    manyStrokes,             // много строк
    inputFileEmpty,          // входной файл пуст
    outputFileDoesNotExist,   // выходного файла не существует
    manyJavaFiles,           // превышает допустимое количество Java файлов
    fileWithoutPackage,      // файл без явного указания пакета
    manyClassesInFile,       // превышает допустимое количество классов
    manyInterfacesInFile,    // превышает допустимое количество интерфейсов
    manyMethodInClass,       // превышает допустимое количество методов в классе
    manyMethodInInterface,   // превышает допустимое количество методов в интерфейсе
    manyFieldInClass,        // превышает допустимое количество полей в классе
    manyFieldInInterface,    // превышает допустимое количество полей в интерфейсе
    noClosingFiguredScoop,   // нет закрывающей фигурной скобы
    noOpenningFiguredScoop,  // нет открывающей фигурной скобы
    notClosedComment,        // не закрыт комментарий
    notClosedSingleQuotes,   // не закрыты одинарные кавычки
    notClosedDoubleQuotes    // не закрыты двойные кавычки
};
#endif // TYPEMISTAKES_H
