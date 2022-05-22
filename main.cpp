#include "asciiartmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ASCIIArtMenu w;
    w.show();
    return a.exec();
}
