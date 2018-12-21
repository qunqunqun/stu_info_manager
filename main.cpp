#include "mainwindow.h"
#include <QApplication>
#include <login.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    login * t = new login();
    t->exec();
    while(true)
    {
        if(t->get_is_ret() == false)
        {
            return 0;
        }
        else if(t->get_is_correct() == false) //密码不正确
        {
            delete t;
            t = new login();
            t->exec();
        }
        else break;
    }
    return a.exec();
}
