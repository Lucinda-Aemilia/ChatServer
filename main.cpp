#include "mainwindow.h"
#include "configdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ConfigDialog dialog;
    int ret = dialog.exec();
    if (!ret)
        return 0;

    MainWindow w(dialog.getAddress(), dialog.getPort());
    w.show();

    return a.exec();
}
