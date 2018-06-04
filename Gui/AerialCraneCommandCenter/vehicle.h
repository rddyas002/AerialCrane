#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"


class Vehicle : public QObject{
   Q_OBJECT
public:
    Vehicle(uint32_t port);
    ~Vehicle();
public slots:
    void readData();

private:
    QUdpSocket * udp_socket;
    mavlink_message_t msg;
    mavlink_status_t status;

};

#endif // VEHICLE_H
