#pragma once

#include <boost/asio.hpp>
#include <thread>
#include "GfxRenderer.hpp"

struct CtrlToPie
{
    int cmdid;
    int clientid;
    int nrofstars;
    float r; // [0..1]
    float g; // [0..1]
    float b; // [0..1]
};

struct PieToCtrl
{
    int responseid;
};

class NetworkHandler;

class UdpServer
{
public:
    UdpServer (boost::asio::io_service& aIoService, short port);
    void DoReceive (void);
    void DoReply (int clientid);

private:
    void UpdateReplyStruct (int clientid);
    void UpdateCommandStruct (CtrlToPie receivedCmd);
    void UpdateGfxInput(void);
    
private:
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mSenderEndpoint;
    enum { max_length = 1024 };
    char mData[max_length];
    char mDataToSend[max_length];
    std::map <int, struct PieToCtrl> mReplyMap;
    std::map <int, struct CtrlToPie> mCommandMap;
};

class NetworkHandler
{
public:
    NetworkHandler();
    ~NetworkHandler();

    void StartNetworkHandler();
    void StopNetworkHandler();

private:
    void StartServer ();

private:
    unsigned short mPortNumber = 33100;
    std::thread* mNetworkThread;
};