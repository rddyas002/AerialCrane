#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QElapsedTimer>

#include "lib/c_library_v1/ardupilotmega/mavlink.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(uint32_t port, uint8_t channel);
    qint64 transmit(const char *data, qint64 size);
    ~Connection();

signals:
    void MavLinkPacketReceived(const mavlink_message_t *msg, const qint64 timestamp);

public slots:
    void readData();

private:
    QElapsedTimer timer;
    QUdpSocket * udp_socket;
    mavlink_message_t msg;
    mavlink_status_t status;
    bool first_connect;
    uint8_t mav_channel;

    QHostAddress hostAddress;
    QHostAddress senderAddress;
    quint16 senderPort;
    uint32_t udp_port;
};

#endif // CONNECTION_H
