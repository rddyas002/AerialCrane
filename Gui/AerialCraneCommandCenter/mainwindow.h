#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

#include "connection.h"
#include "decodemavpackets.h"
#include "vehicle.h"

#define MAX_MAV_VEHICLES    3
#define MAVLINK_UDP_IP      "10.24.5.30"
#define MAVLINK_UDP_LOCAL   "127.0.0.1"
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

private:
    Ui::MainWindow *ui;
    Connection *mav_vehicles[MAX_MAV_VEHICLES];
    Vehicle *vehicles[MAX_MAV_VEHICLES];
    DecodeMavPackets *decode[MAX_MAV_VEHICLES];
};

#endif // MAINWINDOW_H
