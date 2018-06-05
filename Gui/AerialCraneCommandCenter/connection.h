#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(const char * host_address, uint32_t port);
    ~Connection();

signals:
    void MavLinkPacketReceived(const mavlink_message_t * msg);

public slots:
    void readData();

private:
    QUdpSocket * udp_socket;
    mavlink_message_t msg;
    mavlink_status_t status;
};

#endif // CONNECTION_H
