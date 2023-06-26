#pragma execution_character_set("utf-8")
#include "Enter.h"
#include <QtWidgets/QApplication>
#include "Login.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Á¬½Ómysql
    if (!createMySqlConn())
    {
        return 1;
     }
    
    Enter w;
    Login lw;
    int result;
    result = lw.exec();
    if (result == 1)
    {
        
        w.show();
    }
    else
    {
        return result;
    }

    return a.exec();
   
}


