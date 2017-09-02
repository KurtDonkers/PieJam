#pragma once

#include <thread>

struct clientInput
{
	int nrofstars;
};

extern clientInput GGfxInput;

class GfxRenderer
{
public:
    GfxRenderer() = default;
    ~GfxRenderer() = default;

    void StartGfxRenderer();
    void StopGfxRenderer();

private:
    void StartGlut();

private:
    std::thread* mGfxThread;
};
