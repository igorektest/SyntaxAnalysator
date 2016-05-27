#include "launcher.h"

Launcher::Launcher(QString filePath)
{
    index = 0;
    this->filePath = filePath;
    readFile();
}

void Launcher::run()
{
    setLabels(); //Устанавливаем все метки в программе

    while(true)
    {
        if(index>lines.size()-1)
            break;
        else
            runLine();
    }
}

void Launcher::readFile()
{
    QFile myFile(filePath);

    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QTextStream myText(&myFile);

    while(true)
    {
        if(myText.atEnd() == true)
            break;
        else
            lines.push_back(myText.readLine() + "\n");
    }
    myFile.close();

}

void Launcher::runLine()
{
    QString line = lines[index];

    if(line[0] == ';')
    {
        nextLine();
    }

    if(line[0] == '=')
    {
        setVar();
        nextLine();
    }


    if(line[0] == '+')
    {
        operation("+");
        nextLine();
    }

    if(line[0] == '-')
    {
        operation("-");
        nextLine();
    }


    if(line[0] == '/')
    {
        operation("/");
        nextLine();
    }

    if(line[0] == '*')
    {
        operation("*");
        nextLine();
    }


    if(line[0] == ':')
    {
        nextLine();
    }

    if(line[0] == 'J' && line[1] == 'M' && line[2] == 'P')
    {
        QString label_str = "";
        for(int i(4); i<line.length();++i)
        {
            if(line[i] == ' ' || line[i] == '\n')
                break;
            else
                label_str += (QString)line[i];
        }
        jump(label_str.toInt());
    }

    if(line[0] == '!')
    {
        outOnConsole();
        nextLine();
    }


    if(line[0] == 'I' && line[1]=='F')
    {
        setIf();
    }

    if(line[0] == 'S' && line[1] == 'Q' && line[2] == 'R' && line[3] == 'T')
    {
        f_sqrt();
        nextLine();
    }

    if(line[0] == 'M' && line[1] == 'S' && line[2] == 'G')
    {
        outOnConsoleMessage();
        nextLine();
    }

    if(line[0] == 'I' && line[1] == 'N' && line[2] == 'V'
            && line[3] == 'A' && line[4] == 'R')
    {
        inConsole();
        nextLine();
    }
}



void Launcher::setVar()
{
    QString line = lines[index];
    QString id = "";
    int i;
    for(i = 2; i<line.length();i++)
    {
        if(line[i] == ' ') break;
        else
            id += (QString)line[i];
    }
    QString valueStr ="";

    for(int j = i+1; j<line.length()-1;j++)
        valueStr+=(QString)line[j];

    Var var;
    var.id = id;
    var.value = valueStr.toFloat();
    bool create = false;


    for(int i = 0;i<vars.size();++i)
    {
        if(var.id == vars[i].id)
        {
            vars[i].value = var.value;
            create = true;
        }
    }

    if(create == false)
    {
        vars.push_back(var);
    }
}

