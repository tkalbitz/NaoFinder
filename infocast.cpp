/*
 * NaoFinder - Make robots visible
 * Copyright 2012-2013 Tobias Kalbitz.
 * Subject to the AGPL, version 3.
 */

#include "infocast.h"
#include <stdint.h>
#include <stdio.h>

#include <arpa/inet.h>


bool Infocast::parse(QByteArray arr)
{
    const uint8_t MAGIC_BYTE = 0x11;
    const uint8_t VERSION    = 0x02;

    const char* buf = arr.constData();

    if(arr.size() < 25)
        return false;

    if(*buf != MAGIC_BYTE)
        return false;
    buf++;

    if(*buf != VERSION)
        return false;
    buf++;

    quint32 ip;

    memcpy(&ip, buf, sizeof(ip));
    buf += sizeof(ip);
    ip = ntohl(ip);
    lanIp = QHostAddress(ip).toString();

    memcpy(&ip, buf, sizeof(ip));
    buf += sizeof(ip);
    ip = ntohl(ip);
    wifiIp = QHostAddress(ip).toString();

    battery    = *buf; buf++;
    cpuTemp    = *buf; buf++;
    wifiSignal = *buf; buf++;

    char cBuffer[100] = {0};
    char mac[6];

    memcpy(&mac, buf, sizeof(mac));
    buf += sizeof(mac);
    snprintf(cBuffer, sizeof(cBuffer), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0]&0xff, mac[1]&0xff, mac[2]&0xff, mac[3]&0xff, mac[4]&0xff, mac[5]&0xff);
    lanMac.append(cBuffer);

    memcpy(&mac, buf, sizeof(mac));
    buf += sizeof(mac);
    snprintf(cBuffer, sizeof(cBuffer), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0]&0xff, mac[1]&0xff, mac[2]&0xff, mac[3]&0xff, mac[4]&0xff, mac[5]&0xff);
    wifiMac.append(cBuffer);

    while(*buf != '\0') {
        robotName.append(*buf);
        buf++;
    }

    return true;
}

