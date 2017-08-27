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
    UdpServer (boost::asio::io_service& aIoService, short port, NetworkHandler* N);
    void DoReceive (void);
    void DoReply (int clientid);
    void setGfxRenderer(GfxRenderer* R);

private:
    void UpdateReplyStruct (int clientid);
    void ReadData(void);
    
private:
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mSenderEndpoint;
    enum { max_length = 1024 };
    char mData[max_length];
    char mDataToSend[max_length];
    std::map <int, struct PieToCtrl> mReplyMap;

    GfxRenderer* mGfxRenderer;
    NetworkHandler* mNetworkHandler;
};

class NetworkHandler
{
public:
    NetworkHandler();
    ~NetworkHandler();

    void StartNetworkHandler();
    void StopNetworkHandler();
    void setGfxRenderer(GfxRenderer* R);
    GfxRenderer* getGfxRenderer();

private:
    void StartServer ();

private:
    unsigned short mPortNumber = 33100;
    std::thread* mNetworkThread;
    GfxRenderer* mGfxRenderer;
};