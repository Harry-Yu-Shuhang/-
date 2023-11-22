#include "input.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    input w_i;
    w_i.show();
    return a.exec();
}
