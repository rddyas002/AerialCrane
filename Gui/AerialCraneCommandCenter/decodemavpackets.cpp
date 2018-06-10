#include "decodemavpackets.h"
#include <QDebug>

DecodeMavPackets::DecodeMavPackets(Connection * connection)
{
    connect(connection, SIGNAL(MavLinkPacketReceived(const mavlink_message_t *, const qint64)),
            this, SLOT(decodePacket(const mavlink_message_t *, const qint64)));
}

void DecodeMavPackets::emitStringSignal(const QString message, const qint64 timestamp){
    emit DecodeMavPackets::StringToUi(message, timestamp);
}

void DecodeMavPackets::decodePacket(const mavlink_message_t * msg, const qint64 timestamp){
//    qDebug() << "MAV" << msg->sysid;
//    qDebug() << (double)timestamp/1e3;
    switch (msg->msgid){
    case MAVLINK_MSG_ID_HEARTBEAT:
        //qDebug() << "MAVLINK_MSG_ID_HEARTBEAT";
        handle_MAVLINK_MSG_ID_HEARTBEAT(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_SYS_STATUS:
        //qDebug() << "MAVLINK_MSG_ID_SYS_STATUS";
        handle_MAVLINK_MSG_ID_SYS_STATUS(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_SYSTEM_TIME:
        //qDebug() << "MAVLINK_MSG_ID_SYSTEM_TIME";
        handle_MAVLINK_MSG_ID_SYSTEM_TIME(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT:
        //qDebug() << "MAVLINK_MSG_ID_GPS_RAW_INT";
        break;
    case MAVLINK_MSG_ID_RAW_IMU:
        //qDebug() << "MAVLINK_MSG_ID_RAW_IMU";
        break;
    case MAVLINK_MSG_ID_SCALED_PRESSURE:
        //qDebug() << "MAVLINK_MSG_ID_SCALED_PRESSURE";
        break;
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        //qDebug() << "MAVLINK_MSG_ID_GLOBAL_POSITION_INT";
        break;
    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
        //qDebug() << "MAVLINK_MSG_ID_RC_CHANNELS_RAW";
        break;
    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
        //qDebug() << "MAVLINK_MSG_ID_SERVO_OUTPUT_RAW";
        break;
    case MAVLINK_MSG_ID_ATTITUDE:
        //qDebug() << "MAVLINK_MSG_ID_ATTITUDE";
        handle_MAVLINK_MSG_ID_ATTITUDE(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
        //qDebug() << "MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT";
        break;
    case MAVLINK_MSG_ID_VFR_HUD:
        //qDebug() << "MAVLINK_MSG_ID_VFR_HUD";
        break;
    case MAVLINK_MSG_ID_MISSION_CURRENT:
        //qDebug() << "MAVLINK_MSG_ID_MISSION_CURRENT";
        break;
    case MAVLINK_MSG_ID_TERRAIN_REQUEST:
        //qDebug() << "MAVLINK_MSG_ID_TERRAIN_REQUEST";
        break;
    case MAVLINK_MSG_ID_TERRAIN_REPORT:
        //qDebug() << "MAVLINK_MSG_ID_TERRAIN_REPORT";
        break;
    case MAVLINK_MSG_ID_SCALED_IMU2:
        //qDebug() << "MAVLINK_MSG_ID_SCALED_IMU2";
        break;
        // ArdupiloMegaSpecific
    case MAVLINK_MSG_ID_MEMINFO:
        //qDebug() << "MAVLINK_MSG_ID_MEMINFO";
        break;
    case MAVLINK_MSG_ID_AHRS:
        //qDebug() << "MAVLINK_MSG_ID_AHRS";
        break;
    case MAVLINK_MSG_ID_SIMSTATE:
        //qDebug() << "MAVLINK_MSG_ID_SIMSTATE";
        break;
    case MAVLINK_MSG_ID_HWSTATUS:
        //qDebug() << "MAVLINK_MSG_ID_HWSTATUS";
        break;
    case MAVLINK_MSG_ID_AHRS2:
        //qDebug() << "MAVLINK_MSG_ID_AHRS2";
        break;
    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:
        //qDebug() << "MAVLINK_MSG_ID_EKF_STATUS_REPORT";
        break;
    case MAVLINK_MSG_ID_SENSOR_OFFSETS:
        //qDebug() << "MAVLINK_MSG_ID_SENSOR_OFFSETS";
        break;
    case MAVLINK_MSG_ID_VIBRATION:
        //qDebug() << "MAVLINK_MSG_ID_VIBRATION";
        break;
    case MAVLINK_MSG_ID_PARAM_VALUE:
        //qDebug() << "MAVLINK_MSG_ID_PARAM_VALUE";
        break;
    case MAVLINK_MSG_ID_RC_CHANNELS:
        //qDebug() << "MAVLINK_MSG_ID_RC_CHANNELS";
        break;
    case MAVLINK_MSG_ID_POWER_STATUS:
        //qDebug() << "MAVLINK_MSG_ID_POWER_STATUS";
        break;
    case MAVLINK_MSG_ID_BATTERY_STATUS:
        //qDebug() << "MAVLINK_MSG_ID_BATTERY_STATUS";
        break;
    case MAVLINK_MSG_ID_AHRS3:
        //qDebug() << "MAVLINK_MSG_ID_AHRS3";
        break;
    case MAVLINK_MSG_ID_RADIO_STATUS:
        //qDebug() << "MAVLINK_MSG_ID_RADIO_STATUS";
        break;
        default:
            qDebug() << "MSG ID: " << msg->msgid << "MSG LEN: " << msg->len;

    }
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_HEARTBEAT(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_heartbeat_t mavlink_heartbeat;
    mavlink_msg_heartbeat_decode(msg, &mavlink_heartbeat);
    qDebug() << timestamp << "us: [HEARTBEAT] AUTOPILOT: " << mavlink_heartbeat.autopilot <<
    " MAVLINK VERSION: " << mavlink_heartbeat.mavlink_version <<
    " SYSTEM STATUS: " << mavlink_heartbeat.system_status <<
    " BASE MODE: " << mavlink_heartbeat.base_mode <<
    " TYPE: " << mavlink_heartbeat.type;
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYS_STATUS(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_sys_status_t mavlink_sys_status;
    mavlink_msg_sys_status_decode(msg, &mavlink_sys_status);
    qDebug() << timestamp << "us: [STATUS] BATTERY VOLTAGE: " << mavlink_sys_status.voltage_battery <<
    " COMM ERROR: " << mavlink_sys_status.errors_comm;
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYSTEM_TIME(const mavlink_message_t * msg, const qint64 timestamp){
    qDebug() << timestamp << "us: [SYSTEM_TIME] USEC UNIX: " << mavlink_msg_system_time_get_time_unix_usec(msg) <<
    " TIME SINCE BOOT MS: " << mavlink_msg_system_time_get_time_boot_ms(msg);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_ATTITUDE(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_msg_attitude_decode(msg, &mavlink_attitude_pvt);

    qDebug() << timestamp << "us: [ATTITUDE] ROLL: " << RAD2DEG(mavlink_attitude_pvt.roll) <<
    " ROLLSPEED: " << RAD2DEG(mavlink_attitude_pvt.rollspeed) <<
    " PITCH: " << RAD2DEG(mavlink_attitude_pvt.pitch) <<
    " PITCHSPEED: " << RAD2DEG(mavlink_attitude_pvt.pitchspeed) <<
    " YAW: " << RAD2DEG(mavlink_attitude_pvt.yaw) <<
    " YAWSPEED: " << RAD2DEG(mavlink_attitude_pvt.yawspeed);
}

