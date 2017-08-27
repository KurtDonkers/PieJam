#include "NetworkHandler.hpp"

#include <iostream>

UdpServer::UdpServer (boost::asio::io_service& aIoService, short port, NetworkHandler* N)
  : mSocket (aIoService, boost::asio::ip::udp::endpoint (boost::asio::ip::udp::v4(), port))
  , mReplyMap()
{
	mNetworkHandler = N;
	mGfxRenderer = NULL;
    DoReceive();
}

void UdpServer::setGfxRenderer(GfxRenderer* R) {
	mGfxRenderer = R;
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
                    std::cout << mData[cidx];
                }
                std::cout << "]." << std::endl;

                CtrlToPie receivedCmd = {0};
                memcpy (&receivedCmd, mData, sizeof (CtrlToPie));

                DoReply (receivedCmd.clientid);
                std::cout << "nr of stars = " << receivedCmd.nrofstars << std::endl;
                ReadData();
            }
            else
            {
                DoReceive();
            }
        });
}

void UdpServer::ReadData() {
/*int cmdid;        0  - 3
int clientid;       4  - 7
int nrofstars;		8  - 11
float r; // [0..1]	12 - 15
float g; // [0..1]	16 - 19
float b; // [0..1]	20 - 23
*/
	mGfxRenderer = mNetworkHandler->getGfxRenderer();
	for (int i = 0; i < 24; ++i) {
            std::cout << "mData[" << i << "] = " << (int)mData[i] << std::endl;
    }
	if (mGfxRenderer != NULL) {
		int nrofstars;
		char nrofstars_arr[max_length] = {0};
		if (mData != NULL) {
			memcpy(&nrofstars_arr, &mData[8], 4);
			nrofstars = atoi(nrofstars_arr);
			std::cout << "Received: " << nrofstars << std::endl;
		}
		else {
			std::cout << "mData is NULL!" << std::endl;
		}
	}
	else {
		std::cout << "GfxRenderer is NULL!" << std::endl;
	}
}

void UdpServer::UpdateReplyStruct (int clientid)
{
    auto clientstruct = mReplyMap.find (clientid);
    if (clientstruct == mReplyMap.end())
    {
        PieToCtrl reply = {0};
        mReplyMap.insert (std::pair<int, PieToCtrl>(clientid, reply));
    }
    clientstruct->second.responseid += clientid;
}

NetworkHandler::NetworkHandler()
{
	mGfxRenderer = NULL;
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

void NetworkHandler::setGfxRenderer(GfxRenderer* R)
{
	mGfxRenderer = R;
}

GfxRenderer* NetworkHandler::getGfxRenderer()
{
	return mGfxRenderer;
}

void NetworkHandler::StartServer ()
{
    std::cout << "sizeof int " << sizeof(int) << std::endl;
    std::cout << "sizeof input " << sizeof(CtrlToPie) << std::endl;
    std::cout << "sizeof output " << sizeof(PieToCtrl) << std::endl;
    try
    {
        boost::asio::io_service io_service;
        UdpServer s(io_service, mPortNumber, this);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}



