#include "MyServer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyServer myserver(2323);
    myserver.show();
    return a.exec();
}
