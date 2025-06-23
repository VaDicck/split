/*!
 * \file typemistakes.h
 * \brief Заголовочный файл перечисления typeMistakes
 *
 * Содержит перечисление возможных типов ошибок:
 */

#ifndef TYPEMISTAKES_H
#define TYPEMISTAKES_H

/**
 * \enum typeMistakes
 * \brief Перечисление типов возможных ошибок в коде
 *
 * Определяет все возможные типы ошибок, которые могут быть обнаружены
 */
enum class typeMistakes {
    inputFileDoesNotExist,    ///< Входного файла не существует
    inputJavaFileDoesNotExist,///< Входного Java файла не существует
    manyStrokes,             ///< Превышено допустимое количество строк в файле
    inputFileEmpty,          ///< Входной файл пуст
    outputFileDoesNotExist,  ///< Выходного файла не существует
    manyJavaFiles,           ///< Превышено допустимое количество Java файлов
    fileWithoutPackage,      ///< Файл без явного указания пакета
    manyClassesInFile,       ///< Превышено допустимое количество классов в файле
    manyInterfacesInFile,    ///< Превышено допустимое количество интерфейсов в файле
    manyMethodInClass,       ///< Превышено допустимое количество методов в классе
    manyMethodInInterface,   ///< Превышено допустимое количество методов в интерфейсе
    manyFieldInClass,        ///< Превышено допустимое количество полей в классе
    manyFieldInInterface,    ///< Превышено допустимое количество полей в интерфейсе
    noClosingFiguredScoop,   ///< Нет закрывающей фигурной скобки
    noOpenningFiguredScoop,  ///< Нет открывающей фигурной скобки
    notClosedComment,        ///< Не закрыт комментарий
    notClosedSingleQuotes,   ///< Не закрыты одинарные кавычки
    notClosedDoubleQuotes    ///< Не закрыты двойные кавычки
};

#endif // TYPEMISTAKES_H
