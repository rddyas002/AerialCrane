#ifndef DECODEMAVPACKETS_H
#define DECODEMAVPACKETS_H

#include <QObject>
#include "connection.h"
#include "lib/mavlink/include/mavlink/ardupilotmega/mavlink.h"

class DecodeMavPackets : public QObject
{
    Q_OBJECT
public:
    explicit DecodeMavPackets(Connection * connection);

signals:

public slots:
    void decodePacket(const mavlink_message_t * msg);

};

#endif // DECODEMAVPACKETS_H
