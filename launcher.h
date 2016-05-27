#ifndef LAUNCHER_H
#define LAUNCHER_H

#include"var.h"
#include<iostream>
#include<QString>
#include<QChar>
#include<QVector>
#include<QPair>
#include<QFile>
#include<QTextStream>
#include<cmath>

using namespace std;

class Launcher
{
public:
    void run(); //Запустить программу
    Launcher(QString filePath);

private:
    void readFile();
    void setLabels();   //Установка всех меток в программе
    void nextLine();//Переходим у обработке
                                  //Следующей строки
    void runLine(); //Обработка текущей строки
                    //Этот метод вызывает остальные методы
                    //В зависимости того, что делает строка

    void setVar();
    void operation(QString operationName);
    void jump(int jmp);
    void setIf();
    void outOnConsole();
    void inConsole();

    //Дополнительные операции
    void f_sqrt();
    void outOnConsoleMessage();

private:
    QVector<QString> lines; //Здесь храним программу по строчно
    QVector<Var> vars;//Здесь храним все переменные программы
    QVector<QPair<int,int> > labels; //Здесь храним все метки
    int index; //Номер обрабатываемой строки
    QString filePath; //Путь к файлу
};

#endif // LAUNCHER_H
