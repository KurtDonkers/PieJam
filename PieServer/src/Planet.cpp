#include "Planet.hpp"

#include <math.h>

#include "Util.hpp"

Planet::Planet (void)
{
    mPos[0] = SimUtil::DrawRandom (-1.0, 1.0);
    mPos[1] = SimUtil::DrawRandom (-1.0, 1.0);
}

void Planet::Update (double simtime)
{
}
