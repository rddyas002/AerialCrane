#ifndef DECODEMAVPACKETS_H
#define DECODEMAVPACKETS_H

#include <QObject>
#include "connection.h"
#include "lib/c_library_v1/ardupilotmega/mavlink.h"

#define RAD2DEG(X)      (X*180.0/M_PI)

class DecodeMavPackets : public QObject
{
    Q_OBJECT
public:
    explicit DecodeMavPackets(Connection * connection);
    void handle_MAVLINK_MSG_ID_HEARTBEAT(const mavlink_message_t * msg, const qint64 timestamp);
    void handle_MAVLINK_MSG_ID_SYS_STATUS(const mavlink_message_t * msg, const qint64 timestamp);
    void handle_MAVLINK_MSG_ID_SYSTEM_TIME(const mavlink_message_t * msg, const qint64 timestamp);
    void handle_MAVLINK_MSG_ID_ATTITUDE(const mavlink_message_t * msg, const qint64 timestamp);
    void handle_MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE(const mavlink_message_t * msg, const qint64 timestamp);
signals:
    void StringToUi(const QString string, const qint64 timestamp);
public slots:
    void decodePacket(const mavlink_message_t * msg, const qint64 timestamp);
private:
    void emitStringSignal(const QString message, const qint64 timestamp);

    mavlink_attitude_t mavlink_attitude_pvt;
    mavlink_control_system_state_t mavlink_control_system_state;
};

#endif // DECODEMAVPACKETS_H
