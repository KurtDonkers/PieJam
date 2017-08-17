#include <cstdlib>
#include <iostream>

#include "NetworkHandler.hpp"

int main (int argc, char* argv[])
{
    std::cout << "Hoi Pipeloi PieJam." << std::endl;

    NetworkHandler aNetworkHandler;
    aNetworkHandler.StartNetworkHandler();

    std::cout << "Hier ben ik " << std::endl;

    return 0;
}