#include "vehicle.h"

#define STREAM_ALL_ON               0
#define STREAM_RAW_SENSORS_ON       0
#define STREAM_EXTENDED_STATUS_ON   1
#define STREAM_RC_CHANNELS_ON       0
#define STREAM_RAW_CONTROLLER_ON    0
#define STREAM_POSITION_ON          1
#define STREAM_EXTRA1_ON            1
#define STREAM_EXTRA2_ON            0
#define STREAM_EXTRA3_ON            0

#define STREAM_ALL_FREQ             1
#define STREAM_RAW_SENSORS_FREQ     1
#define STREAM_EXTENDED_STATUS_FREQ 1
#define STREAM_RC_CHANNELS_FREQ     1
#define STREAM_RAW_CONTROLLER_FREQ  1
#define STREAM_POSITION_FREQ        10
#define STREAM_EXTRA1_FREQ          10
#define STREAM_EXTRA2_FREQ          1
#define STREAM_EXTRA3_FREQ          1

Vehicle::Vehicle(const QString host_address, uint32_t port, uint8_t channel)
{
    this_sysid = 250;
    this_compid = 0;
    target_sysid = 1;
    target_compid = 1;

    mav_vehicle = new Connection(port, channel);
    decode = new DecodeMavPackets(mav_vehicle);
    timer_1second = new QTimer(this);
    connect(timer_1second, SIGNAL(timeout()), this, SLOT(oneSecondTimer()));
    timer_1second->start(1000);
}

DecodeMavPackets * Vehicle::getDecoder(void){
    return decode;
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

void Vehicle::mavTakeOff(float height){
    mavCommandLong(MAV_CMD_NAV_TAKEOFF, 0, 0,0,0,0,0,height);
}

void Vehicle::mavLand(void){
    mavCommandLong(MAV_CMD_NAV_LAND, 0, 0,0,0,0,0,0);
}

void Vehicle::mavCommandLong(uint16_t cmd, float param1, float param2, float param3, float param4, float param5, float param6, float param7){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_command_long_pack(this_sysid, this_compid, &msg, target_sysid, 0, cmd, 0, param1, param2, param3, param4, param5, param6, param7);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
}

void Vehicle::defaultDataStreamRate(void){
    setStreamRate(MAV_DATA_STREAM_ALL, STREAM_ALL_FREQ, STREAM_ALL_ON);
    setStreamRate(MAV_DATA_STREAM_RAW_SENSORS, STREAM_RAW_SENSORS_FREQ, STREAM_RAW_SENSORS_ON);
    setStreamRate(MAV_DATA_STREAM_EXTENDED_STATUS, STREAM_EXTENDED_STATUS_FREQ, STREAM_EXTENDED_STATUS_ON);
    setStreamRate(MAV_DATA_STREAM_RC_CHANNELS, STREAM_RC_CHANNELS_FREQ, STREAM_RC_CHANNELS_ON);
    setStreamRate(MAV_DATA_STREAM_RAW_CONTROLLER, STREAM_RAW_CONTROLLER_FREQ, STREAM_RAW_CONTROLLER_ON);
    setStreamRate(MAV_DATA_STREAM_POSITION, STREAM_POSITION_FREQ, STREAM_POSITION_ON);
    setStreamRate(MAV_DATA_STREAM_EXTRA1, STREAM_EXTRA1_FREQ, STREAM_EXTRA1_ON);
    setStreamRate(MAV_DATA_STREAM_EXTRA2, STREAM_EXTRA2_FREQ, STREAM_EXTRA2_ON);
    setStreamRate(MAV_DATA_STREAM_EXTRA3, STREAM_EXTRA3_FREQ, STREAM_EXTRA3_ON);
    setStreamRate(MAV_DATA_STREAM_ENUM_END, 0, 0);

    //setIntervalRate(MAVLINK_MSG_ID_ATTITUDE, 100000);
}

void Vehicle::setIntervalRate(uint16_t message_id, int32_t interval_us){
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len = mavlink_msg_message_interval_pack(this_sysid, this_compid, &msg, message_id, interval_us);
    len = mavlink_msg_to_send_buffer(&buf[0], &msg);
    qint64 sent = mav_vehicle->transmit((const char *)&buf[0], len);
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
