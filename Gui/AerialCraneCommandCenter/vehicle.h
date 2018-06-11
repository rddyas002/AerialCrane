#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QByteArray>

#include "connection.h"
#include "decodemavpackets.h"

class Vehicle : public QObject{
   Q_OBJECT

public:
    Vehicle(const QString host_address, uint32_t port);
    ~Vehicle();

public slots:

signals:

private:
    void requestControlStateStream(void);

    Connection *mav_vehicle;
    DecodeMavPackets *decode;

    char transmit_buffer[MAVLINK_MAX_PACKET_LEN];

    float euler[3];
    float body_rates[3];
    float quaternion[4];
    float position_ned[3];
    float velocity_ned[3];
};

#endif // VEHICLE_H
