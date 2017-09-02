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
        boost::asio::buffer(tDataToSend, sizeof (PieToCtrl)), mSenderEndpoint,
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
                    std::cout << (int)mData[cidx] << " ";
                }
                std::cout << "]." << std::endl;

                CtrlToPie receivedCmd = {0};
                memcpy (&receivedCmd, mData, sizeof (CtrlToPie));

                DoReply (receivedCmd.clientid);
                std::cout << "nr of stars = " << receivedCmd.nrofstars << std::endl;
                UpdateCommandStruct(receivedCmd);
                UpdateGfxInput();
            }
            else
            {
                DoReceive();
            }
        });
}

void UdpServer::UpdateGfxInput() {
	int totalstars = 0;
	for (auto i : mCommandMap) {
		totalstars += i.second.nrofstars;
	}
	GGfxInput.nrofstars = totalstars;
}

void UdpServer::UpdateReplyStruct (int clientid)
{
    auto clientstruct = mReplyMap.find (clientid);
    if (clientstruct == mReplyMap.end())
    {
        PieToCtrl reply = {0};
        reply.responseid = 33;
        mReplyMap.insert (std::pair<int, PieToCtrl>(clientid, reply));
    }
    clientstruct->second.responseid += clientid;
}

void UdpServer::UpdateCommandStruct (CtrlToPie receivedCmd)
{
    mCommandMap.insert (std::pair<int, CtrlToPie>(receivedCmd.clientid, receivedCmd));
}

NetworkHandler::NetworkHandler()
{
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
    std::cout << "sizeof input " << sizeof(CtrlToPie) << std::endl;
    std::cout << "sizeof output " << sizeof(PieToCtrl) << std::endl;
    try
    {
        boost::asio::io_service io_service;
        UdpServer s(io_service, mPortNumber);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}



