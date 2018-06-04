#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

#define MAVLINK_UDP_PORT1    14560
#define MAVLINK_UDP_PORT2    14570

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
    void readPendingDatagramsSocket1();
    void readPendingDatagramsSocket2();

private:

    Ui::MainWindow *ui;

    QUdpSocket *udpSocket[2];
    mavlink_message_t msg[2];
    mavlink_status_t status[2];
};

#endif // MAINWINDOW_H
