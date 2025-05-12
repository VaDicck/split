#include <QCoreApplication>
#include <argument.h>

//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol);
//Пропустить многострочный комментарий
void skipMultilineComment(const QStringList &code,  int &indexCurrentString, int &indexCurrentSimbol);

int main(int argc, char *argv[])
{
}

//Пропустить константу
bool skipConstant(const QString &string, int &indexCurrentSimbol, const char &simbol){
    //Найти индекс следующей возможной константы в строке
    int indexConstant = indexCurrentSimbol+ string.mid(indexCurrentSimbol).indexOf(simbol);
    //Если была найденна
    if(indexConstant != -1){
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
            indexCurrentSimbol = indexConstant+1;
            //Если количество нечетное
            if(countBackup%2 != 0){
                //Исследовать строку далее
                return skipConstant(string, indexCurrentSimbol, simbol);
            }
            //Иначе нашли пару
            else{
                return true;
            }
        }
    }
    //Иначе
    else{
        //Считать пару не найденной
        return false;
    }
}
