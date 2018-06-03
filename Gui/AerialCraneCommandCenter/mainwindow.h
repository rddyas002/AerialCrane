#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

#define MAVLINK_UDP_PORT    14551

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void serialReceived();
    void readPendingDatagrams();

private:
    void processDataReceived(QByteArray ba);

    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QUdpSocket *udpSocket;
    mavlink_message_t msg;
    mavlink_status_t status;
};

#endif // MAINWINDOW_H