void Launcher::operation(QString operationName)
{

    if(operationName == "+")
    {
        QString line =  lines[index];
        QString var_1 = "";
        QString var_2 = "";
        QString var_3 = "";

        int i;
        for(i = 2; i<line.length();i++)
        {
            if(line[i] == ' ') break;
            else
                var_1 += (QString)line[i];
        }

        int j;
        for(j = i+1; j<line.length();j++)
        {
            if(line[j] == ' ') break;
            else
                var_2 += (QString)line[j];
        }

        int k;
        for(k = j+1; k<line.length();k++)
        {
            if(line[k] == '\n' || line[k] == ' ') break;
            else
                var_3 += (QString)line[k];
        }

        int index_1 = -1;
        int index_2 = -1;
        int index_3 = -1;


        for(int i = 0;i<vars.size();++i)
        {
            if(vars[i].id == var_1) index_1 = i;
            if(vars[i].id == var_2) index_2 = i;
            if(vars[i].id == var_3) index_3 = i;
        }

        if(index_1 == -1 || index_2 == -1)
        {
            //Выкинуть эксепшен
        }
        else
        {
            if(index_3 == -1)
            {
                Var var;
                var.id = var_3;
                var.value = vars[index_1].value + vars[index_2].value;
                vars.push_back(var);
            }
            else
            {
                vars[index_3].value =  vars[index_1].value + vars[index_2].value;
            }
        }
    }

    if(operationName == "-")
    {
        QString line =  lines[index];
        QString var_1 = "";
        QString var_2 = "";
        QString var_3 = "";

        int i;
        for(i = 2; i<line.length();i++)
        {
            if(line[i] == ' ') break;
            else
                var_1 += (QString)line[i];
        }

        int j;
        for(j = i+1; j<line.length();j++)
        {
            if(line[j] == ' ') break;
            else
                var_2 += (QString)line[j];
        }

        int k;
        for(k = j+1; k<line.length();k++)
        {
            if(line[k] == '\n' || line[k] == ' ') break;
            else
                var_3 += (QString)line[k];
        }

        int index_1 = -1;
        int index_2 = -1;
        int index_3 = -1;


        for(int i = 0;i<vars.size();++i)
        {
            if(vars[i].id == var_1) index_1 = i;
            if(vars[i].id == var_2) index_2 = i;
            if(vars[i].id == var_3) index_3 = i;
        }

        if(index_1 == -1 || index_2 == -1)
        {
            //Выкинуть эксепшен
        }
        else
        {
            if(index_3 == -1)
            {
                Var var;
                var.id = var_3;
                var.value = vars[index_1].value - vars[index_2].value;
                vars.push_back(var);
            }
            else
            {
                vars[index_3].value =  vars[index_1].value - vars[index_2].value;
            }
        }
    }

    if(operationName == "*")
    {
        QString line =  lines[index];
        QString var_1 = "";
        QString var_2 = "";
        QString var_3 = "";

        int i;
        for(i = 2; i<line.length();i++)
        {
            if(line[i] == ' ') break;
            else
                var_1 += (QString)line[i];
        }

        int j;
        for(j = i+1; j<line.length();j++)
        {
            if(line[j] == ' ') break;
            else
                var_2 += (QString)line[j];
        }

        int k;
        for(k = j+1; k<line.length();k++)
        {
            if(line[k] == '\n' || line[k] == ' ') break;
            else
                var_3 += (QString)line[k];
        }

        int index_1 = -1;
        int index_2 = -1;
        int index_3 = -1;


        for(int i = 0;i<vars.size();++i)
        {
            if(vars[i].id == var_1) index_1 = i;
            if(vars[i].id == var_2) index_2 = i;
            if(vars[i].id == var_3) index_3 = i;
        }

        if(index_1 == -1 || index_2 == -1)
        {
            //Выкинуть эксепшен
        }
        else
        {
            if(index_3 == -1)
            {
                Var var;
                var.id = var_3;
                var.value = vars[index_1].value * vars[index_2].value;
                vars.push_back(var);
            }
            else
            {
                vars[index_3].value =  vars[index_1].value * vars[index_2].value;
            }
        }
    }


    if(operationName == "/")
    {
        QString line =  lines[index];
        QString var_1 = "";
        QString var_2 = "";
        QString var_3 = "";

        int i;
        for(i = 2; i<line.length();i++)
        {
            if(line[i] == ' ') break;
            else
                var_1 += (QString)line[i];
        }

        int j;
        for(j = i+1; j<line.length();j++)
        {
            if(line[j] == ' ') break;
            else
                var_2 += (QString)line[j];
        }

        int k;
        for(k = j+1; k<line.length();k++)
        {
            if(line[k] == '\n' || line[k] == ' ') break;
            else
                var_3 += (QString)line[k];
        }

        int index_1 = -1;
        int index_2 = -1;
        int index_3 = -1;


        for(int i = 0;i<vars.size();++i)
        {
            if(vars[i].id == var_1) index_1 = i;
            if(vars[i].id == var_2) index_2 = i;
            if(vars[i].id == var_3) index_3 = i;
        }

        if(index_1 == -1 || index_2 == -1)
        {
            //Выкинуть эксепшен
        }
        else
        {
            if(index_3 == -1)
            {
                Var var;
                var.id = var_3;
                var.value = vars[index_1].value / vars[index_2].value;
                vars.push_back(var);
            }
            else
            {
                vars[index_3].value =  vars[index_1].value / vars[index_2].value;
            }
        }
    }
}

