#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QByteArray>
#include <QTimer>

#include "connection.h"
#include "decodemavpackets.h"

class Vehicle : public QObject{
   Q_OBJECT

public:
    Vehicle(const QString host_address, uint32_t port, uint8_t channel);
    ~Vehicle();

    void setMode(uint32_t mode);
    void mavCommandLong(uint16_t cmd, float param1, float param2, float param3, float param4, float param5, float param6, float param7);
    void mavTakeOff(float height);
    void mavLand(void);
    void defaultDataStreamRate(void);
    void setStreamRate(uint8_t stream_id, uint16_t frequency, uint8_t enable);
    void setIntervalRate(uint16_t message_id, int32_t interval_us);
    DecodeMavPackets * getDecoder(void);
public slots:
    void oneSecondTimer(void);

signals:

private:
    void mavSendHeartbeat(void);

    Connection *mav_vehicle;
    DecodeMavPackets *decode;
    QTimer *timer_1second;

    char transmit_buffer[MAVLINK_MAX_PACKET_LEN];
    uint8_t this_sysid;
    uint8_t this_compid;
    uint8_t target_sysid;
    uint8_t target_compid;

    float euler[3];
    float body_rates[3];
    float quaternion[4];
    float position_ned[3];
    float velocity_ned[3];
};

#endif // VEHICLE_H
