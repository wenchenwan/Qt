#include "my_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    My_Widget w;
    w.show();

    return a.exec();
}
