#include "Planet.hpp"

#include <math.h>

#include "Util.hpp"

Planet::Planet (void)
{
    mPos[0] = SimUtil::DrawRandom (-1.0, 1.0);
    mPos[1] = SimUtil::DrawRandom (-1.0, 1.0);
    mCVeer = SimUtil::DrawRandom (1, 5);
}

double Planet::GetVeerConstante (void) {
    return SimUtil::DrawRandom (0.33, 0.55);
}

void Planet::Update (double simtime)
{
}
