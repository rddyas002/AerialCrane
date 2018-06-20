#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageProcessing *imProc = new ImageProcessing();
    MainWindow w(0, imProc);
    w.show();

    return a.exec();
}
