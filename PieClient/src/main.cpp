#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

enum { max_length = 1024 };

int main (int argc, char* argv[])
{
    try
    {
        std::string tServerIp = "192.168.2.39";
        std::string tServerPort = "33100";

        boost::asio::io_service io_service;
        udp::socket s(io_service, udp::endpoint(udp::v4(), 0));

        udp::resolver resolver(io_service);
        udp::endpoint endpoint = *resolver.resolve({udp::v4(), tServerIp, tServerPort});

        std::cout << "Enter number of stars: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        int input = atoi(request);
        size_t request_length = std::strlen(request);

        char mData[max_length] = {0};
        memcpy(&mData[8], &input, 4);

        for (int i = 0; i < 24; ++i) {
            std::cout << "mData[" << i << "] = " << (int)mData[i] << std::endl;
        }

        s.send_to(boost::asio::buffer(mData, request_length), endpoint);

        char reply[max_length];
        udp::endpoint sender_endpoint;
        size_t reply_length = s.receive_from(
            boost::asio::buffer(reply, max_length), sender_endpoint);
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}