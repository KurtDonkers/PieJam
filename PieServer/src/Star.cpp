#include "Star.hpp"

#include <math.h>
#include <iostream>

#include "Util.hpp"

Star::Star (void)
{
    mInitPos[0] = SimUtil::DrawRandom (-2.0, 2.0);
    mInitPos[1] = SimUtil::DrawRandom (-2.0, 2.0);
    //mInitPos[0] = -1.0;
    //mInitPos[1] = -1.0;
    mRadius = SimUtil::DrawRandom (0.01, 0.3);
    mFrequencyAchtigIets = SimUtil::DrawRandom (-5.0, 5.0);
    mPos[0] = mInitPos[0];
    mPos[1] = mInitPos[1];
    mVel[0] = SimUtil::DrawRandom (-0.1, 0.1);
    mVel[1] = SimUtil::DrawRandom (-0.1, 0.1);
    //mVel[0] = 0.0;
    //mVel[1] = 0.1;
    mAccel[0] = 0.0;
    mAccel[1] = 0.0;
}

void Star::UpdateStar (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars)
{
    mdelta = delta;
    mAccel[0] = 0.0;
    mAccel[1] = 0.0;
    for (auto &planet : planets)
    {
        double dx = 100.0 * (planet->GetPosX() - mPos[0]);
        double dy = 100.0 * (planet->GetPosY() - mPos[1]);
        double rsquared = (dx * dx) + (dy * dy);
        double r = sqrt (rsquared);
        double masssquared = GetMass() * planet->GetMass();

        double fg = SimUtil::cG * masssquared / rsquared;

        double fx = (dx / r) * fg;
        double fy = (dy / r) * fg;
        
        mAccel[0] += fx / GetMass();
        mAccel[1] += fy / GetMass();
    }
#if 0
    for (auto &star : stars)
    {
        if (this != star.get()) 
        {
            double dx = 100.0 * (star->GetPosX() - mPos[0]);
            double dy = 100.0 * (star->GetPosY() - mPos[1]);
            double rsquared = (dx * dx) + (dy * dy);
            double r = sqrt (rsquared);
            double masssquared = GetMass() * star->GetMass();
    
            double fg = SimUtil::cG * masssquared / rsquared;
    
            double fx = (dx / r) * fg;
            double fy = (dy / r) * fg;
            
            mAccel[0] += fx / GetMass();
            mAccel[1] += fy / GetMass();
        }
    }
#endif
    mVel[0] += mAccel[0] * delta * 0.1;
    mVel[1] += mAccel[1] * delta * 0.1;
    mPos[0] += mVel[0] * delta;
    mPos[1] += mVel[1] * delta;
}

void Star::UpdateVeer (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars)
{
    mdelta = delta;
    mAccel[0] = 0.0;
    mAccel[1] = 0.0;
    for (auto &planet : planets)
    {
        double dx = (planet->GetPosX() - mPos[0]);
        double dy = (planet->GetPosY() - mPos[1]);
        double rsquared = (dx * dx) + (dy * dy);
        double r = sqrt (rsquared);

        double fv = planet->GetVeerConstante() * r;

        double fx = (dx / r) * fv;
        double fy = (dy / r) * fv;
        
        mAccel[0] += fx / GetMass();
        mAccel[1] += fy / GetMass();
    }
    #if 0
    for (auto &star : stars)
    {
        if (this != star.get()) 
        {
            double dx = (star->GetPosX() - mPos[0]);
            double dy = (star->GetPosY() - mPos[1]);
            double rsquared = (dx * dx) + (dy * dy);
            double r = sqrt (rsquared);
    
            double fv = star->GetVeerConstante() * r;
    
            double fx = (dx / r) * fv;
            double fy = (dy / r) * fv;
            
            mAccel[0] += fx / GetMass();
            mAccel[1] += fy / GetMass();
        }
    }
#endif


    mVel[0] += mAccel[0] * delta * 0.1;
    mVel[1] += mAccel[1] * delta * 0.1;
    mPos[0] += mVel[0] * delta;
    mPos[1] += mVel[1] * delta;
}


void Star::Update (double simtime, double delta, std::vector<std::unique_ptr<Planet>>& planets, std::vector<std::unique_ptr<Star>>& stars)
{
    //UpdateStar (simtime, delta, planets, stars);
    UpdateVeer (simtime, delta, planets, stars);
}

void Star::DebugOutput (void)
{
    std::cout << mAccel[0] << " - " << mAccel[1] << " - " << mdelta << std::endl;
}