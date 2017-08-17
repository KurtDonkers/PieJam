#pragma once

#include <boost/asio.hpp>

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
    ~NetworkHandler() = default;

    void StartServer ();

private:
    unsigned short mPortNumber = 33100;
    
};