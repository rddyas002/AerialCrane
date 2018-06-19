#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ImageProcessing *imageProcessing = new ImageProcessing();
    imageProcessing->start(QThread::HighestPriority);
    w.show();

    return a.exec();
}
