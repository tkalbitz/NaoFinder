#ifndef INFOCAST_H
#define INFOCAST_H

#include <QMetaType>
#include <QtNetwork/QtNetwork>

class Infocast
{
public:
    QString robotName;
    QString lanMac;
    QString wifiMac;
    QString lanIp;
    QString wifiIp;
    int cpuTemp;
    int battery;
    int wifiSignal;

public:
    bool parse(QByteArray arr);
};

Q_DECLARE_METATYPE(Infocast)

#endif // INFOCAST_H
