#include "decodemavpackets.h"
#include <QDebug>

//#define QDEBUG_OUT

DecodeMavPackets::DecodeMavPackets(Connection * connection){
    connect(connection, SIGNAL(MavLinkPacketReceived(const mavlink_message_t *, const qint64)),
            this, SLOT(decodePacket(const mavlink_message_t *, const qint64)));
}

void DecodeMavPackets::emitStringSignal(const QString message, const qint64 timestamp){
    emit DecodeMavPackets::StringToUi(message, timestamp);
}

void DecodeMavPackets::decodePacket(const mavlink_message_t * msg, const qint64 timestamp){
   // qDebug() << "SYSID: " << msg->sysid;
    switch (msg->msgid){
    case MAVLINK_MSG_ID_HEARTBEAT:
        //qDebug() << "MAVLINK_MSG_ID_HEARTBEAT";
        handle_MAVLINK_MSG_ID_HEARTBEAT(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_SYS_STATUS:
        qDebug() << "MAVLINK_MSG_ID_SYS_STATUS";
        //handle_MAVLINK_MSG_ID_SYS_STATUS(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_SYSTEM_TIME:
        qDebug() << "MAVLINK_MSG_ID_SYSTEM_TIME";
        //handle_MAVLINK_MSG_ID_SYSTEM_TIME(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_GPS_RAW_INT:
        qDebug() << "MAVLINK_MSG_ID_GPS_RAW_INT";
        handle_MAVLINK_MSG_ID_GPS_RAW_INT(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_RAW_IMU:
        qDebug() << "MAVLINK_MSG_ID_RAW_IMU";
        break;
    case MAVLINK_MSG_ID_SCALED_PRESSURE:
        qDebug() << "MAVLINK_MSG_ID_SCALED_PRESSURE";
        break;
    case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
        handle_MAVLINK_MSG_ID_GLOBAL_POSITION_INT(msg, timestamp);
        //qDebug() << "MAVLINK_MSG_ID_GLOBAL_POSITION_INT";
        break;
    case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
        qDebug() << "MAVLINK_MSG_ID_RC_CHANNELS_RAW";
        break;
    case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
        qDebug() << "MAVLINK_MSG_ID_SERVO_OUTPUT_RAW";
        break;
    case MAVLINK_MSG_ID_ATTITUDE:
        //qDebug() << "MAVLINK_MSG_ID_ATTITUDE";
        handle_MAVLINK_MSG_ID_ATTITUDE(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
        qDebug() << "MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT";
        break;
    case MAVLINK_MSG_ID_VFR_HUD:
        qDebug() << "MAVLINK_MSG_ID_VFR_HUD";
        break;
    case MAVLINK_MSG_ID_MISSION_CURRENT:
        qDebug() << "MAVLINK_MSG_ID_MISSION_CURRENT";
        break;
    case MAVLINK_MSG_ID_TERRAIN_REQUEST:
        qDebug() << "MAVLINK_MSG_ID_TERRAIN_REQUEST";
        break;
    case MAVLINK_MSG_ID_TERRAIN_REPORT:
        qDebug() << "MAVLINK_MSG_ID_TERRAIN_REPORT";
        break;
    case MAVLINK_MSG_ID_SCALED_IMU2:
        qDebug() << "MAVLINK_MSG_ID_SCALED_IMU2";
        break;
        // ArdupiloMegaSpecific
    case MAVLINK_MSG_ID_MEMINFO:
        qDebug() << "MAVLINK_MSG_ID_MEMINFO";
        break;
    case MAVLINK_MSG_ID_AHRS:
        qDebug() << "MAVLINK_MSG_ID_AHRS";
        break;
    case MAVLINK_MSG_ID_SIMSTATE:
        qDebug() << "MAVLINK_MSG_ID_SIMSTATE";
        break;
    case MAVLINK_MSG_ID_HWSTATUS:
        qDebug() << "MAVLINK_MSG_ID_HWSTATUS";
        break;
    case MAVLINK_MSG_ID_AHRS2:
        handle_MAVLINK_MSG_ID_AHRS2(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_EKF_STATUS_REPORT:
        qDebug() << "MAVLINK_MSG_ID_EKF_STATUS_REPORT";
        break;
    case MAVLINK_MSG_ID_SENSOR_OFFSETS:
        qDebug() << "MAVLINK_MSG_ID_SENSOR_OFFSETS";
        break;
    case MAVLINK_MSG_ID_VIBRATION:
        qDebug() << "MAVLINK_MSG_ID_VIBRATION";
        break;
    case MAVLINK_MSG_ID_PARAM_VALUE:
        qDebug() << "MAVLINK_MSG_ID_PARAM_VALUE";
        break;
    case MAVLINK_MSG_ID_RC_CHANNELS:
        qDebug() << "MAVLINK_MSG_ID_RC_CHANNELS";
        break;
    case MAVLINK_MSG_ID_POWER_STATUS:
        qDebug() << "MAVLINK_MSG_ID_POWER_STATUS";
        break;
    case MAVLINK_MSG_ID_BATTERY_STATUS:
        qDebug() << "MAVLINK_MSG_ID_BATTERY_STATUS";
        break;
    case MAVLINK_MSG_ID_AHRS3:
        qDebug() << "MAVLINK_MSG_ID_AHRS3";
        break;
    case MAVLINK_MSG_ID_RADIO_STATUS:
        qDebug() << "MAVLINK_MSG_ID_RADIO_STATUS";
        break;
    case MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE:
        handle_MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE(msg, timestamp);
        qDebug() << "MAVLINK_MSG_ID_RADIO_STATUS";
        break;
    case MAVLINK_MSG_ID_STATUSTEXT:
        handle_MAVLINK_MSG_ID_STATUSTEXT(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_COMMAND_ACK:
        handle_MAVLINK_MSG_ID_COMMAND_ACK(msg, timestamp);
        break;
    case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
        handle_MAVLINK_MSG_ID_LOCAL_POSITION_NED(msg, timestamp);
        break;
        default:
            qDebug() << "MSG ID: " << msg->msgid << "MSG LEN: " << msg->len;

    }
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_LOCAL_POSITION_NED(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_local_position_ned_t mavlink_local_position_ned;
    mavlink_msg_local_position_ned_decode(msg, &mavlink_local_position_ned);
    emit local_position_update_received(&mavlink_local_position_ned);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_GPS_RAW_INT(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_gps_raw_int_t mavlink_gps_raw_int;
    mavlink_msg_gps_raw_int_decode(msg, &mavlink_gps_raw_int);
    emit gps_raw_update_received(&mavlink_gps_raw_int);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_STATUSTEXT(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_statustext_t mavlink_statustext;
    mavlink_msg_statustext_decode(msg, &mavlink_statustext);
    qDebug() << "STATUS_EXT: Serverity " << mavlink_statustext.severity << " " << mavlink_statustext.text;
    emit statusext_update_received(&mavlink_statustext);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_COMMAND_ACK(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_msg_command_ack_decode(msg, &mavlink_command_ack);
    qDebug() << "Command ID: " << mavlink_command_ack.command << " Result: " << mavlink_command_ack.result;
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_GLOBAL_POSITION_INT(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_global_position_int_t mavlink_global_position_int;
    mavlink_msg_global_position_int_decode(msg, &mavlink_global_position_int);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [GLOBAL_POSITION_INT] TIMEBOOT(ms): " << mavlink_global_position_int.time_boot_ms <<
                "alt: " << mavlink_global_position_int.alt <<
                "lat: " << mavlink_global_position_int.lat <<
                "lon: " << mavlink_global_position_int.lon <<
                "hdg: " << mavlink_global_position_int.hdg <<
                "relative_alt: " << mavlink_global_position_int.relative_alt <<
                "vx: " << mavlink_global_position_int.vx <<
                "vy: " << mavlink_global_position_int.vy <<
                "vz: " << mavlink_global_position_int.vz;
#endif
    emit gps_update_received(&mavlink_global_position_int);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_msg_control_system_state_decode(msg, &mavlink_control_system_state);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [CONTROL_SYSTEM_STATE] TIMESTAMP(us): " << mavlink_control_system_state.time_usec <<
                "x_acc: " << mavlink_control_system_state.x_acc <<
                "y_acc: " << mavlink_control_system_state.y_acc <<
                "z_acc: " << mavlink_control_system_state.z_acc <<
                "x_vel: " << mavlink_control_system_state.x_vel <<
                "y_vel: " << mavlink_control_system_state.y_vel <<
                "z_vel: " << mavlink_control_system_state.z_vel <<
                "x_pos: " << mavlink_control_system_state.x_pos <<
                "y_pos: " << mavlink_control_system_state.y_pos <<
                "z_pos: " << mavlink_control_system_state.z_pos <<
                "roll_rate: " << mavlink_control_system_state.roll_rate <<
                "pitch_rate: " << mavlink_control_system_state.pitch_rate <<
                "yaw_rate: " << mavlink_control_system_state.yaw_rate <<
                "q0: " << mavlink_control_system_state.q[0] <<
                "q1: " << mavlink_control_system_state.q[1] <<
                "q2: " << mavlink_control_system_state.q[2] <<
                "q3: " << mavlink_control_system_state.q[3];
#endif
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_HEARTBEAT(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_heartbeat_t mavlink_heartbeat;
    mavlink_msg_heartbeat_decode(msg, &mavlink_heartbeat);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [HEARTBEAT] AUTOPILOT: " << mavlink_heartbeat.autopilot <<
    " MAVLINK VERSION: " << mavlink_heartbeat.mavlink_version <<
    " SYSTEM STATUS: " << mavlink_heartbeat.system_status <<
    " BASE MODE: " << mavlink_heartbeat.base_mode <<
    " CUSTOM MODE: " << mavlink_heartbeat.custom_mode <<
    " TYPE: " << mavlink_heartbeat.type;
#endif
    emit heartbeat_update_received(&mavlink_heartbeat);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYS_STATUS(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_sys_status_t mavlink_sys_status;
    mavlink_msg_sys_status_decode(msg, &mavlink_sys_status);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [STATUS] BATTERY VOLTAGE: " << mavlink_sys_status.voltage_battery <<
    " COMM ERROR: " << mavlink_sys_status.errors_comm;
#endif
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_SYSTEM_TIME(const mavlink_message_t * msg, const qint64 timestamp){
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [SYSTEM_TIME] USEC UNIX: " << mavlink_msg_system_time_get_time_unix_usec(msg) <<
    " TIME SINCE BOOT MS: " << mavlink_msg_system_time_get_time_boot_ms(msg);
#endif
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_ATTITUDE(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_msg_attitude_decode(msg, &mavlink_attitude_pvt);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [ATTITUDE] ROLL: " << RAD2DEG(mavlink_attitude_pvt.roll) <<
    " ROLLSPEED: " << RAD2DEG(mavlink_attitude_pvt.rollspeed) <<
    " PITCH: " << RAD2DEG(mavlink_attitude_pvt.pitch) <<
    " PITCHSPEED: " << RAD2DEG(mavlink_attitude_pvt.pitchspeed) <<
    " YAW: " << RAD2DEG(mavlink_attitude_pvt.yaw) <<
    " YAWSPEED: " << RAD2DEG(mavlink_attitude_pvt.yawspeed);
#endif
    emit attitude_update_received(&mavlink_attitude_pvt);
}

void DecodeMavPackets::handle_MAVLINK_MSG_ID_AHRS2(const mavlink_message_t * msg, const qint64 timestamp){
    mavlink_msg_ahrs2_decode(msg, &mavlink_ahrs2);
#ifdef QDEBUG_OUT
    qDebug() << timestamp << "us: [AHRS2] ROLL: " << RAD2DEG(mavlink_ahrs2.roll) <<
    " PITCH: " << RAD2DEG(mavlink_ahrs2.pitch) <<
    " YAW: " << RAD2DEG(mavlink_ahrs2.yaw) <<
    " ALTITUDE: " << mavlink_ahrs2.altitude <<
    " LATITUDE: " << mavlink_ahrs2.altitude <<
    " LONGITUDE: " << mavlink_ahrs2.altitude;
#endif
    emit ahrs_update_received(&mavlink_ahrs2);
}

