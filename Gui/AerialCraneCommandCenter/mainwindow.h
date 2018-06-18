#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/c_library_v1/ardupilotmega/mavlink.h"

#include "connection.h"
#include "decodemavpackets.h"
#include "vehicle.h"

#define MAX_MAV_VEHICLES    3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connect_helicopter1(void);
    void connect_helicopter2(void);
    void disconnect_helicopter1(void);
    void disconnect_helicopter2(void);

    void switchGuidedMode1(void);
    void takeoff1(void);
    void setArm1(void);
    void setStream1(void);
    void land1();

    void update_attitude1(const mavlink_attitude_t * mav_att);
    void update_ahrs1(const mavlink_ahrs2_t * mav_ahrs2);
    void update_gps1(const mavlink_global_position_int_t *mavlink_global_position_int);
    void update_gps_raw1(const mavlink_gps_raw_int_t *mavlink_gps_raw_int);
    void update_heartbeat1(const mavlink_heartbeat_t *mavlink_heartbeat);
    void update_local_position1(const mavlink_local_position_ned_t *mavlink_local_position_ned);
private:
    Ui::MainWindow *ui;
    Vehicle *vehicles[MAX_MAV_VEHICLES];
};

#endif // MAINWINDOW_H
