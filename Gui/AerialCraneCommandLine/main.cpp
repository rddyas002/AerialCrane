#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSerialPort *m_serial = new QSerialPort("mavSerial");

    printf("Hello world!\n");

    return a.exec();
}
