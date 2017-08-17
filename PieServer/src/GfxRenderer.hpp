#pragma once

#include <thread>


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
