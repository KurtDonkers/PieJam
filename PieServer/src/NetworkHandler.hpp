#pragma once

#include <boost/asio.hpp>
#include <thread>

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

class UdpServer
{
public:
    UdpServer (boost::asio::io_service& aIoService, short port);
    void DoReceive (void);
    void DoSend (std::size_t length);

private:
    boost::asio::ip::udp::socket mSocket;
    boost::asio::ip::udp::endpoint mSenderEndpoint;
    enum { max_length = 1024 };
    char mData[max_length];
    char mDataToSend[max_length];
};

class NetworkHandler
{
public:
    NetworkHandler() = default;
    ~NetworkHandler();

    void StartNetworkHandler();
    void StopNetworkHandler();

private:
    void StartServer ();

private:
    unsigned short mPortNumber = 33100;
    std::thread* mNetworkThread;
};