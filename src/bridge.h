#ifndef BRIDGE_H
#include <Arduino.h>
#include <WiFi.h>
#include <list>
#include <vector>
//#include "utils.h"

typedef std::vector<byte> apiframe;



typedef std::list<apiframe> PacketRxList_t;

enum bridge_mode_t
{
	WAIT,
	CONNECTING,
	CONNECTED,
	DISCONNECTING
};

class Bridge
{
    public:
    Bridge();
    Bridge(int _port);


    static bridge_mode_t state;
    static PacketRxList_t packetList;
    static WiFiServer* bridge_server;
    static WiFiClient client;
    static bool enabled;
    static int port;

    static std::function<void()> cbConnecting;
    static std::function<void()> cbDisconnecting;
    static std::function<void(apiframe pkt)> cbAddPacketToSmkTxBuffer;
    static std::function<void(apiframe pkt, String prefix)> cbWhenSmkPacketReceived;


    static void init();
    static bool taskloop();
    static size_t write();
    static void putPacketInsideBuffer(apiframe packet, uint8_t* buffer);
    static bool isConnecting();
    static bool isDisconnecting();
    static bool isConnected(){return (state==CONNECTED);};
    static bool WhenNewSmkPacketRx(apiframe packet){if(state==CONNECTED) packetList.push_back(packet); return (state==CONNECTED);};
    static void parseApiFromHost(uint8_t* buf, uint16_t len);
};

#endif