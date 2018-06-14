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

private:
    Ui::MainWindow *ui;
    Vehicle *vehicles[MAX_MAV_VEHICLES];
};

#endif // MAINWINDOW_H
