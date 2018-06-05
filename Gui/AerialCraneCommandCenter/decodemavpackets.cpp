#include "decodemavpackets.h"
#include <QDebug>

DecodeMavPackets::DecodeMavPackets(Connection * connection)
{
    connect(connection, SIGNAL(MavLinkPacketReceived(const mavlink_message_t *)),
            this, SLOT(decodePacket(const mavlink_message_t *)));
}

void DecodeMavPackets::decodePacket(const mavlink_message_t * msg){
    switch (msg->msgid){
    case MAVLINK_MSG_ID_HEARTBEAT:
        handle_MAVLINK_MSG_ID_HEARTBEAT(msg);
        break;
    case MAVLINK_MSG_ID_SYS_STATUS:
        handle_MAVLINK_MSG_ID_SYS_STATUS(msg);
        break;
    case MAVLINK_MSG_ID_SYSTEM_TIME:
        handle_MAVLINK_MSG_ID_SYSTEM_TIME(msg);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT:
        break;
    case MAVLINK_MSG_ID_RAW_IMU:
        break;
    case MAVLINK_MSG_ID_SCALED_PRESSURE:
        break;
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        break;
    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
        break;
    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
        break;
    case MAVLINK_MSG_ID_ATTITUDE:
        break;
    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
        break;
    case MAVLINK_MSG_ID_VFR_HUD:
        break;
    case MAVLINK_MSG_ID_MISSION_CURRENT:
        break;
    case MAVLINK_MSG_ID_TERRAIN_REQUEST:
        break;
    case MAVLINK_MSG_ID_TERRAIN_REPORT:
        break;
    case MAVLINK_MSG_ID_SCALED_IMU2:
        break;
        // ArdupiloMegaSpecific
    case MAVLINK_MSG_ID_MEMINFO:
        break;
    case MAVLINK_MSG_ID_AHRS:
        break;
    case MAVLINK_MSG_ID_SIMSTATE:
        break;
    case MAVLINK_MSG_ID_HWSTATUS:
        break;
    case MAVLINK_MSG_ID_AHRS2:
        break;
    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:
        break;
    case MAVLINK_MSG_ID_SENSOR_OFFSETS:
        break;
    case MAVLINK_MSG_ID_VIBRATION:
        break;
        default:
            qDebug() << "MSG ID: " << msg->msgid << "MSG LEN: " << msg->len;

    }
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_HEARTBEAT(const mavlink_message_t * msg){
    mavlink_heartbeat_t mavlink_heartbeat;
    mavlink_msg_heartbeat_decode(msg, &mavlink_heartbeat);
    qDebug() << "[HEARTBEAT]AUTOPILOT: " << mavlink_heartbeat.autopilot;
    qDebug() << "[HEARTBEAT]MAVLINK VERSION: " << mavlink_heartbeat.mavlink_version;
    qDebug() << "[HEARTBEAT]SYSTEM STATUSx: " << mavlink_heartbeat.system_status;
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYS_STATUS(const mavlink_message_t * msg){
    mavlink_sys_status_t mavlink_sys_status;
    mavlink_msg_sys_status_decode(msg, &mavlink_sys_status);
    qDebug() << "[STATUS]BATTERY VOLTAGE: " << mavlink_sys_status.voltage_battery;
    qDebug() << "[STATUS]COMM ERROR: " << mavlink_sys_status.errors_comm;
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYSTEM_TIME(const mavlink_message_t * msg){
    qDebug() << "[SYSTEM_TIME]USEC UNIX: " << mavlink_msg_system_time_get_time_unix_usec(msg);
    qDebug() << "[SYSTEM_TIME]TIME SINCE BOOT MS: " << mavlink_msg_system_time_get_time_boot_ms(msg);
}
