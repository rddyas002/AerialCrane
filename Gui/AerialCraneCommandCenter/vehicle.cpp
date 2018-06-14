#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    this_sysid = 250;
    this_compid = 0;
    target_sysid = 1;
    target_compid = 1;

    mav_vehicle = new Connection(port);
    decode = new DecodeMavPackets(mav_vehicle);
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

void Vehicle::mavSetMode(uint8_t mode){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_command_long_pack(this_sysid, this_compid, &msg, target_sysid, 0, mode, 0, 0, 0, 0, 0, 0, 0, 0);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

void Vehicle::defaultDataStreamRate(void){
    setStreamRate(MAV_DATA_STREAM_ALL, 0, 0);
    setStreamRate(MAV_DATA_STREAM_RAW_SENSORS, 0, 0);
    setStreamRate(MAV_DATA_STREAM_EXTENDED_STATUS, 0, 0);
    setStreamRate(MAV_DATA_STREAM_RC_CHANNELS, 0, 0);
    setStreamRate(MAV_DATA_STREAM_RAW_CONTROLLER, 0, 0);
    setStreamRate(MAV_DATA_STREAM_POSITION, 0, 0);
    setStreamRate(MAV_DATA_STREAM_EXTRA1, 0, 0);
    setStreamRate(MAV_DATA_STREAM_EXTRA2, 0, 0);
    setStreamRate(MAV_DATA_STREAM_EXTRA3, 0, 0);
    setStreamRate(MAV_DATA_STREAM_ENUM_END, 0, 0);
}

void Vehicle::setStreamRate(uint8_t stream_id, uint16_t frequency, uint8_t enable){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_request_data_stream_pack(this_sysid, this_compid, &msg, target_sysid, target_compid, stream_id, frequency, enable);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

void Vehicle::setMode(uint32_t mode){
    mavlink_message_t msg;
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
