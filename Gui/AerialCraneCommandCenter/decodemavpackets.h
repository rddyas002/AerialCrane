#ifndef DECODEMAVPACKETS_H
#define DECODEMAVPACKETS_H

#include <QObject>
#include "connection.h"
#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

#define RAD2DEG(X)      (X*180.0/M_PI)

class DecodeMavPackets : public QObject
{
    Q_OBJECT
public:
    explicit DecodeMavPackets(Connection * connection);
    void handle_MAVLINK_MSG_ID_HEARTBEAT(const mavlink_message_t * msg);
    void handle_MAVLINK_MSG_ID_SYS_STATUS(const mavlink_message_t * msg);
    void handle_MAVLINK_MSG_ID_SYSTEM_TIME(const mavlink_message_t * msg);
    void handle_MAVLINK_MSG_ID_ATTITUDE(const mavlink_message_t * msg);
signals:

public slots:
    void decodePacket(const mavlink_message_t * msg, const qint64 timestamp);

};

#endif // DECODEMAVPACKETS_H
