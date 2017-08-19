#include "Star.hpp"

#include <math.h>

#include "Util.hpp"

Star::Star (void)
{
    mInitPos[0] = SimUtil::DrawRandom (-2.0f, 2.0f);
    mInitPos[1] = SimUtil::DrawRandom (-2.0f, 2.0f);
    mRadius = SimUtil::DrawRandom (0.01f, 0.3f);
    mFrequencyAchtigIets = SimUtil::DrawRandom (-5.0f, 5.0f);
}

void Star::Update (double simtime)
{
    mPos[0] = mInitPos[0] + sin (simtime * mFrequencyAchtigIets) * mRadius;
    mPos[1] = mInitPos[1] + cos (simtime * mFrequencyAchtigIets) * mRadius;
}
