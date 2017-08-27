#include "NetworkHandler.hpp"

#include <iostream>

UdpServer::UdpServer (boost::asio::io_service& aIoService, short port)
  : mSocket (aIoService, boost::asio::ip::udp::endpoint (boost::asio::ip::udp::v4(), port))
{
    DoReceive();
}

void UdpServer::DoSend (std::size_t length)
{
    mSocket.async_send_to(
        boost::asio::buffer(mDataToSend, length), mSenderEndpoint,
        [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
        {
          DoReceive();
        });
}

void UdpServer::DoReceive()
{
    mSocket.async_receive_from(
        boost::asio::buffer(mData, max_length), mSenderEndpoint,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
            if (!ec && bytes_recvd > 0)
            {
                std::cout << "Received [";
                for (unsigned int cidx = 0; cidx < bytes_recvd; cidx++)
                {
                    std::cout << mData[cidx];
                    mDataToSend[bytes_recvd-cidx-1] = mData[cidx];
                }
                mDataToSend[bytes_recvd] = '\0';
                std::cout << "]." << std::endl;
                DoSend (bytes_recvd);
            }
            else
            {
                DoReceive();
            }
        });
}


NetworkHandler::~NetworkHandler()
{
    StopNetworkHandler();
}

void NetworkHandler::StartNetworkHandler()
{
    mNetworkThread = new std::thread (&NetworkHandler::StartServer, this);
}

void NetworkHandler::StopNetworkHandler()
{
    mNetworkThread->join();
}


void NetworkHandler::StartServer ()
{
    std::cout << "sizeof int " << sizeof(int) << std::endl;
    std::cout << "sizeof input " << sizeof(struct CtrlToPie) << std::endl;
    std::cout << "sizeof output " << sizeof(struct PieToCtrl) << std::endl;
    try
    {
        boost::asio::io_service io_service;
        UdpServer s (io_service, mPortNumber);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}


