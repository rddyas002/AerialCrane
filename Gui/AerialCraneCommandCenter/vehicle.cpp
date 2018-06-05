#include "vehicle.h"

Vehicle::Vehicle(uint32_t port)
{
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(QHostAddress::LocalHost, port);
    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Vehicle::readData()
{
    while (udp_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        for (int i = 0; i < datagram.data().length(); i++){
            if (mavlink_parse_char(MAVLINK_COMM_0, datagram.data()[i], &msg, &status)){
                printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msg.msgid, msg.seq, msg.compid, msg.sysid);

                if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT){
                    mavlink_heartbeat_t mavlink_heartbeat;
                    mavlink_msg_heartbeat_decode(&msg, &mavlink_heartbeat);
                    printf("Received Heartbeat from ID: %u TYPE: %u AUTOPILOT: %u.\r\n",
                           msg.sysid,
                           mavlink_heartbeat.type,
                           mavlink_heartbeat.autopilot);

                }
          }
        }
    }
}

Vehicle::~Vehicle()
{
    delete udp_socket;
}
