#include "decodemavpackets.h"
#include <QDebug>

DecodeMavPackets::DecodeMavPackets(Connection * connection)
{
    connect(connection, SIGNAL(connection->MavLinkPacketReceived(mavlink_message_t*)), this, SLOT(decodePacket(mavlink_message_t*)));
}

void DecodeMavPackets::decodePacket(const mavlink_message_t * msg){
    if (msg->msgid == MAVLINK_MSG_ID_HEARTBEAT){
        mavlink_heartbeat_t mavlink_heartbeat;
        mavlink_msg_heartbeat_decode(msg, &mavlink_heartbeat);
        qDebug() << "Received Heartbeat from ID: " << msg->sysid <<
                    " TYPE: " << mavlink_heartbeat.type <<
                    " Autopilot: " << mavlink_heartbeat.autopilot;
    }
}
