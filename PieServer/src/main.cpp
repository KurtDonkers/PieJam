#include <cstdlib>
#include <iostream>

#include "NetworkHandler.hpp"
#include "GfxRenderer.hpp"

int main (int argc, char* argv[])
{
    std::cout << "Hoi Pipeloi PieJam." << std::endl;

    NetworkHandler aNetworkHandler;
    aNetworkHandler.StartNetworkHandler();
    std::cout << "Started network handler." << std::endl;
    
    GfxRenderer aGfxRenderer;
    aGfxRenderer.StartGfxRenderer();
    std::cout << "Started graphics renderer." << std::endl;

    aNetworkHandler.setGfxRenderer(&aGfxRenderer);
    std::cout << "Linked graphics renderer to network handler." << std::endl;
    return 0;
}