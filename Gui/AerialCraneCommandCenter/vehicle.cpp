#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    mav_vehicle = new Connection(host_address, port);
    decode = new DecodeMavPackets(mav_vehicle);
    //requestControlStateStream();
}

void Vehicle::requestControlStateStream(void){
    mavlink_message_t msg;
    mavlink_msg_request_data_stream_pack(255, 0, &msg, 1, 0, MAVLINK_MSG_ID_CONTROL_SYSTEM_STATE, 5, 1);
    qint64 sent = mav_vehicle->transmit(QByteArray::fromRawData((const char *)&msg, sizeof(mavlink_message_t)));
    qDebug() << sent;
}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
