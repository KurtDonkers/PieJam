#include "Planet.hpp"

#include <math.h>

#include "Util.hpp"

Planet::Planet (void)
{
    mPos[0] = 0.0f;
    mPos[1] = 0.0f;
}

void Planet::Update (double simtime)
{
    mPos[0] = mInitPos[0] + sin (simtime * mFrequencyAchtigIets) * mRadius;
    mPos[1] = mInitPos[1] + cos (simtime * mFrequencyAchtigIets) * mRadius;
}
