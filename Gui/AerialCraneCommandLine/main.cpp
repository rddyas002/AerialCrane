#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSerialPort serial;
    printf("Hello world!\n");

    return a.exec();
}