void Launcher::setIf()
{
    QString line = lines[index];
    QString var1 = "";
    QString var2 = "";
    Var var_1;
    Var var_2;

    //Считываем строку первой переменной
    int i;
    for(i = 3; i<line.length();i++)
    {
        if(line[i] == ' ') break;
        else
            var1 += (QString)line[i];
    }

    //Проверяем, есть ли эта переменная в стеке
    //Если есть, то получаем ее индекс и создаем ее
    //Если нет, ты выбрасываем исключение
    int n = -1;
    for(int i(0); i<vars.size(); ++i)
    {
        if(vars[i].id == var1)
            n = i;
    }
    if(n != -1)
    {
        var_1.id = vars[n].id;
        var_1.value = vars[n].value;
    }
    else
    {
        //Exeption
        cout<<"this is first variable not found";
        cout<<endl;
    }

    //Узнаем знак условия
    QString ifName = "";
    int j;
    for(j = i+1; j<line.length();j++)
    {
        if(line[j] == ' ') break;
        else
            ifName += (QString)line[j];
    }

    //Получаем вторую переменную, и проверяем ее так же как и первую
    int k;
    for(k = j+1; j<line.length();k++)
    {
        if(line[k] == ' ') break;
        else
            var2 += (QString)line[k];
    }

    n = -1;
    for(int i(0); i<vars.size(); ++i)
    {
        if(vars[i].id == var2)
            n = i;
    }
    if(n != -1)
    {
        var_2.id = vars[n].id;
        var_2.value = vars[n].value;
    }
    else
    {
        //Exeption
        cout<<"this is second variable not found";
        cout<<endl;
    }


    //Далее узнаем имя метки, куда перенаправить исполнение
    QString jmp_str = "";
    int l;
    for(l = k+1; l<line.length();l++)
    {
        if(line[l] == ' ' || line[l] == '\n') break;
        else
            jmp_str += (QString)line[l];
    }

    //переводим метку в число
    int jmp = jmp_str.toInt();


    if(ifName == "="){

        if(var_1.value == var_2.value)
            jump(jmp);
        else
            nextLine();
    }

    if(ifName == "!=")
    {
        if(var_1.value != var_2.value)
            jump(jmp);
        else
            nextLine();
    }

    if(ifName == ">")
    {
        if(var_1.value > var_2.value)
            jump(jmp);
        else
            nextLine();
    }

    if(ifName == "<")
    {
        if(var_1.value < var_2.value)
            jump(jmp);
        else
            nextLine();
    }

    if(ifName == "<=")
    {
        if(var_1.value <= var_2.value)
            jump(jmp);
        else
            nextLine();
    }

    if(ifName == ">=")
    {
        if(var_1.value >= var_2.value)
            jump(jmp);
        else
            nextLine();
    }
}

void Launcher::nextLine()
{
    index++;
}

void Launcher::setLabels()
{
    for(int i(0); i<lines.size();++i)
    {
        QString line = lines[i];
        if(line[0] == ':')
        {
            QString labelName = "";
            for(int i = 2; i<line.length();++i)
            {
                if(line[i] == ' ' || line[i] == '\n')
                    break;
                else
                {
                    labelName+=(QString)line[i];
                }
            }

            int value = labelName.toInt();
            QPair<int,int> pair;
            pair.first = i;
            pair.second = value;
            labels.push_back(pair);
        }
    }
}

void Launcher::jump(int jmp)
{
    for(int i(0); i<labels.size();++i)
    {
        if(labels[i].second == jmp)
        {
            this->index = labels[i].first;
        }
    }

}

void Launcher::outOnConsole()
{
    QString line =  lines[index];
    QString id = "";
    int i;
    for(i = 2; i<line.length();i++)
    {
        if(line[i] == '\n' || line[i] == ' ') break;
        else
            id += (QString)line[i];
    }

    for(int i = 0; i<vars.size();++i)
    {
        if(id == vars[i].id)
        {
            cout<<vars[i].value;
            cout<<endl;
        }
    }

}

void Launcher::inConsole()
{
    QString line =  lines[index];
    QString id = "";

    for(int i = 6; i<line.length();i++)
    {
        if(line[i] == '\n' || line[i] == ' ') break;
        else
            id += (QString)line[i];
    }

    int value;
    cin>>value;
    cout<<endl;

    int n = -1;
    for(int i(0); i<vars.size();++i)
    {
        if(vars[i].id == id) n = i;
    }

    if(n != -1)
    {
        vars[n].value = value;
    }
    else
    {
        Var var;
        var.id = id;
        var.value = value;
        vars.push_back(var);
    }
}

void Launcher::f_sqrt()
{
    QString line = lines[index];
    QString var1 = "";
    QString var2 = "";

    //Считываем строку первой переменной
    int i;
    for(i = 5; i<line.length();++i)
    {
        if(line[i] == ' ') break;
        else
            var1 += (QString)line[i];
    }

    //Считываем строку второй переменной
    int j;
    for(j = i+1; j<line.length();++j)
    {
        if(line[j] == ' ' || line[j] == '\n') break;
        else
            var2 += (QString)line[j];
    }

    int index_1 = -1;
    int index_2 = -1;

    //Проверяем, есть ли эти переменные
    for(int n = 0; n<vars.size(); ++n)
    {
        if(vars[n].id == var1) index_1 = n;
        if(vars[n].id == var2) index_2 = n;
    }

    if(index_1 != -1 && index_2 != -1)
    {
        vars[index_2].value = (float)sqrt(vars[index_1].value);
    }
    else
    {

        if(index_1 != -1 && index_2 == -1)
        {
            Var var;
            var.id = var2;
            var.value = (float)sqrt(vars[index_1].value);
            vars.push_back(var);
        }
        else
        {
        cout<<"variables is not found";
        cout<<endl;
        }
    }

}

void Launcher::outOnConsoleMessage()
{
     QString line = lines[index];

     QString msg = "";

     //Считываем строку первой переменной
     int i;
     for(i = 4; i<line.length();++i)
     {
         if(line[i] == ' ' || line[i] == '\n') break;
         else
             msg += (QString)line[i];
     }

     cout<<msg.toStdString();
     cout<<endl;

}
