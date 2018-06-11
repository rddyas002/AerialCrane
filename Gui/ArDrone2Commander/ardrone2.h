#ifndef ARDRONE2_H
#define ARDRONE2_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QElapsedTimer>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define YAW_RATE 4
#define THROTTLE_RATE 15000
#define PITCH_ROLL_RATE 1
#define ALTITUDE_MAX 10000
#define FLY_OUTDOOR "FALSE"

class ArDrone2 : public QObject{
    Q_OBJECT
public:
    explicit ArDrone2(const QString host_address, uint32_t port);
    void initialiseDrone(void);
    void sendData(QByteArray ba);
    void resetWatchdog(void);
    void flatTrim(void);
    void takeOff(float roll, float pitch, float heave_rate, float yaw_rate);
    void hoverControl(float roll, float pitch, float heave_rate, float yaw_rate);
    void flying(float roll, float pitch, float heave_rate, float yaw_rate);
    void land(void);
    virtual ~ArDrone2();

signals:

public slots:

private:
    QElapsedTimer timer;
    QUdpSocket * udp_socket;

    char buffer[200];
    int seq;
};

#endif // ARDRONE2_H
