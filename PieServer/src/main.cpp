#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

class server
{
public:
    server (boost::asio::io_service& io_service, short port)
    : mSocket (io_service, udp::endpoint (udp::v4(), port))
    {
        do_receive();
    }

    void do_receive()
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
                    do_send (bytes_recvd);
                }
                else
                {
                    do_receive();
                }
            });
    }

    void do_send (std::size_t length)
    {
        mSocket.async_send_to(
            boost::asio::buffer(mData, length), mSenderEndpoint,
            [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
            {
              do_receive();
            });
    }

private:
    udp::socket mSocket;
    udp::endpoint mSenderEndpoint;
    enum { max_length = 1024 };
    char mData[max_length];
};

int main (int argc, char* argv[])
{
    try
    {
        std::cout << "Hoi Pipeloi PieJam." << std::endl;
        unsigned short mPortNumber = 33100;

        boost::asio::io_service io_service;
        server s(io_service, mPortNumber);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

  return 0;
}