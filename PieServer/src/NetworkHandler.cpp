#include "NetworkHandler.hpp"

#include <iostream>

UdpServer::UdpServer (boost::asio::io_service& aIoService, short port)
  : mSocket (aIoService, boost::asio::ip::udp::endpoint (boost::asio::ip::udp::v4(), port))
  , mReplyMap()
{
    DoReceive();
}

void UdpServer::DoReply (int clientid)
{
    UpdateReplyStruct (clientid);
    auto clientstruct = mReplyMap.find (clientid)->second;
    char* tDataToSend = (char*)(&clientstruct);
    mSocket.async_send_to(
        boost::asio::buffer(tDataToSend, sizeof (struct PieToCtrl)), mSenderEndpoint,
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
                }
                std::cout << "]." << std::endl;

                struct CtrlToPie
                {
                    int cmdid;
                    int clientid;
                    int nrofstars;
                    float r; // [0..1]
                    float g; // [0..1]
                    float b; // [0..1]
                };
                struct CtrlToPie receivedCmd = {0};
                memcpy (&receivedCmd, mData, sizeof (struct CtrlToPie));

                DoReply (receivedCmd.clientid);
            }
            else
            {
                DoReceive();
            }
        });
}

void UdpServer::UpdateReplyStruct (int clientid)
{
    auto clientstruct = mReplyMap.find (clientid);
    if (clientstruct == mReplyMap.end())
    {
        struct PieToCtrl reply = {0};
        mReplyMap.insert (std::pair<int, struct PieToCtrl>(clientid, reply));
    }
    clientstruct->second.responseid += clientid;
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



