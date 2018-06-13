#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    this_sysid = 250;
    this_compid = 0;
    target_sysid = 1;
    target_compid = 0;

    mav_vehicle = new Connection(port);
    decode = new DecodeMavPackets(mav_vehicle);
    //requestControlStateStream();
    timer_1second = new QTimer(this);
    connect(timer_1second, SIGNAL(timeout()), this, SLOT(oneSecondTimer()));
    timer_1second->start(1000);
}

void Vehicle::oneSecondTimer(void){
   mavSendHeartbeat();
}

void Vehicle::mavSendHeartbeat(void){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_heartbeat_pack(this_sysid, this_compid, &msg, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, MAV_MODE_PREFLIGHT, COPTER_MODE_STABILIZE, MAV_STATE_UNINIT);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

void Vehicle::mavTakeOff(void){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_command_long_pack(this_sysid, this_compid, &msg, target_sysid, 0, MAV_CMD_NAV_TAKEOFF, 0, 0, 0, 0, 0, 0, 0, 20);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

void Vehicle::requestControlStateStream(void){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint8_t streams[10] = {MAV_DATA_STREAM_ALL,
        MAV_DATA_STREAM_RAW_SENSORS,
        MAV_DATA_STREAM_EXTENDED_STATUS,
        MAV_DATA_STREAM_RC_CHANNELS,
        MAV_DATA_STREAM_RAW_CONTROLLER,
        MAV_DATA_STREAM_POSITION,
        MAV_DATA_STREAM_EXTRA1,
        MAV_DATA_STREAM_EXTRA2,
        MAV_DATA_STREAM_EXTRA3,
        MAV_DATA_STREAM_ENUM_END};
    for (int i = 0; i < 10; i++){
        uint16_t len = mavlink_msg_request_data_stream_pack(this_sysid, this_compid, &msg, target_sysid, target_compid, streams[i], 1, 0);
        len = mavlink_msg_to_send_buffer(&buf[0], &msg);
        qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
    }
}

void Vehicle::setMode(uint32_t mode){
    mavlink_message_t msg;
    requestControlStateStream();
    uint16_t len = mavlink_msg_set_mode_pack(this_sysid, this_compid, &msg, target_sysid, 1, mode);
    uint8_t buf[100] = {0};
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
